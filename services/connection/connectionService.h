#ifndef CONNECTION_SERVICE_H
#define CONNECTION_SERVICE_H

#include "../../entities/connection/Connection.h"
#include "../../utils/dataStructures/list/List.h"
#include "../../utils/dataStructures/Graph/GraphHashTable.h"

class DistributionCenterManager;

class ConnectionService {
private:
    DistributionCenterManager* manager;
    List& connections;
    static int nextId; // Para generar IDs automaticamente

    // Método privado para generar siguiente ID
    int generateNextId();
    
    // Método privado para verificar si un centro existe
    bool centerExists(const std::string& centerCode);
    
    // Método para verificar centros con referencia al manager
    bool centerExists(const std::string& centerCode, const DistributionCenterManager* manager);

public:
    ConnectionService(
        DistributionCenterManager* manager,
        List& connectionsList);

    // CRUD operations
    void createConnection(int id, const std::string& distributionCenterOrigin, const std::string& distributionCenterDestination, double distance);
    
    // Versión que genera ID automaticamente
    void createConnection(const std::string& distributionCenterOrigin, const std::string& distributionCenterDestination, double distance);
    
    // Versión sin validación (para uso interno del DistributionCenterManager)
    void createConnectionWithoutValidation(const std::string& distributionCenterOrigin, const std::string& distributionCenterDestination, double distance);
    
    // Método para crear conexión bidireccional
    void createBidirectionalConnection(const std::string& distributionCenterOrigin, const std::string& distributionCenterDestination, double distance);
    
    // Método para crear conexión bidireccional sin validación
    void createBidirectionalConnectionWithoutValidation(const std::string& distributionCenterOrigin, const std::string& distributionCenterDestination, double distance);
    
    Connection* getConnectionById(int id);
    void updateConnection(int id, const std::string& distributionCenterOrigin, const std::string& distributionCenterDestination, double distance);
    void deleteConnection(int id);

    // Utility functions
    void displayAllConnections();
    int getConnectionCount();
};

#endif // CONNECTION_SERVICE_H