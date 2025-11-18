#include "mockData.h"
#include "storage.h"
#include <iostream>

// Mock data definitions - now using storage lists
Package pkg1(1, 10.5, 1, 2.0);
Package pkg2(2, 15.0, 2, 3.5);
Package pkg3(3, 8.0, 1, 1.5);

Shipment ship1(1, "In Transit", 50.0, 1, 100.0, 10.0, 1, 1, {pkg1, pkg2}, 1, 2, 1, time(nullptr), time(nullptr), time(nullptr), time(nullptr));
Shipment ship2(2, "Delivered", 75.0, 2, 150.0, 15.0, 2, 2, {pkg3}, 2, 3, 2, time(nullptr), time(nullptr), time(nullptr), time(nullptr));

ShipmentManager sm1(1, 1, {}, 1);
ShipmentManager sm2(2, 2, {}, 2);

Transport trans1(1, "Truck", 1000.0);
Transport trans2(2, "Van", 500.0);

Client client1(1, "John Doe");
Client client2(2, "Jane Smith");

Connection conn1(1, 1, 2, 50.0);
Connection conn2(2, 2, 3, 75.0);

Employee emp1(1, "Alice", 1);
Employee emp2(2, "Bob", 2);

DistributionCenter dc1("DC1", "Center A", "City A", 100, 50, 10, std::vector<Employee>{emp1}, std::vector<Connection>{conn1}, std::vector<Package>{pkg1});
DistributionCenter dc2("DC2", "Center B", "City B", 200, 75, 15, std::vector<Employee>{emp2}, std::vector<Connection>{conn2}, std::vector<Package>{pkg2, pkg3});

DistributionCenterManager manager1;
DistributionCenterManager manager2;

void initializeMockData() {
    // Push packages to storage
    packages.push(pkg1);
    packages.push(pkg2);
    packages.push(pkg3);

    // Push shipments to storage
    shipments.push(ship1);
    shipments.push(ship2);

    // Push shipment managers to storage
    shipmentManagers.push(sm1);
    shipmentManagers.push(sm2);

    // Push transports to storage
    transports.push(trans1);
    transports.push(trans2);

    // Push clients to storage
    clients.push(client1);
    clients.push(client2);

    // Push connections to storage
    connections.push(conn1);
    connections.push(conn2);

    // Push employees to storage
    employees.push(emp1);
    employees.push(emp2);

    // Push distribution centers to storage
    distributionCenters.push(dc1);
    distributionCenters.push(dc2);

    // Push distribution center managers to storage
    distributionCenterManagers.push(manager1);
    distributionCenterManagers.push(manager2);

    // Initialize distribution center managers
    manager1.createDistributionCenter(1, "Center A", "City A", 100, 50, 10);
    manager1.createDistributionCenter(2, "Center B", "City B", 200, 75, 15);
    manager2.createDistributionCenter(3, "Center C", "City C", 150, 60, 12);
}
