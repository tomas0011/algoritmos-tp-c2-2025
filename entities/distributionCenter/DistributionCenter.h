#ifndef DISTRIBUTION_CENTER_H
#define DISTRIBUTION_CENTER_H

#include <string>
#include <vector>
#include "../package/Package.h"
#include "../employee/Employee.h"
#include "../connection/Connection.h"

class DistributionCenter {
private:
    std::string code;           // Codigo del centro (ej: CBA, MZA, BUE)
    std::string name;           // Nombre del centro
    std::string city;           // Ciudad
    int capacity;               // Capacidad total de paquetes
    int dailyPackages;          // Paquetes procesados diariamente
    int numEmployees;           // Número de empleados
    std::vector<Employee> employees;      // Lista detallada de empleados (opcional)
    std::vector<Connection> connections;  // Conexiones con otros centros
    std::vector<Package> warehouse;       // Paquetes en almacen

public:
    // Constructor principal (según formato del archivo centros.txt)
    DistributionCenter(
        const std::string& code,
        const std::string& name,
        const std::string& city,
        int capacity,
        int dailyPackages,
        int numEmployees
    );

    // Constructor completo (con vectores opcionales)
    DistributionCenter(
        const std::string& code,
        const std::string& name,
        const std::string& city,
        int capacity,
        int dailyPackages,
        int numEmployees,
        const std::vector<Employee>& employees,
        const std::vector<Connection>& connections = {},
        const std::vector<Package>& warehouse = {}
    );

    void display() const;
    std::string toString() const;

    // Getters
    const std::string& getCode() const;
    const std::string& getName() const;
    const std::string& getCity() const;
    int getCapacity() const;
    int getDailyPackages() const;
    int getNumEmployees() const;
    const std::vector<Employee>& getEmployees() const;
    const std::vector<Connection>& getConnections() const;
    const std::vector<Package>& getWarehouse() const;

    // Setters
    void setCapacity(int cap);
    void setDailyPackages(int daily);
    void setNumEmployees(int num);

    // Add methods
    void addEmployee(const Employee& emp);
    void addConnection(const Connection& conn);
    void addPackage(const Package& pkg);
};

#endif // DISTRIBUTION_CENTER_H
