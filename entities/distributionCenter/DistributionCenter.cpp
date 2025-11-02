#include "DistributionCenter.h"
#include <iostream>

// Constructor por defecto
DistributionCenter::DistributionCenter()
    : id(0), code(""), name(""), city(""), capacity(0), 
      dailyPackages(0), employeeCount(0), 
      employees(), connections(), warehouse() {}

// Constructor completo
DistributionCenter::DistributionCenter(
    int id,
    const std::string& code,
    const std::string& name,
    const std::string& city,
    int capacity,
    int dailyPackages,
    int employeeCount,
    const std::vector<Employee>& employees,
    const std::vector<Connection>& connections,
    const std::vector<Package>& warehouse
)
    : id(id), code(code), name(name), city(city), capacity(capacity), 
      dailyPackages(dailyPackages), employeeCount(employeeCount),
      employees(employees), connections(connections), warehouse(warehouse) {}

// Constructor simplificado para archivo centros.txt
DistributionCenter::DistributionCenter(
    const std::string& code,
    const std::string& name,
    const std::string& city,
    int capacity,
    int dailyPackages,
    int employeeCount
)
    : id(0), code(code), name(name), city(city), capacity(capacity),
      dailyPackages(dailyPackages), employeeCount(employeeCount) {}

void DistributionCenter::display() const {
    std::cout << "=== Centro de Distribución ===" << std::endl;
    std::cout << "Código: " << code << std::endl;
    std::cout << "Nombre: " << name << std::endl;
    std::cout << "Ciudad: " << city << std::endl;
    std::cout << "Capacidad: " << capacity << std::endl;
    std::cout << "Paquetes diarios: " << dailyPackages << std::endl;
    std::cout << "Empleados: " << employeeCount << std::endl;
    
    if (!employees.empty()) {
        std::cout << "Lista de empleados (" << employees.size() << "):" << std::endl;
        for (const auto& emp : employees) {
            emp.display();
        }
    }
    
    if (!connections.empty()) {
        std::cout << "Conexiones (" << connections.size() << "):" << std::endl;
        for (const auto& conn : connections) {
            conn.display();
        }
    }
    
    if (!warehouse.empty()) {
        std::cout << "Paquetes en almacén (" << warehouse.size() << "):" << std::endl;
        for (const auto& pkg : warehouse) {
            pkg.display();
        }
    }
    std::cout << "=============================" << std::endl;
}

// Getters
int DistributionCenter::getId() const { return id; }
const std::string& DistributionCenter::getCode() const { return code; }
const std::string& DistributionCenter::getName() const { return name; }
const std::string& DistributionCenter::getCity() const { return city; }
int DistributionCenter::getCapacity() const { return capacity; }
int DistributionCenter::getDailyPackages() const { return dailyPackages; }
int DistributionCenter::getEmployeeCount() const { return employeeCount; }
const std::vector<Employee>& DistributionCenter::getEmployees() const { return employees; }
const std::vector<Connection>& DistributionCenter::getConnections() const { return connections; }
const std::vector<Package>& DistributionCenter::getWarehouse() const { return warehouse; }
