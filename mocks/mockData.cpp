#include "mockData.h"
#include <iostream>

// Mock data definitions
std::vector<Package> mockPackages = {
    Package(1, 10.5, 1, 2.0),
    Package(2, 15.0, 2, 3.5),
    Package(3, 8.0, 1, 1.5)
};

std::vector<Shipment> mockShipments = {
    Shipment(1, "In Transit", 50.0, 1, 100.0, 10.0, 1, 1, {mockPackages[0], mockPackages[1]}, 1, 2, 1, time(nullptr), time(nullptr), time(nullptr), time(nullptr)),
    Shipment(2, "Delivered", 75.0, 2, 150.0, 15.0, 2, 2, {mockPackages[2]}, 2, 3, 2, time(nullptr), time(nullptr), time(nullptr), time(nullptr))
};

std::vector<ShipmentManager> mockShipmentManagers = {
    ShipmentManager(1, 1, {}, 1),
    ShipmentManager(2, 2, {}, 2)
};

std::vector<Transport> mockTransports = {
    Transport(1, "Truck", 1000.0),
    Transport(2, "Van", 500.0)
};

std::vector<Client> mockClients = {
    Client(1, "John Doe"),
    Client(2, "Jane Smith")
};

std::vector<Connection> mockConnections = {
    Connection(1, 1, 2, 50.0),
    Connection(2, 2, 3, 75.0)
};

std::vector<DistributionCenter> mockDistributionCenters = {
    DistributionCenter(1, "Center A", "City A", 100, {}),
    DistributionCenter(2, "Center B", "City B", 200, {})
};

std::vector<Employee> mockEmployees = {
    Employee(1, "Alice", 1),
    Employee(2, "Bob", 2)
};

// Display functions
void displayMockPackages() {
    std::cout << "Mock Packages:" << std::endl;
    for (const auto& pkg : mockPackages) {
        pkg.display();
    }
}

void displayMockShipments() {
    std::cout << "Mock Shipments:" << std::endl;
    for (const auto& ship : mockShipments) {
        ship.display();
    }
}

void displayMockShipmentManagers() {
    std::cout << "Mock Shipment Managers:" << std::endl;
    for (const auto& sm : mockShipmentManagers) {
        sm.display();
    }
}

void displayMockTransports() {
    std::cout << "Mock Transports:" << std::endl;
    for (const auto& trans : mockTransports) {
        trans.display();
    }
}

void displayMockClients() {
    std::cout << "Mock Clients:" << std::endl;
    for (const auto& client : mockClients) {
        client.display();
    }
}

void displayMockConnections() {
    std::cout << "Mock Connections:" << std::endl;
    for (const auto& conn : mockConnections) {
        conn.display();
    }
}

void displayMockDistributionCenters() {
    std::cout << "Mock Distribution Centers:" << std::endl;
    for (const auto& dc : mockDistributionCenters) {
        dc.display();
    }
}

void displayMockEmployees() {
    std::cout << "Mock Employees:" << std::endl;
    for (const auto& emp : mockEmployees) {
        emp.display();
    }
}