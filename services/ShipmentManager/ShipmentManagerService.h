#ifndef SHIPMENT_MANAGER_SERVICE_H
#define SHIPMENT_MANAGER_SERVICE_H

#include "../../entities/shipmentManager/ShipmentManager.h"
#include "../../utils/dataStructures/list/List.h"

class ShipmentManagerService {
private:
    List& shipmentManagers;

public:
    ShipmentManagerService(List& shipmentManagersList);

    // CRUD operations
    void createShipmentManager(int id, int transportId, const std::vector<Connection>& path, int distributionCenterId);
    ShipmentManager* getShipmentManagerById(int id);
    void updateShipmentManager(int id, int transportId, const std::vector<Connection>& path, int distributionCenterId);
    void deleteShipmentManager(int id);

    // Utility functions
    void displayAllShipmentManagers();
    int getShipmentManagerCount();
};  

#endif // SHIPMENT_MANAGER_SERVICE_H