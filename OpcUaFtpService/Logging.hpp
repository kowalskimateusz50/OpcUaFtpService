#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <mutex>
#pragma once
#define _WINSOCKAPI_ 
#include <string>
#include <fstream>
#include <windows.h>
#include <chrono>
#include <ctime>
#include <atlstr.h>
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "user32.lib")

using namespace std;

/* Define types of messages */
#define M_INFO 1
#define M_WARNING 2
#define M_ERROR 3

class LoggingToTextFile
{
	public:
		LoggingToTextFile(LPCWSTR iLogFolderPath);
		int AppendLog(string LogMessage, int LogType);


	private:
		LPCWSTR LogFolderPath;
		mutex mLock;

		time_t ttime;
		tm* local_time;

		string LogFileName;
		string LogFileFolder;
		string LogFilePath;

		fstream LogFile;

		string AddLeadingZero(int Number);
		string GetMessageType(int Type);


};
