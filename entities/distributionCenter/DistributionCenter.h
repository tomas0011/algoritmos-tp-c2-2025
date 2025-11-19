#ifndef DISTRIBUTION_CENTER_H
#define DISTRIBUTION_CENTER_H

#include <string>
#include "../package/Package.h"
#include "../employee/Employee.h"
#include "../connection/Connection.h"
#include "../../utils/dataStructures/list/List.h"

class DistributionCenter {
private:
    std::string code;           // Codigo del centro (ej: CBA, MZA, BUE)
    std::string name;           // Nombre del centro
    std::string city;           // Ciudad
    int capacity;               // Capacidad total de paquetes
    int dailyPackages;          // Paquetes procesados diariamente
    int numEmployees;           // Número de empleados
    List employees;      // Lista detallada de empleados (opcional)
    List connections;  // Conexiones con otros centros
    List warehouse;       // Paquetes en almacen

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

    // Constructor completo (con listas opcionales)
    DistributionCenter(
        const std::string& code,
        const std::string& name,
        const std::string& city,
        int capacity,
        int dailyPackages,
        int numEmployees,
        const List& employees,
        const List& connections = List(),
        const List& warehouse = List()
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
    const List& getEmployees() const;
    const List& getConnections() const;
    const List& getWarehouse() const;

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
