#include "Shipment.h"
#include <iostream>

Shipment::Shipment(int id, const std::string& state, double cost, int priority, double totalPrice, double totalWeight,
                   int shimpmentManagerId, int distributionCenterId, const std::vector<Package>& packages,
                   int originId, int destinationId, int clientId, time_t createDate, time_t leftWarehouseDate,
                   time_t estimatedDeliveryDate, time_t deliveryDate)
    : id(id), state(state), cost(cost), priority(priority), totalPrice(totalPrice), totalWeight(totalWeight),
      shimpmentManagerId(shimpmentManagerId), distributionCenterId(distributionCenterId), packages(packages),
      originId(originId), destinationId(destinationId), clientId(clientId), createDate(createDate),
      leftWarehouseDate(leftWarehouseDate), estimatedDeliveryDate(estimatedDeliveryDate), deliveryDate(deliveryDate) {}

void Shipment::display() const {
    std::cout << "ID: " << id << ", State: " << state << ", Cost: " << cost << ", Priority: " << priority
              << ", TotalPrice: " << totalPrice << ", TotalWeight: " << totalWeight
              << ", ShipmentManagerId: " << shimpmentManagerId << ", DistributionCenterId: " << distributionCenterId
              << ", OriginId: " << originId << ", DestinationId: " << destinationId << ", ClientId: " << clientId
              << ", CreateDate: " << createDate << ", LeftWarehouseDate: " << leftWarehouseDate
              << ", EstimatedDeliveryDate: " << estimatedDeliveryDate << ", DeliveryDate: " << deliveryDate << std::endl;
    for (const auto& pkg : packages) {
        pkg.display();
    }
}

int Shipment::getId() const { return id; }
const std::string& Shipment::getState() const { return state; }
double Shipment::getCost() const { return cost; }
int Shipment::getPriority() const { return priority; }
double Shipment::getTotalPrice() const { return totalPrice; }
double Shipment::getTotalWeight() const { return totalWeight; }
int Shipment::getShimpmentManagerId() const { return shimpmentManagerId; }
int Shipment::getDistributionCenterId() const { return distributionCenterId; }
const std::vector<Package>& Shipment::getPackages() const { return packages; }
int Shipment::getOriginId() const { return originId; }
int Shipment::getDestinationId() const { return destinationId; }
int Shipment::getClientId() const { return clientId; }
time_t Shipment::getCreateDate() const { return createDate; }
time_t Shipment::getLeftWarehouseDate() const { return leftWarehouseDate; }
time_t Shipment::getEstimatedDeliveryDate() const { return estimatedDeliveryDate; }
time_t Shipment::getDeliveryDate() const { return deliveryDate; }