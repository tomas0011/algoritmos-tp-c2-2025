#include "initializeServices.h"

// Global service instances
PackageService* packageService = nullptr;
ShipmentService* shipmentService = nullptr;
ClientService* clientService = nullptr;
EmployeeService* employeeService = nullptr;
ConnectionService* connectionService = nullptr;
ShipmentManagerService* shipmentManagerService = nullptr;
// Crear la lista del módulo
static List connectionsList;

void initializeServices() {
    // Initialize services
    packageService = new PackageService(packages);
    shipmentService = new ShipmentService(shipments);
    clientService = new ClientService(clients);
    employeeService = new EmployeeService(employees);
    connectionService = new ConnectionService(connectionsList);
    shipmentManagerService = new ShipmentManagerService(shipmentManagers);
}
