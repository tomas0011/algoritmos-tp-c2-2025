#ifndef MOCK_DATA_H
#define MOCK_DATA_H

#include "storage.h"

// Initialization functions
#include "../entities/distributionCenter/DistributionCenter.h"
#include "../entities/shipment/Shipment.h"
#include "../entities/employee/Employee.h"
#include "../entities/package/Package.h"

// Contadores globales para tracking de memoria
extern int allocated_shipments;
extern int allocated_managers;
extern int deleted_shipments;
extern int deleted_managers;

void initializeMockData();
void cleanupMockData();  // Nueva función para liberar memoria
void displayMemoryReport();  // Mostrar reporte de memoria

#endif // MOCK_DATA_H
