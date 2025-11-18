#include "DistributionCenterManager.h"
#include <iostream>

void DistributionCenterManager::createDistributionCenter(int id, std::string name, std::string city, int capacity, int dailyPackages, int employees) {
    // For now, create empty vectors for employees and connections
    // In a real implementation, these would be populated based on the parameters
    std::vector<Employee> empVector;
    std::vector<Connection> connVector;
    std::vector<Package> pkgVector;

    DistributionCenter center(id, name, city, empVector, connVector, pkgVector);
    distributionCenters.push_back(center);

    std::cout << "Distribution Center created: " << name << " in " << city << std::endl;
}

void DistributionCenterManager::getCenters() {
    std::cout << "List of Distribution Centers:" << std::endl;
    for (const auto& center : distributionCenters) {
        std::cout << "ID: " << center.getId()
                  << ", Name: " << center.getName()
                  << ", City: " << center.getCity()
                  << ", Employees: " << center.getEmployees().size()
                  << ", Connections: " << center.getConnections().size()
                  << ", Warehouse Packages: " << center.getWarehouse().size()
                  << std::endl;
    }
}

const std::vector<DistributionCenter>& DistributionCenterManager::getDistributionCenters() const {
    return distributionCenters;
}

DistributionCenter* DistributionCenterManager::getById(int id) {
    for (auto& center : distributionCenters) {
        if (center.getId() == id) {
            return &center;   // devolvés puntero al objeto real del vector
        }
    }
    return nullptr; // si no lo encontró
}
