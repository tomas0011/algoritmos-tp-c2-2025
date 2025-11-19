#include "Shipment.h"
#include <iostream>
#include <utils/algorithms/parseDate/parseDate.h>

Shipment::Shipment(int id, const std::string& state, double cost, int priority, double totalPrice, double totalWeight,
                   int shimpmentManagerId, std::string distributionCenterId, const List& packages,
                   std::string originId, std::string destinationId, int clientId, time_t createDate, time_t leftWarehouseDate,
                   time_t estimatedDeliveryDate, time_t deliveryDate)
    : id(id), state(state), cost(cost), priority(priority), totalPrice(totalPrice), totalWeight(totalWeight),
      shimpmentManagerId(shimpmentManagerId), distributionCenterId(distributionCenterId), packages(packages),
      originId(originId), destinationId(destinationId), clientId(clientId), createDate(createDate),
      leftWarehouseDate(leftWarehouseDate), estimatedDeliveryDate(estimatedDeliveryDate), deliveryDate(deliveryDate) {}

void Shipment::display() const {
    std::cout << "=== Envio ===" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "State: " << state << std::endl;
    std::cout << "Cost: " << cost << std::endl;
    std::cout << "Priority: " << priority << std::endl;
    std::cout << "TotalPrice: " << totalPrice << std::endl;
    std::cout << "TotalWeight: " << totalWeight << std::endl;
    std::cout << "ShipmentManagerId: " << shimpmentManagerId << std::endl;
    std::cout << "DistributionCenterId: " << distributionCenterId << std::endl;
    std::cout << "OriginId: " << originId << std::endl;
    std::cout << "DestinationId: " << destinationId << std::endl;
    std::cout << "ClientId: " << clientId << std::endl;
    std::cout << "CreateDate: " << dateToStr(createDate) << std::endl;
    std::cout << "LeftWarehouseDate: " << dateToStr(leftWarehouseDate) << std::endl;
    std::cout << "EstimatedDeliveryDate: " << dateToStr(estimatedDeliveryDate) << std::endl;
    std::cout << "DeliveryDate: " << dateToStr(deliveryDate) << std::endl;
    
    // Iterar manualmente sobre packages en lugar de range-based loop
    std::cout << "============" << std::endl;
    Node* current = packages.getHead();
    do {
        try {
            Package pkg = std::any_cast<Package>(current->getData());
            pkg.display();
        } catch (const std::bad_any_cast&) {}
        current = current->getNext();
    } while (current != nullptr);
    std::cout << "============" << std::endl;
}

int Shipment::getId() const { return id; }
const std::string& Shipment::getState() const { return state; }
double Shipment::getCost() const { return cost; }
int Shipment::getPriority() const { return priority; }
double Shipment::getTotalPrice() const { return totalPrice; }
double Shipment::getTotalWeight() const { return totalWeight; }
int Shipment::getShimpmentManagerId() const { return shimpmentManagerId; }
std::string Shipment::getDistributionCenterId() const { return distributionCenterId; }
const List& Shipment::getPackages() const { return packages; }
std::string Shipment::getOriginId() const { return originId; }
std::string Shipment::getDestinationId() const { return destinationId; }
int Shipment::getClientId() const { return clientId; }
time_t Shipment::getCreateDate() const { return createDate; }
time_t Shipment::getLeftWarehouseDate() const { return leftWarehouseDate; }
time_t Shipment::getEstimatedDeliveryDate() const { return estimatedDeliveryDate; }
time_t Shipment::getDeliveryDate() const { return deliveryDate; }