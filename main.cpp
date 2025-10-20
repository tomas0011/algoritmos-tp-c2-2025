#include "entities/distributionCenter/DistributionCenter.h"
#include "entities/employee/Employee.h"
#include "entities/managers/ShipmentManager.h"
#include <iostream>

int main() {
    Employee employee1(1, "Tomas Vasquez", "123456");
    employee1.display();

    DistributionCenter distributionCenter1(
        1,
        "Correo Argentino - Pedro diaz",
        "Tesei",
        100,
        5
    );
    distributionCenter1.display();

    std::cout << "\n=== PROBANDO SHIPMENT MANAGER ===" << std::endl;
    ShipmentManager manager;
    manager.loadFromFile("./data/envios.txt");  // Cambié la ruta
    
    // Probar el cálculo de envíos por centro en un rango de fechas
    // Ejemplo: desde 1 de febrero hasta 31 de marzo de 2025
    auto result = manager.getShipmentsByCenter(20250201, 20250331);
    
    return 0;
}
