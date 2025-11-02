#ifndef DISTRIBUTION_CENTER_H
#define DISTRIBUTION_CENTER_H

#include <string>
#include <vector>
#include "../package/Package.h"
#include "../employee/Employee.h"
#include "../connection/Connection.h"

class DistributionCenter {
private:
    int id;
    std::string code;          // Código único (ej: CBA, MZA)
    std::string name;
    std::string city;
    int capacity;              // Capacidad del centro (pide el enunciado)
    int dailyPackages;         // Paquetes diarios procesados (pide el enunciado)
    int employeeCount;         // Cantidad de empleados (pide el enunciado)
    std::vector<Employee> employees;
    std::vector<Connection> connections;
    std::vector<Package> warehouse;

public:
    // Constructor por defecto (necesario para unordered_map)
    DistributionCenter();
    
    // Constructor completo
    DistributionCenter(
        int id,
        const std::string& code,
        const std::string& name,
        const std::string& city,
        int capacity,
        int dailyPackages,
        int employeeCount,
        const std::vector<Employee>& employees = {},
        const std::vector<Connection>& connections = {},
        const std::vector<Package>& warehouse = {}
    );
    
    // Constructor para archivo centros.txt
    DistributionCenter(
        const std::string& code,
        const std::string& name,
        const std::string& city,
        int capacity,
        int dailyPackages,
        int employeeCount
    );
    
    void display() const;

    // Getters
    int getId() const;
    const std::string& getCode() const;
    const std::string& getName() const;
    const std::string& getCity() const;
    int getCapacity() const;
    int getDailyPackages() const;
    int getEmployeeCount() const;
    const std::vector<Employee>& getEmployees() const;
    const std::vector<Connection>& getConnections() const;
    const std::vector<Package>& getWarehouse() const;
};

#endif // DISTRIBUTION_CENTER_H
