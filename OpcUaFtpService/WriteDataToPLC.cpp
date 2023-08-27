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
    int ret;

    std::string WriteString = "TestWritee";

    std::cout << "\nWrite to PLC function CALL, string value is: " << WriteString << std::endl;

    UA_String WriteUaString;
    /* Convert string data type to UA_String */
    StringToUAString(WriteString, WriteUaString);

    UA_Variant value; /* Variants can hold scalar values and arrays of any type */

    UA_Variant_init(&value);
    UA_Variant_setScalar(&value, &WriteUaString, &UA_TYPES[UA_TYPES_STRING]);
    /* NodeId of the variable holding the current time */
    const UA_NodeId nodeId = UA_NODEID_STRING(3, (char*)"\"ProductionData\".\"ProductionData\".\"BatchNo\"");
    //const UA_NodeId nodeId = UA_NODEID_STRING(3, (char*)"\"ProductionData\".\"ProductionData\".\"BatchNo\"");
    ret = UA_Client_writeValueAttribute(client, nodeId, &value);

    std::cout << "\nLOG: Variable write result: " << (int)ret << std::endl;

    UA_Variant_deleteMembers(&value);

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

void WriteDataToPLC::ManualInputData(ProductionData& Data){
    /* Input of work order number */
    std::cout << "\nEnter Work Order Number: ";
    std::cin >> Data.WorkOrderNumber;
    /* Input of production line number */
    std::cout << "\nEnter Production Line Number: ";
    std::cin >> Data.ProductionLineNumber;
    /* Input of production item ean */
    std::cout << "\nEnter Production Item Ean: ";
    std::cin >> Data.ProductionItemEan;
    /* Input of production item sku */
    std::cout << "\nEnter Production Item Sku: ";
    std::cin >> Data.ProductionItemSku;
    /* Input of production batch no */
    std::cout << "\nEnter Production batch no: ";
    std::cin >> Data.ProductionBatchNo;

}

