#include "ShipmentManager.h"
#include <iostream>
#include "entities/distributionCenter/DistributionCenter.h"

ShipmentManager::ShipmentManager(int id, int transportId, const List& path, int distributionCenterId)
    : id(id), transportId(transportId), path(path), distributionCenterId(distributionCenterId) {}

void ShipmentManager::display() const {
    std::cout << "ID: " << id << ", TransportId: " << transportId
              << ", DistributionCenterId: " << distributionCenterId << std::endl;
    
    Node* current = path.getHead();
    while (current != nullptr) {
        try {
            Connection conn = std::any_cast<Connection>(current->getData());
            conn.display();
        } catch (const std::bad_any_cast&) {
            // skip
        }
        current = current->getNext();
    }
}

int ShipmentManager::getId() const { return id; }
int ShipmentManager::getTransportId() const { return transportId; }
List ShipmentManager::getPath() const { return path; }
int ShipmentManager::getDistributionCenterId() const { return distributionCenterId; }
