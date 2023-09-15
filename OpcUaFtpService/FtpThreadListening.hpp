#pragma once
#include "FtpReadProductionData.hpp"
#include "Logging.hpp"
#include<mutex>
/* Declaration of void function ich wchich FTP thread is executing */
void FtpListeningThread(ProductionData& Data, std::mutex& Mlock, LoggingToTextFile& MessageFile);
