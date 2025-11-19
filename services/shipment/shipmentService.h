#ifndef SHIPMENT_SERVICE_H
#define SHIPMENT_SERVICE_H

#include "../../storage/storage.h"
#include "../../entities/shipment/Shipment.h"
#include "../../entities/shipmentManager/ShipmentManager.h"
#include "../../entities/transport/Transport.h"
#include "../../entities/distributionCenter/DistributionCenter.h"
#include "../../entities/package/Package.h"
#include "../../utils/dataStructures/list/List.h"
#include "../../utils/algorithms/knapsackProblem/knapsack.h"
#include "../../services/transport/transportService.h"
#include "../../services/distributionCenter/distributionCenterService.h"
#include <vector>
#include <ctime>
#include <unordered_map>

class ShipmentService {
private:
    TransportService* transportService;
    DistributionCenterService* distributionCenterService;
    List& shipments;

public:
    ShipmentService(
        TransportService* transportService,
        DistributionCenterService* distributionCenterService,
        List& shipmentsList);

    // CRUD operations
    void createShipment(int id, const std::string& state, double cost, int priority, double totalPrice,
                       double totalWeight, int shimpmentManagerId, std::string distributionCenterId,
                       const std::vector<Package>& packages, std::string originId, std::string destinationId,
                       int clientId, time_t createDate, time_t leftWarehouseDate,
                       time_t estimatedDeliveryDate, time_t deliveryDate);
    Shipment* getShipmentById(int id);
    void updateShipment(int id, const std::string& state, double cost, int priority, double totalPrice,
                       double totalWeight, int shimpmentManagerId, std::string distributionCenterId,
                       const std::vector<Package>& packages, std::string originId, std::string destinationId,
                       int clientId, time_t createDate, time_t leftWarehouseDate,
                       time_t estimatedDeliveryDate, time_t deliveryDate);
    void deleteShipment(int id);

    // Utility functions
    void displayAllShipments();
    int getShipmentCount();

    // Punto B

    // B.1: cantidad total de envios por centro de distribucion entre dos fechas
    int totalShipmentsByCenterAndDate(std::string centerId, time_t start, time_t end);
    
    // B.2: centros de distribucion que han sobrepasado un limite semanal de envios
    std::vector<std::string> overloadedCenters();

    // B.3 envios pertenecientes a un cliente
    std::vector<Shipment> findShipmentsByClient(int clientId);

    // C.1: generar carga optima para un transporte en un centro de distribucion
    std::vector<Package> generateOptimalCargoForTransport(int transportId, std::string distributionCenterId) const;
};

#endif // SHIPMENT_SERVICE_H
