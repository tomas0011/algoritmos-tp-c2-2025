#ifndef SHIPMENT_MANAGER_SERVICE_H
#define SHIPMENT_MANAGER_SERVICE_H

#include "../../entities/shipmentManager/ShipmentManager.h"
#include "../../entities/transport/Transport.h"
#include "../../entities/distributionCenter/DistributionCenter.h"
#include "../../entities/package/Package.h"
#include "../../utils/dataStructures/list/List.h"
#include "../../services/transport/transportService.h"
#include "../../services/distributionCenter/distributionCenterService.h"

class ShipmentManagerService {
private:
    TransportService* transportService;
    DistributionCenterService* distributionCenterService;
    List& shipmentManagers;

public:
    ShipmentManagerService(
        TransportService* transportService,
        DistributionCenterService* distributionCenterService,
        List& shipmentManagersList);

    // CRUD operations
    void createShipmentManager(int id, int transportId, const List& path, int distributionCenterId);
    ShipmentManager* getShipmentManagerById(int id);
    void updateShipmentManager(int id, int transportId, const List& path, int distributionCenterId);
    void deleteShipmentManager(int id);

    // Utility functions
    void displayAllShipmentManagers();
    int getShipmentManagerCount();
    List generarCargaOptima(int transportId, std::string distributionCenterId) const;
};

#endif // SHIPMENT_MANAGER_SERVICE_H