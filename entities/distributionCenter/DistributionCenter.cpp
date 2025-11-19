#include "DistributionCenter.h"
#include <iostream>
#include <sstream>
#include <any>

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

// Constructor completo
DistributionCenter::DistributionCenter(
    const std::string& code,
    const std::string& name,
    const std::string& city,
    int capacity,
    int dailyPackages,
    int numEmployees,
    const List& employees,
    const List& connections,
    const List& warehouse
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
    
    if (!employees.isEmpty()) {
        std::cout << "\nEmpleados detallados (" << employees.getSize() << "):" << std::endl;
        Node* current = employees.getHead();
        while (current != nullptr) {
            try {
                Employee emp = std::any_cast<Employee>(current->getData());
                emp.display();
            } catch (const std::bad_any_cast&) {}
            current = current->getNext();
        }
    }
    
    if (!connections.isEmpty()) {
        std::cout << "\nConexiones (" << connections.getSize() << "):" << std::endl;
        Node* current = connections.getHead();
        while (current != nullptr) {
            try {
                Connection conn = std::any_cast<Connection>(current->getData());
                conn.display();
            } catch (const std::bad_any_cast&) {}
            current = current->getNext();
        }
    }
    
    if (!warehouse.isEmpty()) {
        std::cout << "\nPaquetes en almacen (" << warehouse.getSize() << "):" << std::endl;
        Node* current = warehouse.getHead();
        while (current != nullptr) {
            try {
                Package pkg = std::any_cast<Package>(current->getData());
                pkg.display();
            } catch (const std::bad_any_cast&) {}
            current = current->getNext();
        }
    }
    std::cout << "=============================" << std::endl;
}

std::string DistributionCenter::toString() const {
    std::ostringstream oss;
    oss << "Id: " << code
        << " | Name: " << name
        << " | City: " << city
        << " | Capacity: " << capacity
        << " | Daly Packages: " << dailyPackages
        << " | Employees: " << numEmployees;
    return oss.str();
}

// Getters
const std::string& DistributionCenter::getCode() const { return code; }
const std::string& DistributionCenter::getName() const { return name; }
const std::string& DistributionCenter::getCity() const { return city; }
int DistributionCenter::getCapacity() const { return capacity; }
int DistributionCenter::getDailyPackages() const { return dailyPackages; }
int DistributionCenter::getNumEmployees() const { return numEmployees; }
const List& DistributionCenter::getEmployees() const { return employees; }
const List& DistributionCenter::getConnections() const { return connections; }
const List& DistributionCenter::getWarehouse() const { return warehouse; }

// Setters
void DistributionCenter::setCapacity(int cap) { capacity = cap; }
void DistributionCenter::setDailyPackages(int daily) { dailyPackages = daily; }
void DistributionCenter::setNumEmployees(int num) { numEmployees = num; }

void DistributionCenter::addEmployee(const Employee& emp) {
    employees.push(std::any(emp));
    numEmployees = employees.getSize();
}

void DistributionCenter::addConnection(const Connection& conn) {
    connections.push(std::any(conn));
}

void DistributionCenter::addPackage(const Package& pkg) {
    warehouse.push(std::any(pkg));
}


