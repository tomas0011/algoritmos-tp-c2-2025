#include "initializeServices.h"

// Global manager instances
DistributionCenterManager* distributionCenterManager = nullptr;

// Global service instances
PackageService* packageService = nullptr;
ShipmentService* shipmentService = nullptr;
ClientService* clientService = nullptr;
EmployeeService* employeeService = nullptr;
ConnectionService* connectionService = nullptr;
TransportService* transportService = nullptr;
DistributionCenterService* distributionCenterService = nullptr;

void initializeServices() {
    // Initialize managers
    distributionCenterManager = new DistributionCenterManager(distributionCenterNetwork);

    // Initialize services
    packageService = new PackageService(packages);
    clientService = new ClientService(clients);
    employeeService = new EmployeeService(employees);
    connectionService = new ConnectionService(distributionCenterManager, connections);
    transportService = new TransportService(transports);
    distributionCenterService = new DistributionCenterService(
        connectionService,
        packageService,
        distributionCenterManager,
        distributionCenters,
        distributionCenterManagers);
    shipmentService = new ShipmentService(
        transportService,
        packageService,
        distributionCenterService,
        shipments);
}

void cleanupServices() {
    // Free all allocated services
    delete distributionCenterManager;
    delete packageService;
    delete shipmentService;
    delete clientService;
    delete employeeService;
    delete connectionService;
    delete transportService;
    delete distributionCenterService;
    
    // Reset pointers to nullptr
    distributionCenterManager = nullptr;
    packageService = nullptr;
    shipmentService = nullptr;
    clientService = nullptr;
    employeeService = nullptr;
    connectionService = nullptr;
    transportService = nullptr;
    distributionCenterService = nullptr;
}
