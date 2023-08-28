/* Definitions of class WriteDataToPLC members */
#pragma warning(disable : 4996)
#include "WriteDataToPLC.hpp"

/*
* Initialize connection with OPC UA Server
* @param: string server adress 
* @return: Server initialization status code 
*/
int WriteDataToPLC::InitOpcUaServerConnection(std::string ServerAdress) {
    /* Convert server adress to c_tring */
    char* CstrServerAdress = new char[ServerAdress.length() + 1];
    strcpy_s(CstrServerAdress, ServerAdress.length() + 1, ServerAdress.c_str());

    client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));
    UA_StatusCode retval = UA_Client_connect(client, CstrServerAdress);

    /* Check server connection status */
    if (retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        std::cout << "\nLog: OpcUa Server connection initialization failed code: " << (int)retval;
        /* Save server connection status */
        ServerConnectionStatus = (int)retval;
        return (int)retval;
    }
    else {
        std::cout << "\nLog: OpcUa Server connection initialization successful: ";
    }
    /* Save server connection status */
    ServerConnectionStatus = (int)retval;

    return 0;
}

/* Function to convert input std::String type to UA_String type
* @param: StrToConvert -> Input string to convert
* @param: StrConverted -> Output string converted
* @return: status of conversion
*/

void WriteDataToPLC::StringToUAString(std::string& StrToConvert, UA_String& StrConverted) {

    /* Write length of input string */
    StrConverted.length = StrToConvert.length();

    /* Define temp char's array */
    char* ConvertArray = new char[StrToConvert.length() + 1];
    UA_Byte* ConvertByteArray = new UA_Byte[StrToConvert.length() + 1];

    // copying the contents of the
    // string to char array
    strcpy_s(ConvertArray, StrToConvert.length() + 1, StrToConvert.c_str());

    for (int i = 0; i < StrToConvert.length(); i++) {
        ConvertByteArray[i] = (UA_Byte)(ConvertArray[i]);
    }
    StrConverted.data = ConvertByteArray;
}

