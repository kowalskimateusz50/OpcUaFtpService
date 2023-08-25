#include <iostream>
#include <string.h>
#include "open62541.h"
#include "ProductionData.hpp"

class WriteDataToPLC {
private:
	UA_Client* client; // Client structure pointer 


public:

	int InitOpcUaServerConnection(std::string ServerAdress); //Init server connection function
	int Write(ProductionData Data);
	void CleanUp();

};
