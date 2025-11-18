#include "DistributionCenterManager.h"
#include <iostream>

DistributionCenterManager::DistributionCenterManager() : distributionCenterNetwork(23) {}

DistributionCenter DistributionCenterManager::createDistributionCenter(std::string code, std::string name, std::string city, int capacity, int dailyPackages, int employees) {
    // For now, create empty vectors for employees and connections
    // In a real implementation, these would be populated based on the parameters
    std::vector<Employee> empVector;
    std::vector<Connection> connVector;
    std::vector<Package> pkgVector;

    DistributionCenter center(code, name, city, capacity, dailyPackages, employees, empVector, connVector, pkgVector);
    distributionCenters.push_back(center);
    distributionCenterNetwork.addNode(code, center);

    std::cout << "Distribution Center created: " << name << " in " << city << std::endl;
    return center;
}

void DistributionCenterManager::relateDistributionCenter(std::string code1, std::string code2, int distance) {
    distributionCenterNetwork.addArista(code1, code2, distance);
}

bool DistributionCenterManager::hasCenter(std::string code) const {
    return distributionCenterNetwork.hasNode(code);
}

DistributionCenter* DistributionCenterManager::getCenter(std::string code) const {
    // Buscar en el vector de centros de distribución
    for (const auto& center : distributionCenters) {
        if (center.getCode() == code) {
            // Retornar un puntero al centro en el vector
            return const_cast<DistributionCenter*>(&center);
        }
    }
    throw std::runtime_error("Distribution Center with code " + code + " not found.");
}

int DistributionCenterManager::getDistributionCentersCount() const {
    return distributionCenters.size();
}

List DistributionCenterManager::getDistributionCentersCodes() {
    return distributionCenterNetwork.getNodeCodes();
}

void DistributionCenterManager::displayStatistics() {
    distributionCenterNetwork.displayStatistics();
}

List* DistributionCenterManager::getConnections(std::string code) const {
    return distributionCenterNetwork.getAristas(code);
}

void DistributionCenterManager::getCenters() {
    std::cout << "List of Distribution Centers:" << std::endl;
    for (const auto& center : distributionCenters) {
        std::cout << "Code: " << center.getCode()
                  << ", Name: " << center.getName()
                  << ", City: " << center.getCity()
                  << ", Employees: " << center.getEmployees().size()
                  << ", Connections: " << center.getConnections().size()
                  << ", Warehouse Packages: " << center.getWarehouse().size()
                  << std::endl;
    }
}

GraphHashTable& DistributionCenterManager::getNetwork() const {
    return const_cast<GraphHashTable&>(distributionCenterNetwork);
}

const std::vector<DistributionCenter>& DistributionCenterManager::getDistributionCenters() const {
    return distributionCenters;
}
