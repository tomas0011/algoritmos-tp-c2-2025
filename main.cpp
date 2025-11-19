#include "entities/distributionCenter/DistributionCenter.h"
#include "entities/employee/Employee.h"
#include <iostream>
#include "storage/mockData.h"
#include "services/InitializeServices.h"
#include "bash/bash.h"

int main() {
    // Instantiate all mock data
    // Note: Mock data is already defined in mockData.cpp and externed in mockData.h

    // Initialize services first (needed by mockData)
    initializeServices();
    
    // Initialize mock data (uses services)
    initializeMockData();

    // Call the menu function from bash.cpp
    showMenu();

    // Cleanup resources
    cleanupServices();
    cleanupMockData();
    
    // Mostrar reporte final de memoria
    displayMemoryReport();

    return 0;
}
