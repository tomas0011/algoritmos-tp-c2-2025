#ifndef SHIPMENT_MANAGER_H
#define SHIPMENT_MANAGER_H

#include <vector>
#include "../connection/Connection.h"
#include "../package/Package.h"
#include "../transport/Transport.h"

class ShipmentManager {
private:
    int id;
    int transportId;
    std::vector<Connection> path;
    int distributionCenterId;

public:
    // Constructor
    ShipmentManager(int id, int transportId, const std::vector<Connection>& path, int distributionCenterId);
    void display() const;

    // Getters
    int getId() const;
    int getTransportId() const;
    const std::vector<Connection>& getPath() const;
    int getDistributionCenterId() const;

    std::vector<Package> generarCargaOptima() const;
}

#endif // SHIPMENT_MANAGER_H