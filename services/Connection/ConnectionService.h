#ifndef CONNECTION_SERVICE_H
#define CONNECTION_SERVICE_H

#include "../../entities/connection/Connection.h"
#include "../../utils/dataStructures/list/List.h"

class ConnectionService {
private:
    List& connections;
    static int nextId; // Para generar IDs automáticamente

    // Método privado para generar siguiente ID
    int generateNextId();

public:
    ConnectionService(List& connectionsList);

    // CRUD operations
    void createConnection(int id, const std::string& distributionCenterOrigin, const std::string& distributionCenterDestination, double distance);
    
    // Versión que genera ID automáticamente
    void createConnection(const std::string& distributionCenterOrigin, const std::string& distributionCenterDestination, double distance);
    
    Connection* getConnectionById(int id);
    void updateConnection(int id, const std::string& distributionCenterOrigin, const std::string& distributionCenterDestination, double distance);
    void deleteConnection(int id);

    // Utility functions
    void displayAllConnections();
    int getConnectionCount();
};

#endif // CONNECTION_SERVICE_H