#include "entities/distributionCenter/DistributionCenter.h"
#include "entities/employee/Employee.h"
#include "entities/managers/ShipmentManager.h"
#include "entities/managers/DistributionCenterManager.h"
#include <iostream>
#include "storage/mockData.h"
// #include "services/initializeServices.h"  // No existe aún
// #include "bash/bash.h"  // No existe aún

int main() {
    // Instantiate all mock data
    // Note: Mock data is already defined in mockData.cpp and externed in mockData.h

    // Initialize mock data
    initializeMockData();

    // Initialize services
    // initializeServices();  // Comentado: no existe

    // Call the menu function from bash.cpp
    // showMenu();  // Comentado: no existe

    std::cout << "\n=== PROBANDO SHIPMENT MANAGER ===" << std::endl;
    ShipmentManager manager;
    manager.loadFromFile("./data/envios.txt");
    auto result = manager.getShipmentsByCenter(20250201, 20250331);
    
    // ======= PRUEBA DE DISTRIBUTION CENTER MANAGER =======
    std::cout << "\n\n========================================" << std::endl;
    std::cout << "=== GESTIÓN DE CENTROS DE DISTRIBUCIÓN ===" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    DistributionCenterManager dcManager;
    
    // 1. Cargar centros y conexiones
    dcManager.loadCentersFromFile("./data/centros.txt");
    dcManager.loadConnectionsFromFile("./data/conexiones.txt");
    
    // 2. Mostrar información de un centro específico
    std::cout << "\n--- Mostrando centro CBA ---" << std::endl;
    dcManager.displayCenter("CBA");
    
    // 3. Agregar un nuevo centro
    std::cout << "\n--- Agregando nuevo centro ---" << std::endl;
    DistributionCenter newCenter("TUC", "CentroTucuman", "Tucuman", 2500, 900, 60);
    if (dcManager.addCenter(newCenter)) {
        std::cout << "✓ Centro TUC agregado exitosamente" << std::endl;
    }
    
    // 4. Mostrar todos los centros ordenados
    std::cout << "\n--- Ordenando por capacidad ---" << std::endl;
    dcManager.listCentersSortedBy(SortCriterion::CAPACITY);
    
    std::cout << "\n--- Ordenando por paquetes diarios ---" << std::endl;
    dcManager.listCentersSortedBy(SortCriterion::DAILY_PACKAGES);
    
    std::cout << "\n--- Ordenando por empleados ---" << std::endl;
    dcManager.listCentersSortedBy(SortCriterion::EMPLOYEES);
    
    // 5. Calcular camino mínimo
    std::cout << "\n--- Calculando camino mínimo CBA -> BUE ---" << std::endl;
    auto [distance, path] = dcManager.shortestPath("CBA", "BUE");
    
    std::cout << "\n--- Calculando camino mínimo MZA -> ROS ---" << std::endl;
    dcManager.shortestPath("MZA", "ROS");
    
    // 6. Estadísticas del sistema
    dcManager.printStatistics();
    
    // 7. Eliminar un centro
    std::cout << "\n--- Eliminando centro TUC ---" << std::endl;
    if (dcManager.removeCenter("TUC")) {
        std::cout << "✓ Centro TUC eliminado exitosamente" << std::endl;
    }
    dcManager.printStatistics();
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "=== FIN DE PRUEBAS ===" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    return 0;
}
