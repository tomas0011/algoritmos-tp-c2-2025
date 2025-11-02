#include "entities/distributionCenter/DistributionCenter.h"
#include "entities/employee/Employee.h"
#include "entities/managers/ShipmentManager.h"
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

    std::cout << "\n=== PROBANDO SHIPMENT MANAGER ===" << std::endl;
    ShipmentManager manager;
    manager.loadFromFile("./data/envios.txt");  // Cambié la ruta
    
    // Probar el cálculo de envíos por centro en un rango de fechas
    // Ejemplo: desde 1 de febrero hasta 31 de marzo de 2025
    auto result = manager.getShipmentsByCenter(20250201, 20250331);
    
    return 0;
}
