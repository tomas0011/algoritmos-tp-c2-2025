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
    std::string name;
    std::string city;
    std::vector<Employee> employees;
    std::vector<Connection> connections;
    std::vector<Package> warehouse;

public:
    DistributionCenter(
        int id,
        const std::string& name,
        const std::string& city,
        const std::vector<Employee>& employees = {},
        const std::vector<Connection>& connections = {},
        const std::vector<Package>& warehouse = {}
    );
    void display() const;

    // Getters
    int getId() const;
    const std::string& getName() const;
    const std::string& getCity() const;
    const std::vector<Employee>& getEmployees() const;
    const std::vector<Connection>& getConnections() const;
    const std::vector<Package>& getWarehouse() const;

    DistributionCenter* getById(int id);

};

#endif // DISTRIBUTION_CENTER_H
