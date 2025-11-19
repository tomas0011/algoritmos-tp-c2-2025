#include "DistributionCenterManager.h"
#include <iostream>

DistributionCenterManager::DistributionCenterManager() : distributionCenterNetwork(23) {}

// Destructor para liberar memoria manualmente
DistributionCenterManager::~DistributionCenterManager() {
    Node* current = distributionCenterPtrs.getHead();
    while (current != nullptr) {
        Node* nextNode = current->getNext();
        try {
            DistributionCenter* centerPtr = std::any_cast<DistributionCenter*>(current->getData());
            delete centerPtr;  // Liberar DistributionCenter
        } catch (const std::bad_any_cast&) {}
        delete current;  // Liberar Node
        current = nextNode;
    }
    // Clear the list head
    distributionCenterPtrs.setHead(nullptr);
}

DistributionCenter DistributionCenterManager::createDistributionCenter(std::string code, std::string name, std::string city, int capacity, int dailyPackages, int employees) {
    List empVector;
    List connVector;
    List pkgVector;

    // Simplificado: usar new simple en lugar de unique_ptr
    DistributionCenter* centerPtr = new DistributionCenter(code, name, city, capacity, dailyPackages, employees, empVector, connVector, pkgVector);
    
    // Almacenar puntero simple en List
    distributionCenterPtrs.push(centerPtr);
    //  Puntero sigue siendo estable
    distributionCenterNetwork.addNode(code, centerPtr);

    std::cout << "Distribution Center created: " << name << " in " << city << std::endl;
    return *centerPtr;
}

void DistributionCenterManager::relateDistributionCenter(std::string code1, std::string code2, int distance) {
    // Usar el nuevo método que crea objetos Connection solo en el grafo interno
    distributionCenterNetwork.addConnection(code1, code2, distance);
}

bool DistributionCenterManager::hasCenter(std::string code) const {
    return distributionCenterNetwork.hasNode(code);
}

DistributionCenter* DistributionCenterManager::getCenter(std::string code) const {
    //  Simplificado: iterar sobre punteros simples
    Node* current = distributionCenterPtrs.getHead();
    
    while (current != nullptr) {
        try {
            DistributionCenter* centerPtr = std::any_cast<DistributionCenter*>(current->getData());
            if (centerPtr->getCode() == code) {
                return centerPtr;  //  Retornar puntero simple
            }
        } catch (const std::bad_any_cast&) {}
        current = current->getNext();
    }
    return nullptr;
}

int DistributionCenterManager::getDistributionCentersCount() const {
    return distributionCenterPtrs.getSize();  //  Cambio: usar getSize() de List en lugar de size() de vector
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
    Node* current = distributionCenterPtrs.getHead();
    
    while (current != nullptr) {
        try {
            DistributionCenter* centerPtr = std::any_cast<DistributionCenter*>(current->getData());
            const DistributionCenter& center = *centerPtr;
            std::cout << "Code: " << center.getCode()
                      << ", Name: " << center.getName()
                      << ", City: " << center.getCity()
                      << ", Employees: " << center.getEmployees().getSize()
                      << ", Connections: " << center.getConnections().getSize()
                      << ", Warehouse Packages: " << center.getWarehouse().getSize()
                      << std::endl;
        } catch (const std::bad_any_cast&) {}
        current = current->getNext();
    }
}

GraphHashTable& DistributionCenterManager::getNetwork() const {
    return const_cast<GraphHashTable&>(distributionCenterNetwork);
}

List& DistributionCenterManager::getDistributionCentersList() {
    return distributionCenterPtrs;  //  Cambiado: retornar referencia a List en lugar de vector
}

DistributionCenter* DistributionCenterManager::getById(std::string id) {
    //  Cambio: reutilizar getCenter que ya busca por código
    return getCenter(id);
}
