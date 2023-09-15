#include "FtpThreadListening.hpp"
#include "Parameters.hpp"

void FtpListeningThread(ProductionData& Data, std::mutex& Mlock, LoggingToTextFile& MessageFile)
{
    using namespace std;

    //Initialize ftp server connection
    FtpReadProductionData DhlData;

    //int InitFtpConnection(string iServerAdress, string iServerUsername, string iServerPassword, string iFileServerPath, string iArchDestPath)
    DhlData.InitFtpConnection(SERVER_IP_ADRESS, SERVER_USERNAME, SERVER_PASSWORD, SERVER_PATH, ARCHIVE_PATH, MessageFile);

    //  Periodically check if the service has been requested to stop
    while (true)
    {
        /* Find production batch file on FTP server */
        Mlock.lock();
        DhlData.FindFileOnFtpServer(Data, MessageFile);
        Mlock.unlock();

        this_thread::sleep_for(5000ms);
    }
    DhlData.CloseFtpConnection();
}