#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <thread>
#include <mutex>

#include "FtpThreadListening.hpp"
#include "ProductionData.hpp"
#include "DataChangesOnFtpControl.hpp"
#include "Logging.hpp"
#include "Parameters.hpp"
#include "WriteDataToPLC.hpp"

int main()
{
	std::mutex Mlock;

	/* Create general program folder */
		/* Create new local folder if doesn't exist */
	if (CreateDirectory(ROOT_PATH, NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError())
	{
		if (ERROR_ALREADY_EXISTS != GetLastError())
		{
			cout << "\nLog: New folder created: " << ROOT_PATH;
		}
	}
	else
	{
		cout << "\nLog: Fail during folder creation";
	}
	/* Declare object responsible for writing data on PLC */
	WriteDataToPLC PLC;

	/* Declare production data structure instance wchich is receiving from GD machine */
	ProductionData ProductionBatchFromGD, ProductionBatchOnPlc;

	/* Create text file logging object */
	LoggingToTextFile MessageFile(LOGGING_PATH);

	/* Log print Examples */
	MessageFile.AppendLog("Program is starting",M_INFO);

	/* Clear Declared Production Data */
	ProductionBatchFromGD.ClearData();
	ProductionBatchOnPlc.ClearData();

	//this_thread::sleep_for(50000ms);

	/* Create FTP Read Production Thread */
	std::thread FtpListener(FtpListeningThread, std::ref(ProductionBatchFromGD), std::ref(Mlock), std::ref(MessageFile));

	/* Endless loop for testing */
	while (true)
	/* Detecting changes on input from FTP */
	{
		Mlock.lock();
		DetectDataChangesOnFtp(ProductionBatchFromGD, ProductionBatchOnPlc, MessageFile, PLC);
		Mlock.unlock();

		//this_thread::sleep_for(5000ms);
	}

	/* Wait for end thred jobs */
	FtpListener.join();

	return 0;

}
