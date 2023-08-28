#include "ProductionData.hpp"

/* Method to simulate Production data input from future csv file (only for testing purpose) */
void ProductionData::TestInputData() {
    /* Input of work order number */
    ProductionData::WorkOrderNumber = "00010xxxx877";
    
    /* Input of production line number */
    ProductionData::ProductionLineNumber = "I4AL01";

    /* Input of production item ean */
    ProductionData::ProductionItemEan = "7622100597018";

    /* Input of production item sku */
    ProductionData::ProductionItemSku = "DK003095.01";

    /* Input of production batch no */
    ProductionData::ProductionBatchNo = "LG-4573271";

    /* Input of work order quantity */
    ProductionData::WorkOrderQuantity = 1770;
}

/* Method to clearing production Data structure */
void ProductionData::ClearData() {
    /* Clear work order number */
    ProductionData::WorkOrderNumber = "";

    /* Clear production line number */
    ProductionData::ProductionLineNumber = "";

    /* Clear production item ean */
    ProductionData::ProductionItemEan = "";

    /* Clear production item sku */
    ProductionData::ProductionItemSku = "";

    /* Clear production batch no */
    ProductionData::ProductionBatchNo = "";

    /* Clear work order quantity */
    ProductionData::WorkOrderQuantity = 0;
}
