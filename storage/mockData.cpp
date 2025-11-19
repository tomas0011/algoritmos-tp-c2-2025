#include "mockData.h"
#include "storage.h"
#include "../services/Connection/ConnectionService.h"
#include <iostream>
#include <utils/algorithms/parseDate/parseDate.h>

// Contadores de memoria
int allocated_shipments = 0;
int allocated_managers = 0;
int deleted_shipments = 0;
int deleted_managers = 0;

// Mock data definitions - now using storage lists
Package pkg1(1, "TV", 500, 2, 20);
Package pkg2(2, "Heladera", 800, 1, 150);
Package pkg3(3, "Lavaropas", 350, 1, 85);

// Mock shipments data
Employee emp1(1, "Alice", 1);
Employee emp2(2, "Bob", 2);

ShipmentManager sm1(1, 1, List(), 1);
ShipmentManager sm2(2, 2, List(), 2);

Transport trans1(1, "Truck", 500);
Transport trans2(2, "Van", 250);

Client client1(1, "John Doe");
Client client2(2, "Jane Smith");

void initializeMockData() {
    std::cout << "Initializing mock data..." << std::endl;
    
    // Create package lists
    List pkgList1;
    pkgList1.push(std::any(pkg1));
    
    List pkgList2;
    pkgList2.push(std::any(pkg2));
    pkgList2.push(std::any(pkg3));
    
    // Create package lists for shipments
    List pkgListShip1;
    pkgListShip1.push(std::any(pkg1));
    pkgListShip1.push(std::any(pkg2));

    List pkgListShip2;
    pkgListShip2.push(std::any(pkg3));

    List pkgListShip3;
    pkgListShip3.push(std::any(pkg1));
    pkgListShip3.push(std::any(pkg3));

    // Create shipments with unique IDs and varied data
    Shipment ship1(1, "Pending", 50.0, 1, 100.0, 10.0, 1, "BUE", pkgListShip1, "BUE", "MZA", 1, strToDate("10-11-2025"), -1, -1, -1);
    Shipment ship2(2, "In Transit", 75.0, 2, 150.0, 15.0, 2, "BUE", pkgListShip2, "BUE", "CBA", 2, strToDate("09-11-2025"), -1, -1, -1);
    Shipment ship3(3, "Delivered", 60.0, 1, 120.0, 12.0, 1, "CBA", pkgListShip3, "CBA", "MZA", 1, strToDate("08-11-2025"), strToDate("09-11-2025"), strToDate("10-11-2025"), strToDate("11-11-2025"));
    Shipment ship4(4, "Pending", 80.0, 3, 160.0, 18.0, 2, "BUE", pkgListShip1, "BUE", "BUE", 2, strToDate("11-11-2025"), -1, -1, -1);
    Shipment ship5(5, "In Transit", 45.0, 2, 90.0, 8.0, 1, "BUE", pkgListShip2, "BUE", "ROS", 1, strToDate("10-11-2025"), -1, -1, -1);
    Shipment ship6(6, "Pending", 55.0, 1, 110.0, 11.0, 2, "BUE", pkgListShip3, "BUE", "BUE", 2, strToDate("11-11-2025"), -1, -1, -1);
    Shipment ship7(7, "Delivered", 70.0, 2, 140.0, 14.0, 1, "BUE", pkgListShip1, "BUE", "CBA", 1, strToDate("07-11-2025"), strToDate("08-11-2025"), strToDate("09-11-2025"), strToDate("10-11-2025"));
    Shipment ship8(8, "In Transit", 65.0, 3, 130.0, 13.0, 2, "BUE", pkgListShip2, "BUE", "TUC", 2, strToDate("09-11-2025"), -1, -1, -1);
    Shipment ship9(9, "Pending", 40.0, 1, 80.0, 7.0, 1, "BUE", pkgListShip3, "BUE", "SAL", 1, strToDate("11-11-2025"), -1, -1, -1);
    Shipment ship10(10, "Pending", 90.0, 2, 180.0, 20.0, 2, "SAL", pkgListShip1, "SAL", "CBA", 2, strToDate("10-11-2025"), -1, -1, -1);
    
    // Crear ConnectionService primero
    ConnectionService* connService = new ConnectionService(connections);
    
    DistributionCenterManager* manager = new DistributionCenterManager(connService);
    allocated_managers++;  // Trackear allocación
    
    // Initialize distribution center managers BEFORE pushing

    manager->createDistributionCenter("CBA", "Cordoba Center", "Cordoba", 300, 10, 9);
    manager->createDistributionCenter("MZA", "Mendoza Center", "Mendoza", 250, 12, 13);
    manager->createDistributionCenter("BUE", "Buenos Aires Center", "Buenos Aires", 400, 1, 12);
    manager->createDistributionCenter("ROS", "Rosario Center", "Rosario", 200, 5, 8);
    manager->createDistributionCenter("TUC", "Tucuman Center", "Tucuman", 180, 4, 6);
    manager->createDistributionCenter("SAL", "Salta Center", "Salta", 160, 2, 5);

    manager->relateDistributionCenter("CBA", "MZA", 900);   // Cordoba - Mendoza
    manager->relateDistributionCenter("CBA", "BUE", 700);   // Cordoba - Buenos Aires
    manager->relateDistributionCenter("CBA", "ROS", 400);   // Cordoba - Rosario
    manager->relateDistributionCenter("MZA", "BUE", 1100);  // Mendoza - Buenos Aires
    manager->relateDistributionCenter("BUE", "ROS", 300);   // Buenos Aires - Rosario
    manager->relateDistributionCenter("TUC", "CBA", 550);   // Tucuman - Cordoba
    manager->relateDistributionCenter("TUC", "SAL", 300);   // Tucuman - Salta
    manager->relateDistributionCenter("SAL", "CBA", 800);   // Salta - Cordoba
    
    distributionCenterManagers.push(std::any(manager));
    
    packages.push(std::any(pkg1));
    packages.push(std::any(pkg2));
    packages.push(std::any(pkg3));
    
    shipments.push(std::any(new Shipment(ship1)));
    shipments.push(std::any(new Shipment(ship2)));
    shipments.push(std::any(new Shipment(ship3)));
    shipments.push(std::any(new Shipment(ship4)));
    shipments.push(std::any(new Shipment(ship5)));
    shipments.push(std::any(new Shipment(ship6)));
    shipments.push(std::any(new Shipment(ship7)));
    shipments.push(std::any(new Shipment(ship8)));
    shipments.push(std::any(new Shipment(ship9)));
    shipments.push(std::any(new Shipment(ship10)));
    allocated_shipments += 10;  // Trackear las 10 allocaciones
    
    employees.push(std::any(emp1));
    employees.push(std::any(emp2));
    
    shipmentManagers.push(std::any(sm1));
    shipmentManagers.push(std::any(sm2));
    
    transports.push(std::any(trans1));
    transports.push(std::any(trans2));
    
    clients.push(std::any(client1));
    clients.push(std::any(client2));
    
    std::cout << "Mock data initialized successfully." << std::endl;
}

