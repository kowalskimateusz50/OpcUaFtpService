#pragma once 
#include<iostream>
#include<string.h>
#include<sstream>

/* Definition of production data structure */
class ProductionData {
public:
	std::string WorkOrderNumber;
	int WorkOrderQuantity;
	std::string ProductionLineNumber;
	std::string ProductionItemEan;
	std::string ProductionItemSku;
	std::string ProductionBatchNo; 
																	
	void TestInputData(); /* Inputing some test production data to structure */
	void PrintDataToConsole(); /* Print input data to console */
	std::string PrintDataToFile(); /* Print input data to LogFile */
	void ClearData(); /* Clear production data wchich means set empty strings and 0 quantities */
	int  IsEmpty(); /* Checking whether data structure is empty */
	void CopyData(ProductionData& InputData); /* Copying data */
};


