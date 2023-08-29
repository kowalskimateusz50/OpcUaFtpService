#pragma warning(disable : 4996)

#include <stdio.h>
#include "open62541.h"
#include <iostream>
#include <windows.h>
#include <wininet.h>
#include <tchar.h>
#include <string.h>
#include "ProductionData.hpp"
#include "WriteDataToPLC.hpp"

/* Define Server Adress(TODO: as loadable parameter)*/
#define SERVER_ADRESS "opc.tcp://192.168.10.10:4840"

int main(void) {

    /* Define some production data dummy structure*/
    ProductionData ProdData;
    /* Clear defined data structure */
    ProdData.ClearData();

    /* Definie PLC write object*/
    WriteDataToPLC PLC;

    /* Initialize server connection */
    std::cout << "\PLC.InitOpcUaServerConnection() function starting: ";
    PLC.InitOpcUaServerConnection(SERVER_ADRESS);

    /* Testing decision loop */
    int TestUserDecision = 0;

    while (TestUserDecision != 999) {
        std::cout << "\n 1. Write test data to PLC \n2. Clear data on PLC \nDecision: ";
        std::cin >> TestUserDecision;

        /* Write test production data to PLC (Simulation of start production batch) */
        if (TestUserDecision == 1) {
            ProdData.TestInputData();
            PLC.Write(ProdData);
        }

        /* Clear data on PLC (simulation of end production data batch) */
        if (TestUserDecision == 2) {
            ProdData.ClearData();
            PLC.Write(ProdData);
        }
    }
    /* Clean Up after OPC UA connections */
    PLC.CleanUp();

    system("pause");
    return 0;
}