void cleanupMockData() {
    std::cout << "\n=== INICIANDO LIMPIEZA DE MEMORIA ===" << std::endl;
    std::cout << "Liberando objetos creados dinamicamente..." << std::endl;
    
    // Liberar shipments (creados con new)
    Node* current = shipments.getHead();
    while (current != nullptr) {
        try {
            Shipment* shipment = std::any_cast<Shipment*>(current->getData());
            std::cout << "  -> Liberando Shipment ID: " << shipment->getId() << std::endl;
            delete shipment;
            deleted_shipments++;
        } catch (const std::bad_any_cast&) {}
        current = current->getNext();
    }
    
    // Liberar distribution center managers (creados con new)
    current = distributionCenterManagers.getHead();
    while (current != nullptr) {
        try {
            DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(current->getData());
            std::cout << "  -> Liberando DistributionCenterManager (" << manager->getDistributionCentersCount() << " centros)" << std::endl;
            delete manager;
            deleted_managers++;
        } catch (const std::bad_any_cast&) {}
        current = current->getNext();
    }
    
    std::cout << "\n=== REPORTE DE LIMPIEZA COMPLETADO ===" << std::endl;
}

void displayMemoryReport() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "         REPORTE FINAL DE MEMORIA" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    std::cout << "Shipments:" << std::endl;
    std::cout << "  V Creados:  " << allocated_shipments << std::endl;
    std::cout << "  V Liberados: " << deleted_shipments << std::endl;
    std::cout << "  " << (allocated_shipments == deleted_shipments ? "OK SIN MEMORY LEAKS" : "!! POSIBLES LEAKS") << std::endl;
    
    std::cout << "\nDistribution Center Managers:" << std::endl;
    std::cout << "  V Creados:  " << allocated_managers << std::endl;
    std::cout << "  V Liberados: " << deleted_managers << std::endl;
    std::cout << "  " << (allocated_managers == deleted_managers ? "OK SIN MEMORY LEAKS" : "!! POSIBLES LEAKS") << std::endl;
    
    int total_created = allocated_shipments + allocated_managers;
    int total_deleted = deleted_shipments + deleted_managers;
    
    std::cout << "\nTOTAL:" << std::endl;
    std::cout << "  * Objetos dinamicos creados: " << total_created << std::endl;
    std::cout << "  * Objetos dinamicos liberados: " << total_deleted << std::endl;
    
    if (total_created == total_deleted) {
        std::cout << "  OK MEMORIA COMPLETAMENTE LIBERADA" << std::endl;
        std::cout << "  !! NO HAY MEMORY LEAKS DETECTADOS" << std::endl;
    } else {
        std::cout << "  !! ATENCION: POSIBLES MEMORY LEAKS" << std::endl;
        std::cout << "  !! Objetos no liberados: " << (total_created - total_deleted) << std::endl;
    }
    
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Nota: Las listas globales y objetos de stack se liberan" << std::endl;
    std::cout << "automaticamente al terminar el programa." << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}
