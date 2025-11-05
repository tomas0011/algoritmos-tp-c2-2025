#ifndef PATH_TRANSPORT_SERVICE_H
#define PATH_TRANSPORT_SERVICE_H

#include "../../entities/transport/Transport.h"
#include "../../utils/dataStructures/list/List.h"

class TransportService {
private:
    List& transports;

public:
    TransportService(List& transportsList);

    // CRUD operations
    void createTransport(int id, const std::string& type, double maxWeight);
    Transport* getTransportById(int id);
    void updateTransport(int id, const std::string& type, double maxWeight);
    void deleteTransport(int id);

    // Utility functions
    void displayAllTransports();
    int getTransportCount();

};

#endif // TRANSPORT_SERVICE_H
