#include "DistributionCenterManager.h"
#include "../../storage/storage.h"
#include <iostream>

DistributionCenterManager::DistributionCenterManager(ConnectionService* connService) 
    : distributionCenterNetwork(47), connectionService(connService) {}

// Destructor para liberar memoria manualmente
DistributionCenterManager::~DistributionCenterManager() {
    int centers_deleted = 0;
    Node* current = distributionCenterList.getHead();
    
    while (current != nullptr) {
        Node* nextNode = current->getNext();
        try {
            DistributionCenter* centerPtr = std::any_cast<DistributionCenter*>(current->getData());
            std::cout << "    -> Liberando DistributionCenter: " << centerPtr->getCode() 
                      << " (" << centerPtr->getName() << ")" << std::endl;
            delete centerPtr;  // Liberar DistributionCenter
            centers_deleted++;
        } catch (const std::bad_any_cast&) {}
        delete current;  // Liberar Node
        current = nextNode;
    }
    // Clear the list head
    distributionCenterList.setHead(nullptr);
    
    if (centers_deleted > 0) {
        std::cout << "    ✓ Total centros liberados: " << centers_deleted << std::endl;
    }
}

DistributionCenter DistributionCenterManager::createDistributionCenter(std::string code, std::string name, std::string city, int capacity, int dailyPackages, int employees) {
    List empVector;
    List connVector;
    List pkgVector;

    // Simplificado: usar new simple en lugar de unique_ptr
    DistributionCenter* centerPtr = new DistributionCenter(code, name, city, capacity, dailyPackages, employees, empVector, connVector, pkgVector);
    
    // Almacenar puntero simple en List
    distributionCenterList.push(centerPtr);
    //  Puntero sigue siendo estable
    distributionCenterNetwork.addNode(code, centerPtr);

    std::cout << "Distribution Center created: " << name << " in " << city << std::endl;
    return *centerPtr;
}

void DistributionCenterManager::createConnection(std::string originCode, std::string destinationCode, double distance) {
    // Validar que los centros existen usando nuestro propio método
    if (!hasCenter(originCode) || !hasCenter(destinationCode)) {
        std::cout << "Error: Uno o ambos centros no existen." << std::endl;
        std::cout << "Origen: " << originCode << " - " << (hasCenter(originCode) ? "Existe" : "No existe") << std::endl;
        std::cout << "Destino: " << destinationCode << " - " << (hasCenter(destinationCode) ? "Existe" : "No existe") << std::endl;
        return;
    }
    
    // Crear connection usando el service, pero sin validación interna (ya validamos)
    connectionService->createConnectionWithoutValidation(originCode, destinationCode, distance);
    
    // Añadir arista al grafo para algoritmos
    distributionCenterNetwork.addConnection(originCode, destinationCode, distance);
    
    std::cout << "Conexion creada: " << originCode << " -> " << destinationCode 
              << " (" << distance << " km)" << std::endl;
}

void DistributionCenterManager::createBidirectionalConnection(std::string originCode, std::string destinationCode, double distance) {
    // Validar que los centros existen
    if (!hasCenter(originCode) || !hasCenter(destinationCode)) {
        std::cout << "Error: Uno o ambos centros no existen." << std::endl;
        std::cout << "Origen: " << originCode << " - " << (hasCenter(originCode) ? "Existe" : "No existe") << std::endl;
        std::cout << "Destino: " << destinationCode << " - " << (hasCenter(destinationCode) ? "Existe" : "No existe") << std::endl;
        return;
    }
    
    // Crear conexiones bidireccionales usando el service
    connectionService->createBidirectionalConnectionWithoutValidation(originCode, destinationCode, distance);
    
    // Añadir aristas bidireccionales al grafo
    distributionCenterNetwork.addConnection(originCode, destinationCode, distance);
    distributionCenterNetwork.addConnection(destinationCode, originCode, distance);
    
    std::cout << "Conexión bidireccional creada: " << originCode << " <-> " << destinationCode 
              << " (" << distance << " km)" << std::endl;
}

void DistributionCenterManager::addConnectionToGraph(const Connection& conn) {
    // Añadir arista técnica al grafo para algoritmos
    distributionCenterNetwork.addConnection(conn.getDistributionCenterOrigin(), 
                                           conn.getDistributionCenterDestination(), 
                                           conn.getDistance());
}

void DistributionCenterManager::relateDistributionCenter(std::string code1, std::string code2, int distance) {
    // Crear conexión usando el service (ahora es void)
    createConnection(code1, code2, distance);
    
    std::cout << "Conexion entre centros "<< code1 << " y " << code2 << std::endl;
}

bool DistributionCenterManager::hasCenter(std::string code) const {
    return distributionCenterNetwork.hasNode(code);
}

void DistributionCenterManager::displayAllConnections() const {
    std::cout << "\n=== Conexiones del Manager de Centros de Distribución ===" << std::endl;
    
    // Mostrar conexiones usando el ConnectionService
    connectionService->displayAllConnections();
}

DistributionCenter* DistributionCenterManager::getCenter(std::string code) const {
    //  Simplificado: iterar sobre punteros simples
    Node* current = distributionCenterList.getHead();
    
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
    return distributionCenterList.getSize();  //  Cambio: usar getSize() de List en lugar de size() de vector
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
    std::cout << "Lista de Centros de Distribucion:" << std::endl;
    Node* current = distributionCenterList.getHead();
    
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
    return distributionCenterList;  //  Cambiado: retornar referencia a List en lugar de vector
}

DistributionCenter* DistributionCenterManager::getById(std::string id) {
    //  Cambio: reutilizar getCenter que ya busca por código
    return getCenter(id);
}
