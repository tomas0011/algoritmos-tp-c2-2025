#ifndef SHIPMENT_SERVICE_H
#define SHIPMENT_SERVICE_H

#include "../../entities/shipment/Shipment.h"
#include "../../utils/dataStructures/list/List.h"
#include <vector>

class ShipmentService {
private:
    List& shipments;

public:
    ShipmentService(List& shipmentsList);

    // CRUD operations
    void createShipment(int id, const std::string& state, double cost, int priority, double totalPrice,
                       double totalWeight, int shimpmentManagerId, int distributionCenterId,
                       const std::vector<Package>& packages, int originId, int destinationId,
                       int clientId, time_t createDate, time_t leftWarehouseDate,
                       time_t estimatedDeliveryDate, time_t deliveryDate);
    Shipment* getShipmentById(int id);
    void updateShipment(int id, const std::string& state, double cost, int priority, double totalPrice,
                       double totalWeight, int shimpmentManagerId, int distributionCenterId,
                       const std::vector<Package>& packages, int originId, int destinationId,
                       int clientId, time_t createDate, time_t leftWarehouseDate,
                       time_t estimatedDeliveryDate, time_t deliveryDate);
    void deleteShipment(int id);

    // Utility functions
    void displayAllShipments();
    int getShipmentCount();
};

#endif // SHIPMENT_SERVICE_H