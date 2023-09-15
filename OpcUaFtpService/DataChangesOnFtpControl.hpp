#include<iostream>

#include "Parameters.hpp"
#include "FtpReadProductionData.hpp"
#include "ProductionData.hpp"
#include "WriteDataToPLC.hpp"

/* Function for detecting   */
void DetectDataChangesOnFtp(ProductionData& ProductionBatchFromGD, ProductionData& ProductionBatchOnPlc, LoggingToTextFile& MessageFile, WriteDataToPLC& PLC);
