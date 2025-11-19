#ifndef SHIPMENT_H
#define SHIPMENT_H

#include <string>
#include <ctime>
#include "../package/Package.h"
#include "../utils/dataStructures/list/List.h"


class Shipment {
private:
    int id;
    std::string state;
    double cost;
    int priority;
    double totalPrice;
    double totalWeight;
    int shimpmentManagerId;
    std::string distributionCenterId;
    List packages;
    int originId;
    int destinationId;
    int clientId;
    time_t createDate;
    time_t leftWarehouseDate;
    time_t estimatedDeliveryDate;
    time_t deliveryDate;

public:
    Shipment(int id, const std::string& state, double cost, int priority, double totalPrice, double totalWeight,
             int shimpmentManagerId, std::string distributionCenterId, const  List packages,
             int originId, int destinationId, int clientId, time_t createDate, time_t leftWarehouseDate,
             time_t estimatedDeliveryDate, time_t deliveryDate);
    void display() const;

    // Getters
    int getId() const;
    const std::string& getState() const;
    double getCost() const;
    int getPriority() const;
    double getTotalPrice() const;
    double getTotalWeight() const;
    int getShimpmentManagerId() const;
    std::string getDistributionCenterId() const;
    List getPackages() const;
    int getOriginId() const;
    int getDestinationId() const;
    int getClientId() const;
    time_t getCreateDate() const;
    time_t getLeftWarehouseDate() const;
    time_t getEstimatedDeliveryDate() const;
    time_t getDeliveryDate() const;
};

#endif // SHIPMENT_H