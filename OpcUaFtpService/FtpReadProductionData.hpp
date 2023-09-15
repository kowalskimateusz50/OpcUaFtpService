#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCKAPI_ 
#include <chrono>
#include <iostream>
#include <windows.h>
#include <stdio.h>         
#include <wininet.h> 
#include <tchar.h>
#include <string.h>
#include <fstream>
#include <string>
#include <thread>
#include <sstream>
#include <atlstr.h>

#include "ProductionData.hpp"
#include "Logging.hpp"

#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "user32.lib")

using namespace std;

/* Ftp connecion class */

    class FtpReadProductionData
    {
        /* Found file name */
        WCHAR FoundFileName[MAX_PATH];

        /* Found file path */
        WCHAR FoundFilePath[MAX_PATH];

        /* Archived file path */
        WCHAR ArchivedFilePath[MAX_PATH];

        /* Definition of connection handlers */
        HINTERNET hInternet = NULL;
        HINTERNET hFtpSession = NULL;

    public:

        /* Declare FTP Server parameters */
        //Server IP adresS
        LPCWSTR ServerAdress;
        //Server Username
        LPCWSTR ServerUsername;
        //Server password
        LPCWSTR ServerPassword;
        //Server path to find file
        LPCWSTR FileServerPath;
        //Server destination file path
        LPCWSTR ArchDestPath;

        /* Function for initialization of FTP Connection 
        * @param:string ServerAdress
        * @param:string ServerUsername
        * @param:string ServerPassword
        * @param:string FilePath
        * @param: string ArchDestPath
        */
        int InitFtpConnection(LPCWSTR iServerAdress, LPCWSTR iServerUsername, LPCWSTR iServerPassword, LPCWSTR iFileServerPath, LPCWSTR iArchDestPath, LoggingToTextFile& MessageFile);
        int FindFileOnFtpServer(ProductionData& Data, LoggingToTextFile& MessageFile);
        void CloseFtpConnection();

    private:
        string WcharToString(WCHAR* wstr);
        int VerfifyFoundFile(string FoundFile);
        int ArchiveFoundFile(LoggingToTextFile& MessageFile);
        int ReadFoundFile(ProductionData& Data);
    };

