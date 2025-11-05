#ifndef INITIALIZE_SERVICES_H
#define INITIALIZE_SERVICES_H

#include "package/packageService.h"
#include "shipment/shipmentService.h"
#include "../storage/storage.h"
#include "client/clientService.h"
#include "employee/employeeService.h"
#include "connection/connectionService.h"
#include "shipmentManager/shipmentManagerService.h"


// Global service instances
extern PackageService* packageService;
extern ShipmentService* shipmentService;
extern ClientService* clientService;
extern EmployeeService* employeeService;
extern ConnectionService* connectionService;
extern ShipmentManagerService* shipmentManagerService;


// Initialization function
void initializeServices();

#endif // INITIALIZE_SERVICES_H
