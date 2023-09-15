#include "FtpReadProductionData.hpp"

int FtpReadProductionData::InitFtpConnection(LPCWSTR iServerAdress, LPCWSTR iServerUsername, LPCWSTR iServerPassword, LPCWSTR iFileServerPath, LPCWSTR iArchDestPath, LoggingToTextFile& MessageFile)
{
	/* Save connection parameters into class members */

	/* Saving Server adress */
	ServerAdress = iServerAdress;

	/* Saving Server username */
	ServerUsername = iServerUsername;

	/* Saving Server password */
	ServerPassword = iServerPassword;

	/*Saving path to find files on server */
	FileServerPath = iFileServerPath;

	/* Saving destination server path to archive copied files */
	ArchDestPath = iArchDestPath;

	/* Open internet connection with error handling */
	hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (hInternet == NULL)
	{
		//cout << "\nError during opening connection: " << GetLastError();
		MessageFile.AppendLog("Connection opening failed" + to_string(GetLastError()), M_ERROR);
		return GetLastError();
	}
	else
	{
		//cout << "\nInternet connection opened succesfully: ";
		MessageFile.AppendLog("Connection opening succesfull", M_INFO);

		hFtpSession = InternetConnect(hInternet, ServerAdress, INTERNET_DEFAULT_FTP_PORT, ServerUsername, ServerPassword, INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
		if (hFtpSession == NULL)
		{
			//cout << "Error during opening connection with FTP server: " << GetLastError();
			MessageFile.AppendLog("FTP Connection opening failed" + to_string(GetLastError()), M_ERROR);
			return GetLastError();
		}
		else
		{
			//_tprintf(TEXT("Opened connection with FTP server: %s\n"), ServerAdress);
			MessageFile.AppendLog("FTP Connection opening succesfull", M_INFO);
			return 0;
		}
		
	}
}
string FtpReadProductionData::WcharToString(WCHAR* wstr)
{
	//convert from wide char to narrow char array
	std::wstring WstringToConvert(wstr);

	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)WstringToConvert.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)WstringToConvert.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}

int FtpReadProductionData::ArchiveFoundFile(LoggingToTextFile& MessageFile)
{

	/* Creating destination file path */
	wcscpy(ArchivedFilePath, ArchDestPath);
	wcscat(ArchivedFilePath, FoundFileName); 


	/* Create new local folder if doesn't exist */
	if (CreateDirectory(ArchDestPath, NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError())
	{
		if (ERROR_ALREADY_EXISTS != GetLastError())
		{
			MessageFile.AppendLog("Log folder created", M_INFO);
		}
		/* Copy file to local directory  */
		FtpGetFile(hFtpSession, FoundFilePath, ArchivedFilePath, FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_ASCII, 0);
		MessageFile.AppendLog("File copied to local achrive", M_INFO);
	}
	else
	{
		//cout << "\nLog: Folder creating failed";
		MessageFile.AppendLog("Folder creating failed", M_ERROR);
	}

	return 0;

}
int FtpReadProductionData::VerfifyFoundFile(string FoundFile)
{
	if (FoundFile[0] == 'W' && FoundFile[1] == 'O' && FoundFile[2] == '_' && FoundFile[15] == '.' && FoundFile[16] == 'c' && FoundFile[17] == 's' && FoundFile[18] == 'v')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int FtpReadProductionData::ReadFoundFile(ProductionData& Data)
{
	ifstream file;
	int LineNumber = 0;
	file.open(ArchivedFilePath);
	string line;
	while (getline(file, line)) 
	{
		if (LineNumber == 1)
		{
			string column = "";
			int ColumnIndex = 0;
			stringstream s(line);
			
			/* read every column data of a row and
			 store it in a string variable, 'word' */

			while(getline(s, column, ';')) 
			{
				/* Selecting variable to assign */
				if(ColumnIndex == 0)
					Data.WorkOrderNumber = column;
				else if(ColumnIndex == 1)
					Data.ProductionLineNumber = column;
				else if (ColumnIndex == 2)
					Data.ProductionItemSku = column;
				else if (ColumnIndex == 3)
					Data.ProductionItemEan = column;
				else if (ColumnIndex == 4)
					Data.ProductionBatchNo = column;
				else if (ColumnIndex == 5)
					Data.WorkOrderQuantity = stoi(column);

				/* Increment column counter */
				ColumnIndex++;
			}
		}
		LineNumber++;
	}
	file.close();
	return 0;
}
int FtpReadProductionData::FindFileOnFtpServer(ProductionData& Data, LoggingToTextFile& MessageFile)
{

	/* Definie structure wchich store parameters of found file */
	WIN32_FIND_DATA FtpFileData; // NOTE: not LP
	/* Define handler for find function */
	HINTERNET hFind = NULL;

	MessageFile.AppendLog("Start scanning specified FTP folder", M_INFO);

	/* Open connection with specified server*/
	hFind = FtpFindFirstFile(hFtpSession, FileServerPath, &FtpFileData, FALSE, 0);

		/* Find file in FTP Server */
		if(!hFind)
		{
			DWORD LastError = GetLastError();
			MessageFile.AppendLog("Error during searching file: " + to_string(LastError), M_ERROR);

			/* Clear Porduction data */
			Data.ClearData();

			/* Restore connection if was broken */
			if (LastError == 12030 || LastError == 6)
			{
				MessageFile.AppendLog("Attempt to restore connection: ", M_ERROR);
				cout << "\nAttempt to restore connection : ";
				InitFtpConnection(ServerAdress, ServerUsername, ServerPassword, FileServerPath, ArchDestPath, MessageFile);
			}
		}
		else
		{
			/* Log found file name */
			MessageFile.AppendLog("The first file found is: " + WcharToString(FtpFileData.cFileName), M_INFO);

			cout << "\nThe first file found is : " + WcharToString(FtpFileData.cFileName) << endl;

			//MessageFile.AppendLog("File verification stared", M_INFO);
			//cout << "\nFile verification started: " << endl;

			if (VerfifyFoundFile(WcharToString(FtpFileData.cFileName)))
			{
				/* Log file verified */
				MessageFile.AppendLog("File verification passed", M_INFO);
				cout << "\nFile verification passed: " << endl;

				/* Save file name into class */
				wcscpy(FoundFileName, FtpFileData.cFileName);

				/* Save Ftp Server Path into class */
				wcscpy(FoundFilePath, FileServerPath);
				wcscat(FoundFilePath, FoundFileName);

				/* Copy found file to archive */
				ArchiveFoundFile(MessageFile);
				MessageFile.AppendLog("Found file has been archived: ", M_INFO);

				/* Read found file */
				ReadFoundFile(Data);
				MessageFile.AppendLog("Found file has been read: ", M_INFO);
			}
			else
			{
				/* Log file verification failed */
				MessageFile.AppendLog("File verification failed, file has been ignored", M_INFO);
				cout << "\nFile verification failed, file has been ignored: " << endl;
			}

			// Close FtpFindFirstFile
			InternetCloseHandle(hFind);
		}
		return 0;
}
void FtpReadProductionData::CloseFtpConnection()
{
	InternetCloseHandle(hFtpSession); // Close hFtpSession
	InternetCloseHandle(hInternet); // Close hInternet  
}