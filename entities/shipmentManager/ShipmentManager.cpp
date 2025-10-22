#include "ShipmentManager.h"
#include <iostream>

ShipmentManager::ShipmentManager(int id, int transportId, const std::vector<Connection>& path, int distributionCenterId)
    : id(id), transportId(transportId), path(path), distributionCenterId(distributionCenterId) {}

void ShipmentManager::display() const {
    std::cout << "ID: " << id << ", TransportId: " << transportId << ", DistributionCenterId: " << distributionCenterId << std::endl;
    for (const auto& conn : path) {
        conn.display();
    }
}

int ShipmentManager::getId() const { return id; }
int ShipmentManager::getTransportId() const { return transportId; }
const std::vector<Connection>& ShipmentManager::getPath() const { return path; }
int ShipmentManager::getDistributionCenterId() const { return distributionCenterId; }