#pragma once
#include <iostream>
#include <string.h>
#include "open62541.h"
#include "ProductionData.hpp"

class WriteDataToPLC {
private:
	UA_Client* client; // Client structure pointer 
	int ServerConnectionStatus;

public:

	int InitOpcUaServerConnection(std::string ServerAdress); //Init server connection function
	void StringToUAString(std::string& StrToConvert, UA_String& StrConverted);
	int Write(ProductionData& Data);
	void ManualInputData(ProductionData& Data);
	void CleanUp();

};
