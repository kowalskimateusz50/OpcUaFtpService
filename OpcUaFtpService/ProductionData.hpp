#pragma once 

#include<iostream>
#include<string.h>

/* Definition of production data structure */
struct ProductionData {
	std::string WorkOrderNumber;
	int WorkOrderQuantity;
	std::string ProductionLineNumber;
	std::string ProductionItemEan;
	std::string ProductionItemSku;
	std::string ProductionBatchNo;

	void TestInputData(); /* Inputing some test production data to structure */
	void ClearData(); /* Clear production data wchich means set empty strings and 0 quantities */
};


