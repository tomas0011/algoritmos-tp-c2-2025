#include "DistributionCenterManager.h"
#include <iostream>

DistributionCenterManager::DistributionCenterManager() : distributionCenterNetwork(23) {}

DistributionCenter DistributionCenterManager::createDistributionCenter(std::string code, std::string name, std::string city, int capacity, int dailyPackages, int employees) {
    
    List empList;
    List connList;
    List pkgList

    DistributionCenter center(code, name, city, capacity, dailyPackages, employees, empList, connList, pkgList);
    distributionCenters.push_back(center);
    distributionCenterNetwork.addNode(code, &distributionCenters.back());

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
    if (!distributionCenterNetwork.hasNode(code)) {
        throw std::runtime_error("Distribution Center with code " + code + " not found.");
    }
    HashGraphNode* node = any_cast<HashGraphNode*>(distributionCenterNetwork.getNode(code));
    return any_cast<DistributionCenter*>(node->getData());
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

List DistributionCenterManager::getDistributionCentersList() const {
    List list;

    for (const DistributionCenter& dc : distributionCenters) {
        list.push((void*)&dc);
    }

    return list;
}

DistributionCenter* DistributionCenterManager::getById(std::string id) {
    for (auto& center : distributionCenters) {
        if (center.getCode() == id) {
            return &center;   // devolvés puntero al objeto real 
        }
    }
    return nullptr; // si no lo encontró
}
