#include "mockData.h"
#include "storage.h"
#include <iostream>

// Mock data definitions - now using storage lists
Package pkg1(1, 10.5, 1, 2.0);
Package pkg2(2, 15.0, 2, 3.5);
Package pkg3(3, 8.0, 1, 1.5);

Shipment ship1(1, "In Transit", 50.0, 1, 100.0, 10.0, 1, 1, {pkg1, pkg2}, 1, 2, 1, time(nullptr), time(nullptr), time(nullptr), time(nullptr));
Shipment ship2(2, "Delivered", 75.0, 2, 150.0, 15.0, 2, 2, {pkg3}, 2, 3, 2, time(nullptr), time(nullptr), time(nullptr), time(nullptr));

ShipmentManager sm1;
ShipmentManager sm2;

Transport trans1(1, "Truck", 1000.0);
Transport trans2(2, "Van", 500.0);

Client client1(1, "John Doe");
Client client2(2, "Jane Smith");

Connection conn1(1, 1, 2, 50.0);
Connection conn2(2, 2, 3, 75.0);

Employee emp1(1, "Alice", 1);
Employee emp2(2, "Bob", 2);

// Usando el constructor simplificado: code, name, city, capacity, dailyPackages, employeeCount
DistributionCenter dc1("CEN1", "Center A", "City A", 100, 50, 10);
DistributionCenter dc2("CEN2", "Center B", "City B", 200, 75, 15);

// El nuevo DistributionCenterManager usa hash table y no se instancia así
// DistributionCenterManager manager1;
// DistributionCenterManager manager2;

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
    // distributionCenterManagers.push(manager1);
    // distributionCenterManagers.push(manager2);

    // Los managers nuevos no tienen createDistributionCenter así
    // El nuevo manager usa addCenter() con código único
}

// Display functions - now using storage lists
void displayMockPackages() {
    std::cout << "Mock Packages:" << std::endl;
    Node* current = packages.getHead();
    while (current != nullptr) {
        try {
            Package pkg = std::any_cast<Package>(current->getData());
            pkg.display();
        } catch (const std::bad_any_cast& e) {
            std::cout << "Error casting package" << std::endl;
        }
        current = current->getNext();
    }
}

void displayMockShipments() {
    std::cout << "Mock Shipments:" << std::endl;
    Node* current = shipments.getHead();
    while (current != nullptr) {
        try {
            Shipment ship = std::any_cast<Shipment>(current->getData());
            ship.display();
        } catch (const std::bad_any_cast& e) {
            std::cout << "Error casting shipment" << std::endl;
        }
        current = current->getNext();
    }
}

void displayMockShipmentManagers() {
    std::cout << "Mock Shipment Managers:" << std::endl;
    Node* current = shipmentManagers.getHead();
    while (current != nullptr) {
        try {
            ShipmentManager sm = std::any_cast<ShipmentManager>(current->getData());
            std::cout << "Total shipments: " << sm.getTotalShipments() << std::endl;
        } catch (const std::bad_any_cast& e) {
            std::cout << "Error casting shipment manager" << std::endl;
        }
        current = current->getNext();
    }
}

void displayMockTransports() {
    std::cout << "Mock Transports:" << std::endl;
    Node* current = transports.getHead();
    while (current != nullptr) {
        try {
            Transport trans = std::any_cast<Transport>(current->getData());
            trans.display();
        } catch (const std::bad_any_cast& e) {
            std::cout << "Error casting transport" << std::endl;
        }
        current = current->getNext();
    }
}

void displayMockClients() {
    std::cout << "Mock Clients:" << std::endl;
    Node* current = clients.getHead();
    while (current != nullptr) {
        try {
            Client client = std::any_cast<Client>(current->getData());
            client.display();
        } catch (const std::bad_any_cast& e) {
            std::cout << "Error casting client" << std::endl;
        }
        current = current->getNext();
    }
}

void displayMockConnections() {
    std::cout << "Mock Connections:" << std::endl;
    Node* current = connections.getHead();
    while (current != nullptr) {
        try {
            Connection conn = std::any_cast<Connection>(current->getData());
            conn.display();
        } catch (const std::bad_any_cast& e) {
            std::cout << "Error casting connection" << std::endl;
        }
        current = current->getNext();
    }
}

void displayMockDistributionCenters() {
    std::cout << "Mock Distribution Centers:" << std::endl;
    Node* current = distributionCenters.getHead();
    while (current != nullptr) {
        try {
            DistributionCenter dc = std::any_cast<DistributionCenter>(current->getData());
            dc.display();
        } catch (const std::bad_any_cast& e) {
            std::cout << "Error casting distribution center" << std::endl;
        }
        current = current->getNext();
    }
}

void displayMockDistributionCenterManagers() {
    std::cout << "Mock Distribution Center Managers:" << std::endl;
    std::cout << "Total managers: " << distributionCenterManagers.getSize() << std::endl;
}

void displayMockEmployees() {
    std::cout << "Mock Employees:" << std::endl;
    Node* current = employees.getHead();
    while (current != nullptr) {
        try {
            Employee emp = std::any_cast<Employee>(current->getData());
            emp.display();
        } catch (const std::bad_any_cast& e) {
            std::cout << "Error casting employee" << std::endl;
        }
        current = current->getNext();
    }
}
