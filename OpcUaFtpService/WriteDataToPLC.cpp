/* Definitions of class WriteDataToPLC members */
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

    UA_Client* client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));
    UA_StatusCode retval = UA_Client_connect(client, CstrServerAdress);

    /* Check server connection status */
    if (retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        std::cout << "\nLog: OpcUa Server connection initialization failed code: " << (int)retval;
        return (int)retval;
    }

    std::cout << "\nLog: OpcUa Server connection initialization successful: ";
    return 0;
}

int WriteDataToPLC::Write(ProductionData Data)
{
    return 0;
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