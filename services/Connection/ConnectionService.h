#ifndef CONNECTION_SERVICE_H
#define CONNECTION_SERVICE_H

#include "../../entities/connection/Connection.h"
#include "../../utils/dataStructures/list/List.h"

class ConnectionService {
private:
    List& connections;

public:
    ConnectionService(List& connectionsList);

    // CRUD operations
    void createConnection(int id, int distributionCenterOrigin, int distributionCenterDestination, double distance);
    Connection* getConnectionById(int id);
    void updateConnection(int id, int distributionCenterOrigin, int distributionCenterDestination, double distance);
    void deleteConnection(int id);

    // Utility functions
    void displayAllConnections();
    int getConnectionCount();
};

#endif // CONNECTION_SERVICE_H