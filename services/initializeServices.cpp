#include "initializeServices.h"

// Global service instances
PackageService* packageService = nullptr;
ShipmentService* shipmentService = nullptr;
ClientService* clientService = nullptr;
EmployeeService* employeeService = nullptr;
ConnectionService* connectionService = nullptr;
ShipmentManagerService* shipmentManagerService = nullptr;
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
    shipmentManagerService = new ShipmentManagerService(shipmentManagers);
}
