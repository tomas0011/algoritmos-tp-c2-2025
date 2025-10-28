#include "DistributionCenter.h"
#include <iostream>

DistributionCenter::DistributionCenter(
    int id,
    const std::string& name,
    const std::string& city,
    const std::vector<Employee>& employees,
    const std::vector<Connection>& connections,
    const std::vector<Package>& warehouse
)
    : id(id), name(name), city(city), employees(employees), connections(connections), warehouse(warehouse) {}

void DistributionCenter::display() const {
    std::cout << "ID: " << id << ", Name: " << name << ", City: " << city << std::endl;
    std::cout << "Employees (" << employees.size() << "):" << std::endl;
    for (const auto& emp : employees) {
        emp.display();
    }
    std::cout << "Connections (" << connections.size() << "):" << std::endl;
    for (const auto& conn : connections) {
        conn.display();
    }
    std::cout << "Warehouse Packages (" << warehouse.size() << "):" << std::endl;
    for (const auto& pkg : warehouse) {
        pkg.display();
    }
}

int DistributionCenter::getId() const { return id; }
const std::string& DistributionCenter::getName() const { return name; }
const std::string& DistributionCenter::getCity() const { return city; }
const std::vector<Employee>& DistributionCenter::getEmployees() const { return employees; }
const std::vector<Connection>& DistributionCenter::getConnections() const { return connections; }
const std::vector<Package>& DistributionCenter::getWarehouse() const { return warehouse; }
