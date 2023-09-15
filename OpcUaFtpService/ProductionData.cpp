#include "ProductionData.hpp"

/* Method to simulate Production data input from future csv file (only for testing purpose) */
void ProductionData::TestInputData() {
    /* Input of work order number */
    WorkOrderNumber = "00010xxxx877";
    
    /* Input of production line number */
    ProductionLineNumber = "I4AL01";

    /* Input of production item ean */
    ProductionItemEan = "7622100597018";

    /* Input of production item sku */
    ProductionItemSku = "DK003095.01";

    /* Input of production batch no */
    ProductionBatchNo = "LG-4573271";

    /* Input of work order quantity */
    WorkOrderQuantity = 1770;
}

/* Method to clearing production Data structure */
void ProductionData::ClearData() {
    /* Clear work order number */
    WorkOrderNumber = "";

    /* Clear production line number */
    ProductionLineNumber = "";

    /* Clear production item ean */
    ProductionItemEan = "";

    /* Clear production item sku */
    ProductionItemSku = "";

    /* Clear production batch no */
    ProductionBatchNo = "";

    /* Clear work order quantity */
    WorkOrderQuantity = 0;
}

void ProductionData::PrintDataToConsole()
{
    /* Print of work order number */
    std::cout << "\nWork order number: " << WorkOrderNumber;

    /* Print of production line number */
    std::cout << "\nProduction line number: " << ProductionLineNumber;

    /* Print of production item ean */
    std::cout << "\nProduction item ean: " << ProductionItemEan;

    /* Print of production item sku */
    std::cout << "\nProduction item sku: " << ProductionItemSku;

    /* Print of production batch no */
    std::cout << "\nProduction batch no: " << ProductionBatchNo;

    /* Print of work order quantity */
    std::cout << "\nWork order quantity: " << WorkOrderQuantity;
}
std::string ProductionData::PrintDataToFile()
{
    std::stringstream LogFile;

    /* Print of work order number */
    LogFile << "\nWork order number: " << WorkOrderNumber;

    /* Print of production line number */
    LogFile << "\nProduction line number: " << ProductionLineNumber;

    /* Print of production item ean */
    LogFile << "\nProduction item ean: " << ProductionItemEan;

    /* Print of production item sku */
    LogFile << "\nProduction item sku: " << ProductionItemSku;

    /* Print of production batch no */
    LogFile << "\nProduction batch no: " << ProductionBatchNo;

    /* Print of work order quantity */
    LogFile << "\nWork order quantity: " << WorkOrderQuantity;

    return LogFile.str();
}
/* Check whether Production Data structure is empty */
int ProductionData::IsEmpty()
{
    if (WorkOrderNumber == "" && ProductionLineNumber == "" && ProductionItemEan == "" && ProductionItemSku == "" && ProductionBatchNo == "" && WorkOrderQuantity == 0)
    {
        return 1;
    }
    else if(WorkOrderNumber != "" && ProductionLineNumber != "" && ProductionItemEan != "" && ProductionItemSku != "" && ProductionBatchNo != "" && WorkOrderQuantity != 0)
    {
        return 0;
    }
    else
    {
        return 999;
    }
}
void ProductionData::CopyData(ProductionData& InputData)
{
    WorkOrderNumber = InputData.WorkOrderNumber;
    WorkOrderQuantity = InputData.WorkOrderQuantity;
    ProductionLineNumber = InputData.ProductionLineNumber;
    ProductionItemEan = InputData.ProductionItemEan;
    ProductionItemSku = InputData.ProductionItemSku;
    ProductionBatchNo = InputData.ProductionBatchNo;
    
}