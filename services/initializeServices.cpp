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
    shipmentService = new ShipmentService(shipments);
    clientService = new ClientService(clients);
    employeeService = new EmployeeService(employees);
    connectionService = new ConnectionService(connections);
    shipmentManagerService = new ShipmentManagerService(shipmentManagers);
    transportService = new TransportService(transports);
    distributionCenterService = new DistributionCenterService(distributionCenters, distributionNetwork);
    
    // Cargar centros de distribucion de ejemplo
    distributionCenterService->loadMockCenters();
    
    // Cargar conexiones entre centros
    distributionCenterService->loadMockConnections();
}
