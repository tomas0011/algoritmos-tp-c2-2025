#include "initializeServices.h"

// Global service instances
PackageService* packageService = nullptr;
ShipmentService* shipmentService = nullptr;
ClientService* clientService = nullptr;
EmployeeService* employeeService = nullptr;
ConnectionService* connectionService = nullptr;
TransportService* transportService = nullptr;
DistributionCenterService* distributionCenterService = nullptr;

void initializeServices() {
    // Initialize services
    packageService = new PackageService(packages);
    clientService = new ClientService(clients);
    employeeService = new EmployeeService(employees);
    connectionService = new ConnectionService(connections);
    transportService = new TransportService(transports);
    distributionCenterService = new DistributionCenterService(distributionCenters, distributionCenterManagers);
    shipmentService = new ShipmentService(transportService, distributionCenterService, shipments);
}

void cleanupServices() {
    // Free all allocated services
    delete packageService;
    delete shipmentService;
    delete clientService;
    delete employeeService;
    delete connectionService;
    delete transportService;
    delete distributionCenterService;
    
    // Reset pointers to nullptr
    packageService = nullptr;
    shipmentService = nullptr;
    clientService = nullptr;
    employeeService = nullptr;
    connectionService = nullptr;
    transportService = nullptr;
    distributionCenterService = nullptr;
}
