#include "initializeServices.h"

// Global service instances
PackageService* packageService = nullptr;
ShipmentService* shipmentService = nullptr;

void initializeServices() {
    // Initialize services
    packageService = new PackageService(packages);
    shipmentService = new ShipmentService(shipments);
}
