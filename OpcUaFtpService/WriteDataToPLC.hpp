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
	int Write(int16_t ValueToWrite);
	void CleanUp();

};