int WriteDataToPLC::Write(ProductionData& Data) {

    int ret; /* Error code handler */

    /*------------------- Write Work order number -------------------------------*/
    UA_String UaWorkOrderNo; /* Write string variable */
    UA_Variant WorkOrderNoValue; /* Variants can hold scalar values and arrays of any type */

    /* Convert string data type to UA_String */
    StringToUAString(Data.WorkOrderNumber, UaWorkOrderNo);
    UA_Variant_init(&WorkOrderNoValue);
    UA_Variant_setScalar(&WorkOrderNoValue, &UaWorkOrderNo, &UA_TYPES[UA_TYPES_STRING]);

    /* NodeId of the variable holding the work order number */
    const UA_NodeId WorkOrderNoNodeId = UA_NODEID_STRING(3, (char*)"\"ProductionData\".\"ProductionData\".\"WorkOrderNo\"");
    ret = UA_Client_writeValueAttribute(client, WorkOrderNoNodeId, &WorkOrderNoValue);

    std::cout << "\nLOG: Work order number write result: " << (int)ret << std::endl;
    UA_Variant_deleteMembers(&WorkOrderNoValue);

    /*------------------- Write Porduction line number ----------------*/
    UA_String UaProdLineNo; /* Write string variable */
    UA_Variant ProdLineNoValue; /* Variants can hold scalar values and arrays of any type */

    /* Convert string data type to UA_String */
    StringToUAString(Data.ProductionLineNumber, UaProdLineNo);
    UA_Variant_init(&ProdLineNoValue);
    UA_Variant_setScalar(&ProdLineNoValue, &UaProdLineNo, &UA_TYPES[UA_TYPES_STRING]);

    /* NodeId of the variable holding the production line number */
    const UA_NodeId ProdLineNoNodeId = UA_NODEID_STRING(3, (char*)"\"ProductionData\".\"ProductionData\".\"ProductionLineNumber\"");
    ret = UA_Client_writeValueAttribute(client, ProdLineNoNodeId, &ProdLineNoValue);

    std::cout << "\nLOG: Prod line number write result: " << (int)ret << std::endl;
    UA_Variant_deleteMembers(&ProdLineNoValue);

    /*------------------- Write Porduction item ean ----------------*/
    UA_String UaProdItemEan; /* Write string variable */
    UA_Variant ProdItemEanValue; /* Variants can hold scalar values and arrays of any type */

    /* Convert string data type to UA_String */
    StringToUAString(Data.ProductionItemEan, UaProdItemEan);
    UA_Variant_init(&ProdItemEanValue);
    UA_Variant_setScalar(&ProdItemEanValue, &UaProdItemEan, &UA_TYPES[UA_TYPES_STRING]);

    /* NodeId of the variable holding the production item ean */
    const UA_NodeId ProdItemEanNodeId = UA_NODEID_STRING(3, (char*)"\"ProductionData\".\"ProductionData\".\"EAN\"");
    ret = UA_Client_writeValueAttribute(client, ProdItemEanNodeId, &ProdItemEanValue);

    std::cout << "\nLOG: Prod line item ean write result: " << (int)ret << std::endl;
    UA_Variant_deleteMembers(&ProdItemEanValue);
    return ret;

    /*------------------- Write Porduction item sku ----------------*/
    UA_String UaProdItemSku; /* Write string variable */
    UA_Variant ProdItemSkuValue; /* Variants can hold scalar values and arrays of any type */

    /* Convert string data type to UA_String */
    StringToUAString(Data.ProductionItemSku, UaProdItemSku);
    UA_Variant_init(&ProdItemSkuValue);
    UA_Variant_setScalar(&ProdItemSkuValue, &UaProdItemSku, &UA_TYPES[UA_TYPES_STRING]);

    /* NodeId of the variable holding the production item sku */
    const UA_NodeId ProdItemSkuNodeId = UA_NODEID_STRING(3, (char*)"\"ProductionData\".\"ProductionData\".\"SKU_code\"");
    ret = UA_Client_writeValueAttribute(client, ProdItemSkuNodeId, &ProdItemSkuValue);

    std::cout << "\nLOG: Prod line item sku write result: " << (int)ret << std::endl;
    UA_Variant_deleteMembers(&ProdItemSkuValue);

    /*------------------- Write Porduction batch number ----------------*/
    UA_String UaProdBatchNo; /* Write string variable */
    UA_Variant ProdBatchNoValue; /* Variants can hold scalar values and arrays of any type */

    /* Convert string data type to UA_String */
    StringToUAString(Data.ProductionBatchNo, UaProdBatchNo);
    UA_Variant_init(&ProdBatchNoValue);
    UA_Variant_setScalar(&ProdBatchNoValue, &UaProdBatchNo, &UA_TYPES[UA_TYPES_STRING]);

    /* NodeId of the variable holding the production item sku */
    const UA_NodeId ProdBatchNoNodeId = UA_NODEID_STRING(3, (char*)"\"ProductionData\".\"ProductionData\".\"BatchNo\"");
    ret = UA_Client_writeValueAttribute(client, ProdBatchNoNodeId, &ProdBatchNoValue);

    std::cout << "\nLOG: Prod batch number write result: " << (int)ret << std::endl;
    UA_Variant_deleteMembers(&ProdBatchNoValue);

    /*------------------- Write Work order quantity --------------*/
    UA_Int16 UaWorkOrderQuantity; /* Write string variable */
    UA_Variant WorkOrderQuantityValue; /* Variants can hold scalar values and arrays of any type */

    UA_Variant_init(&WorkOrderQuantityValue);
    UA_Variant_setScalar(&WorkOrderQuantityValue, &UaWorkOrderQuantity, &UA_TYPES[UA_TYPES_INT16]);

    /* NodeId of the variable holding the production item sku */
    const UA_NodeId WorkOrderQuantityId = UA_NODEID_STRING(3, (char*)"\"ProductionData\".\"ProductionData\".\"BatchNo\"");
    ret = UA_Client_writeValueAttribute(client, WorkOrderQuantityId, &WorkOrderQuantityValue);

    std::cout << "\nLOG: Work order quantity write result: " << (int)ret << std::endl;
    UA_Variant_deleteMembers(&WorkOrderQuantityValue);

    return ret;
}

/*
* Clean up after OPC UA client connection
* @param: NULL
* @return: NULL
*/

void WriteDataToPLC::CleanUp(){
    UA_Client_delete(client);
}

/* Function only for manual test purpose 
* @param: Production data
* @return: NULL
*/



