#include "mockData.h"
#include "storage.h"
#include <iostream>
#include <utils/algorithms/parseDate/parseDate.h>

// Mock data definitions - now using storage lists
Package pkg1(1, "medias", 10.5, 1, 2.0);
Package pkg2(2, "celular", 15.0, 2, 3.5);
Package pkg3(3, "campera", 8.0, 1, 1.5);

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
    
    DistributionCenterManager* manager = new DistributionCenterManager();
    
   // Initialize distribution center managers BEFORE pushing
    manager->createDistributionCenter("B", "Center B", "City B", 200, 75, 15);

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
    
    std::cout << "Mock data initialized successfully." << std::endl;
}
