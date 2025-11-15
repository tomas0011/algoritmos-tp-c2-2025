#include "initializeServices.h"

// Global service instances
PackageService* packageService = nullptr;
ShipmentService* shipmentService = nullptr;
ClientService* clientService = nullptr;
EmployeeService* employeeService = nullptr;
ConnectionService* connectionService = nullptr;
ShipmentManagerService* shipmentManagerService = nullptr;
DistributionCenterService* distributionCenterService = nullptr;

void initializeServices() {
    // Initialize services
    packageService = new PackageService(packages);
    shipmentService = new ShipmentService(shipments);
    clientService = new ClientService(clients);
    employeeService = new EmployeeService(employees);
    connectionService = new ConnectionService();
    shipmentManagerService = new ShipmentManagerService(shipmentManagers);
    distributionCenterService = new DistributionCenterService();
    
    // Cargar centros de distribución de ejemplo
    distributionCenterService->loadMockCenters();
    
    // Cargar conexiones entre centros
    distributionCenterService->loadMockConnections();
}
