#pragma once
#include <iostream>
#include <string.h>
#include "open62541.h"
#include "ProductionData.hpp"

class WriteDataToPLC {
private:
	UA_Client* client; /* Client structure pointer */ 
	int ServerConnectionStatus; /* Server connection status */ 

public:

	int  InitOpcUaServerConnection(std::string ServerAdress); /* Init server connection function */
	void StringToUAString(std::string& StrToConvert, UA_String& StrConverted); /* Convert std::string type to UA_String type */
	int  Write(ProductionData& Data); /* Write production data data to PLC Controller */
	void CleanUp(); /* Cleaning after OPC UA Server connection session */

};
