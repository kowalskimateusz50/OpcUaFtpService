#include "Logging.hpp"

LoggingToTextFile::LoggingToTextFile(LPCWSTR iLogFolderPath)
{
	/* Save log foler path into class */
	LogFolderPath = iLogFolderPath;

	/* Create new local folder if doesn't exist */
	if (CreateDirectory(LogFolderPath, NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError())
	{
		if (ERROR_ALREADY_EXISTS != GetLastError())
		{
			wcout << "\nLog: New folder created: " << LogFolderPath;
		}
	}
	else
	{
		cout << "\nLog: Fail during folder creation";
	}
}
int LoggingToTextFile::AppendLog(string LogMessage, int LogType)
{
	ttime = time(0);
	local_time = localtime(&ttime);


	/* Prepare date for filename creation*/
	LogFileName = to_string(1900 + local_time->tm_year) + AddLeadingZero(local_time->tm_mon) + to_string(local_time->tm_mday);
	LogFileFolder = CW2A(LogFolderPath);
	LogFilePath = LogFileFolder + LogFileName + ".txt";

	/* File opening */
	LogFile.open(LogFilePath, std::ios_base::app);

	/* Writing string to file */
	LogFile << GetMessageType(LogType) + "[" + to_string(local_time->tm_mday) + "/" + AddLeadingZero(local_time->tm_mon) + "/" + to_string(1900 + local_time->tm_year) + " " + AddLeadingZero(local_time->tm_hour) + ":" + AddLeadingZero(local_time->tm_min) + ":" + AddLeadingZero(local_time->tm_sec) + "]" + ": " + LogMessage << endl;
	
	/* File closing */
	LogFile.close();

	return 0;
}
string LoggingToTextFile::AddLeadingZero(int Number)
{
	if (Number < 10)
	{
		return "0" + to_string(Number);
	}
	else
	{
		return to_string(Number);
	}
}

string LoggingToTextFile::GetMessageType(int Type)
{
	if (Type == 1)
	{
		return "[Info]";
	}
	else if (Type == 2)
	{
		return "[Warning]";
	}
	else if (Type == 3)
	{
		return "[Error]";
	}
	return "";
}
