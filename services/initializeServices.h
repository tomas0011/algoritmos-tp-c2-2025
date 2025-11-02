#ifndef INITIALIZE_SERVICES_H
#define INITIALIZE_SERVICES_H

#include "package/packageService.h"
#include "shipment/shipmentService.h"
#include "../storage/storage.h"

// Global service instances
extern PackageService* packageService;
extern ShipmentService* shipmentService;

// Initialization function
void initializeServices();

#endif // INITIALIZE_SERVICES_H
