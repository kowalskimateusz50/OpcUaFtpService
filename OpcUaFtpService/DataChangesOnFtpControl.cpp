#include "DataChangesOnFtpControl.hpp"

void DetectDataChangesOnFtp(ProductionData& ProductionBatchFromGD, ProductionData& ProductionBatchOnPlc, LoggingToTextFile& MessageFile, WriteDataToPLC& PLC)
{
	/* Detecting moment of incoming data */
	if (ProductionBatchFromGD.IsEmpty() == 0 && ProductionBatchOnPlc.IsEmpty() == 1)
	{
		//cout << "\nNew production data arrived: " << endl;
		MessageFile.AppendLog("New production data arrived", M_INFO);
		ProductionBatchOnPlc.CopyData(ProductionBatchFromGD);

		ProductionBatchOnPlc.PrintDataToConsole();
		MessageFile.AppendLog(ProductionBatchOnPlc.PrintDataToFile(), M_INFO);

		/* Write data to PLC */
		PLC.Write(ProductionBatchOnPlc, OPC_SERVER_ADRESS);
		MessageFile.AppendLog("Data has been written to PLC", M_INFO);
	}
	else if (ProductionBatchFromGD.IsEmpty() == 1 && ProductionBatchOnPlc.IsEmpty() == 0)
	{
		//cout << "\nProduction data cleared: " << endl;
		ProductionBatchOnPlc.ClearData();

		ProductionBatchOnPlc.PrintDataToConsole();
		MessageFile.AppendLog(ProductionBatchOnPlc.PrintDataToFile(), M_INFO);

		/* Write data to PLC */
		PLC.Write(ProductionBatchOnPlc, OPC_SERVER_ADRESS);
		MessageFile.AppendLog("Data has been written to PLC", M_INFO);
	}
}