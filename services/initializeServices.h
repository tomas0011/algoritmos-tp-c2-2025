#ifndef INITIALIZE_SERVICES_H
#define INITIALIZE_SERVICES_H

#include "../storage/storage.h"
#include "package/packageService.h"
#include "shipment/shipmentService.h"
#include "client/clientService.h"
#include "employee/employeeService.h"
#include "connection/connectionService.h"
#include "transport/transportService.h"
#include "distributionCenter/distributionCenterService.h"
#include "../entities/distributionCenterManager/DistributionCenterManager.h"

// Global manager instances
extern DistributionCenterManager* distributionCenterManager;

// Global service instances
extern PackageService* packageService;
extern ShipmentService* shipmentService;
extern ClientService* clientService;
extern EmployeeService* employeeService;
extern ConnectionService* connectionService;
extern TransportService* transportService;
extern DistributionCenterService* distributionCenterService;


// Initialization function
void initializeServices();

// Cleanup function to free allocated services
void cleanupServices();

#endif // INITIALIZE_SERVICES_H
