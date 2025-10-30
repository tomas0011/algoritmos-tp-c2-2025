#include "entities/distributionCenter/DistributionCenter.h"
#include "entities/employee/Employee.h"
#include <iostream>
#include "storage/mockData.h"
#include "services/initializeServices.h"
#include "bash/bash.h"

int main() {
    // Instantiate all mock data
    // Note: Mock data is already defined in mockData.cpp and externed in mockData.h

    // Initialize mock data
    initializeMockData();

    // Initialize services
    initializeServices();

    // Call the menu function from bash.cpp
    showMenu();

    return 0;
}
