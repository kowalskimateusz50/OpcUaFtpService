#include <stdio.h>
#include "open62541.h"
#include <iostream>
#include <windows.h>
#include <wininet.h>
#include <tchar.h>
#include <string.h>
#include "ProductionData.hpp"
#include "WriteDataToPLC.hpp"

#pragma warning(disable : 4996)

/* Define Server Adress(TODO: as loadable parameter)*/
#define SERVER_ADRESS "opc.tcp://192.168.10.10:4840"

int main(void) {
    //Test
    int ReadValue = 9999;

    UA_Client* client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));
    UA_StatusCode retval = UA_Client_connect(client, SERVER_ADRESS);

    if (retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        return (int)retval;
    }

    /* Read the value attribute of the node. UA_Client_readValueAttribute is a
     * wrapper for the raw read service available as UA_Client_Service_read. */
    UA_Variant value; /* Variants can hold scalar values and arrays of any type */
    UA_Variant_init(&value);

    /* NodeId of the variable holding the current time */
    const UA_NodeId nodeId = UA_NODEID_STRING(3, (char*)"\"dbOpcUaTest\".\"OpcInt\"");
    retval = UA_Client_readValueAttribute(client, nodeId, &value);

    if (retval == UA_STATUSCODE_GOOD &&
        UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_INT16])) {
        ReadValue = *(UA_Int16*)value.data;
        // UA_DateTime raw_date = *(UA_DateTime *) value.data;
        // UA_DateTimeStruct dts = UA_DateTime_toStruct(raw_date);
        // UA_LOG_I/NFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "date is: %u-%u-%u %u:%u:%u.%03u\n",
                   //  dts.day, dts.month, dts.year, dts.hour, dts.min, dts.sec, dts.milliSec);
        std::cout << "read from server is : " << ReadValue << std::endl;
    }

    /* Clean up */
    UA_Variant_deleteMembers(&value);
    UA_Client_delete(client); /* Disconnects the client internally */

    system("pause");
    return 0;
}
