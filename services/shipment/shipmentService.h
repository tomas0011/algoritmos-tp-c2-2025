#ifndef SHIPMENT_SERVICE_H
#define SHIPMENT_SERVICE_H

#include "../../entities/shipment/Shipment.h"
#include "../../utils/dataStructures/list/List.h"
#include "../../storage/storage.h"
#include <vector>
#include <ctime>
#include <unordered_map>

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

    //Punto B

    //cantidad total de envios por centro de distribucion entre dos fechas
    int totalShipmentsByCenterAndDate(int centerId, time_t start, time_t end);
    
    // centros de distribucion que han sobrepasado un limite semanal de envios
    std::vector<int> overloadedCenters(int weeklyLimit);

    // envios pertenecientes a un cliente
    std::vector<Shipment> findShipmentsByClient(int clientId);

};

#endif // SHIPMENT_SERVICE_H
