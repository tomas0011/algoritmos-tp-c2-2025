#ifndef SHIPMENT_MANAGER_H
#define SHIPMENT_MANAGER_H

#include "../connection/Connection.h"
#include "../package/Package.h"
#include "../transport/Transport.h"
#include "../../utils/dataStructures/list/List.h"

class ShipmentManager {
private:
    int id;
    int transportId;
    List path;
    int distributionCenterId;

public:
    // Constructor
    ShipmentManager(int id, int transportId, const List& path, int distributionCenterId);
    void display() const;

    // Getters
    int getId() const;
    int getTransportId() const;
    List getPath() const;
    int getDistributionCenterId() const;
};

#endif // SHIPMENT_MANAGER_H