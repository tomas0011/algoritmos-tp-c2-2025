#include "distributionCenterService.h"

DistributionCenterService::DistributionCenterService(Graph& networkRef)
    : network(networkRef) {} //constructor

void DistributionCenterService::createCenter(int id, const std::string& name, const std::string& city,
                                             int capacity, int warehouse, int employees) {
    if (network.existsNode(id)) {
        std::cout << "Center with ID " << id << " already exists." << std::endl;
        return;
    }

    DistributionCenter* newCenter = new DistributionCenter(id, name, city, capacity, warehouse ,employees);
    network.addNode(newCenter);
    std::cout << "Distribution center created successfully." << std::endl;
}

DistributionCenter* DistributionCenterService::getCenterById(int id) {
    return network.getNode(id);
}

void DistributionCenterService::connectCenters(int id1, int id2, double distance) {
    if (!network.existsNode(id1) || !network.existsNode(id2)) {
        std::cout << "One or both centers do not exist." << std::endl;
        return;
    }

    if (network.existsEdge(id1, id2)) {
        std::cout << "Connection already exists between centers " << id1 << " and " << id2 << "." << std::endl;
        return;
    }

    network.addEdge(id1, id2, distance);
    std::cout << "Connection established successfully between centers " << id1
              << " and " << id2 << " (" << distance << " km)." << std::endl;
}

void DistributionCenterService::displayAllCenters() {
    std::vector<DistributionCenter*> centers = network.getAllCenters();
    std::cout << "\n=== All Distribution Centers ===" << std::endl;
    for (auto* c : centers) {
        c->display();
    }
}

void DistributionCenterService::displayConnections(int id) {
    if (!network.existsNode(id)) {
        std::cout << "Center with ID " << id << " not found." << std::endl;
        return;
    }
    std::cout << "\nConnections for Center " << id << ":" << std::endl;
    std::vector<int> connections = network.getConnections(id);
    for (int dest : connections) {
        double dist = network.getDistance(id, dest);
        std::cout << " -> Center " << dest << " (" << dist << " km)" << std::endl;
    }
}