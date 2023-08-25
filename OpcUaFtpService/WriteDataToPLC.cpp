/* Definitions of class WriteDataToPLC members */
#pragma warning(disable : 4996)
#include "WriteDataToPLC.hpp"

/*
* Initialize connection with OPC UA Server
* @param: string server adress 
* @return: Server initialization status code 
*/
int WriteDataToPLC::InitOpcUaServerConnection(std::string ServerAdress)
{
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
    else
    {
        std::cout << "\nLog: OpcUa Server connection initialization successful: ";
    }
    /* Save server connection status */
    ServerConnectionStatus = (int)retval;

    return 0;
}

int WriteDataToPLC::Write(int16_t ValueToWrite)
{
    int ret;

    UA_Int16 WriteValue = ValueToWrite;

    std::cout << "\nWrite to PLC function CALL, variable value is: " << ValueToWrite << std::endl;
    /* Read the value attribute of the node. UA_Client_readValueAttribute is a
     * wrapper for the raw read service available as UA_Client_Service_read. */
    UA_Variant value; /* Variants can hold scalar values and arrays of any type */
    UA_Variant_init(&value);
    UA_Variant_setScalar(&value, &WriteValue, &UA_TYPES[UA_TYPES_INT16]);
    /* NodeId of the variable holding the current time */
    const UA_NodeId nodeId = UA_NODEID_STRING(3, (char*)"\"dbOpcUaTest\".\"OpcInt\"");
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

void WriteDataToPLC::CleanUp()
{
    UA_Client_delete(client);
}