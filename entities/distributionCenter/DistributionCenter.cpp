#include "DistributionCenter.h"
#include <iostream>
#include <sstream>

// Constructor principal (según formato del archivo centros.txt)
DistributionCenter::DistributionCenter(
    const std::string& code,
    const std::string& name,
    const std::string& city,
    int capacity,
    int dailyPackages,
    int numEmployees
)
    : code(code), name(name), city(city), 
      capacity(capacity), dailyPackages(dailyPackages), numEmployees(numEmployees) {}

// Constructor completo (con vectores opcionales)
DistributionCenter::DistributionCenter(
    const std::string& code,
    const std::string& name,
    const std::string& city,
    int capacity,
    int dailyPackages,
    int numEmployees,
    const std::vector<Employee>& employees,
    const std::vector<Connection>& connections,
    const std::vector<Package>& warehouse
)
    : code(code), name(name), city(city),
      capacity(capacity), dailyPackages(dailyPackages), numEmployees(numEmployees),
      employees(employees), connections(connections), warehouse(warehouse) {}

void DistributionCenter::display() const {
    std::cout << "=== Centro de Distribucion ===" << std::endl;
    std::cout << "Codigo: " << code << std::endl;
    std::cout << "Nombre: " << name << std::endl;
    std::cout << "Ciudad: " << city << std::endl;
    std::cout << "Capacidad: " << capacity << " paquetes" << std::endl;
    std::cout << "Paquetes diarios: " << dailyPackages << std::endl;
    std::cout << "Empleados: " << numEmployees << std::endl;
    
    if (!employees.empty()) {
        std::cout << "\nEmpleados detallados (" << employees.size() << "):" << std::endl;
        for (const auto& emp : employees) {
            emp.display();
        }
    }
    
    if (!connections.empty()) {
        std::cout << "\nConexiones (" << connections.size() << "):" << std::endl;
        for (const auto& conn : connections) {
            conn.display();
        }
    }
    
    if (!warehouse.empty()) {
        std::cout << "\nPaquetes en almacen (" << warehouse.size() << "):" << std::endl;
        for (const auto& pkg : warehouse) {
            pkg.display();
        }
    }
    std::cout << "=============================" << std::endl;
}

std::string DistributionCenter::toString() const {
    std::ostringstream oss;
    oss << code << " | " << name << " | " << city 
        << " | Cap:" << capacity 
        << " | Paq:" << dailyPackages 
        << " | Emp:" << numEmployees;
    return oss.str();
}

// Getters
const std::string& DistributionCenter::getCode() const { return code; }
const std::string& DistributionCenter::getName() const { return name; }
const std::string& DistributionCenter::getCity() const { return city; }
int DistributionCenter::getCapacity() const { return capacity; }
int DistributionCenter::getDailyPackages() const { return dailyPackages; }
int DistributionCenter::getNumEmployees() const { return numEmployees; }
const std::vector<Employee>& DistributionCenter::getEmployees() const { return employees; }
const std::vector<Connection>& DistributionCenter::getConnections() const { return connections; }
const std::vector<Package>& DistributionCenter::getWarehouse() const { return warehouse; }

// Setters
void DistributionCenter::setCapacity(int cap) { capacity = cap; }
void DistributionCenter::setDailyPackages(int daily) { dailyPackages = daily; }
void DistributionCenter::setNumEmployees(int num) { numEmployees = num; }

void DistributionCenter::addEmployee(const Employee& emp) {
    employees.push_back(emp);
    numEmployees = employees.size();
}

void DistributionCenter::addConnection(const Connection& conn) {
    connections.push_back(conn);
}

void DistributionCenter::addPackage(const Package& pkg) {
    warehouse.push_back(pkg);
}


