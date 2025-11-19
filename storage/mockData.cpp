#include "mockData.h"
#include "storage.h"
#include <iostream>

// Global mock data instances
Package pkg1(1, 10.0, 1, 2.5);
Package pkg2(2, 15.0, 2, 3.5);
Package pkg3(3, 8.0, 1, 1.5);

// Mock shipments data
Employee emp1(1, "Alice", 1);
Employee emp2(2, "Bob", 2);

Connection conn1(1, 1, 2, 50.0);
Connection conn2(2, 2, 3, 75.0);

ShipmentManager sm1(1, 1, List(), 1);
ShipmentManager sm2(2, 2, List(), 2);

Transport trans1(1, "Truck", 1000.0);
Transport trans2(2, "Van", 500.0);

Client client1(1, "John Doe");
Client client2(2, "Jane Smith");

void initializeMockData() {
    std::cout << "Initializing mock data..." << std::endl;
    
    // Create employee lists
    List empList1;
    empList1.push(std::any(emp1));
    
    List empList2;
    empList2.push(std::any(emp2));
    
    // Create connection lists
    List connList1;
    connList1.push(std::any(conn1));
    
    List connList2;
    connList2.push(std::any(conn2));
    
    // Create package lists
    List pkgList1;
    pkgList1.push(std::any(pkg1));
    
    List pkgList2;
    pkgList2.push(std::any(pkg2));
    pkgList2.push(std::any(pkg3));
    
    // Create distribution centers with List parameters
    DistributionCenter dc1("DC1", "Center A", "City A", 100, 50, 10, empList1, connList1, pkgList1);
    DistributionCenter dc2("DC2", "Center B", "City B", 200, 75, 15, empList2, connList2, pkgList2);
    
    // Create package lists for shipments
    List pkgListShip1;
    pkgListShip1.push(std::any(pkg1));
    pkgListShip1.push(std::any(pkg2));
    
    List pkgListShip2;
    pkgListShip2.push(std::any(pkg3));
    
    List pkgListShip3;
    pkgListShip3.push(std::any(pkg3));
    
    // Create shipments using correct constructor with string IDs
    Shipment ship1(1, "In Transit", 50.0, 1, 100.0, 10.0, 1, "BUE", pkgListShip1, "BUE", "MZA", 1, time(nullptr), time(nullptr), time(nullptr), time(nullptr));
    Shipment ship2(2, "Delivered", 75.0, 2, 150.0, 15.0, 2, "BUE", pkgListShip2, "BUE", "MZA", 2, time(nullptr), time(nullptr), time(nullptr), time(nullptr));
    
    DistributionCenterManager* manager = new DistributionCenterManager();
    
   // Initialize distribution center managers BEFORE pushing
    manager->createDistributionCenter("B", "Center B", "City B", 200, 75, 15);

    manager->createDistributionCenter("CBA", "Cordoba Center", "Cordoba", 300, 10, 9);
    manager->createDistributionCenter("MZA", "Mendoza Center", "Mendoza", 250, 12, 13);
    manager->createDistributionCenter("BUE", "Buenos Aires Center", "Buenos Aires", 400, 0.01, 12);
    manager->createDistributionCenter("ROS", "Rosario Center", "Rosario", 200, 5, 8);
    manager->createDistributionCenter("TUC", "Tucuman Center", "Tucuman", 180, 4, 6);
    manager->createDistributionCenter("SLA", "Salta Center", "Salta", 160, 2, 5);

    manager->relateDistributionCenter("CBA", "MZA", 900);   // Cordoba - Mendoza
    manager->relateDistributionCenter("CBA", "BUE", 700);   // Cordoba - Buenos Aires
    manager->relateDistributionCenter("CBA", "ROS", 400);   // Cordoba - Rosario
    manager->relateDistributionCenter("MZA", "BUE", 1100);  // Mendoza - Buenos Aires
    manager->relateDistributionCenter("BUE", "ROS", 300);   // Buenos Aires - Rosario
    manager->relateDistributionCenter("TUC", "CBA", 550);   // Tucuman - Cordoba
    manager->relateDistributionCenter("TUC", "SLA", 300);   // Tucuman - Salta
    manager->relateDistributionCenter("SLA", "CBA", 800);   // Salta - Cordoba
    
    distributionCenterManagers.push(std::any(manager));
    
    packages.push(std::any(pkg1));
    packages.push(std::any(pkg2));
    packages.push(std::any(pkg3));
    
    shipments.push(std::any(new Shipment(ship1)));
    shipments.push(std::any(new Shipment(ship2)));
    
    employees.push(std::any(emp1));
    employees.push(std::any(emp2));
    
    connections.push(std::any(conn1));
    connections.push(std::any(conn2));
    
    shipmentManagers.push(std::any(sm1));
    shipmentManagers.push(std::any(sm2));
    
    transports.push(std::any(trans1));
    transports.push(std::any(trans2));
    
    clients.push(std::any(client1));
    clients.push(std::any(client2));
    
    List emptyConnVector;
    ShipmentManager sm1(1, 1, emptyConnVector, 1);
    ShipmentManager sm2(2, 2, emptyConnVector, 2);
    
    Transport trans1(1, "Truck", 1000.0);
    Transport trans2(2, "Van", 500.0);
    
    std::cout << "Mock data initialized successfully." << std::endl;
}