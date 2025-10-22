#include "entities/distributionCenter/DistributionCenter.h"
#include "entities/employee/Employee.h"
#include <iostream>
#include "mocks/mockData.h"
#include "bash/bash.h"

int main() {
    // Instantiate all mock data
    // Note: Mock data is already defined in mockData.cpp and externed in mockData.h

    // Call the menu function from bash.cpp
    showMenu();

    return 0;
}
