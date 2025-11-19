#include "Connection.h"
#include <iostream>

Connection::Connection(int id, const std::string& distributionCenterOrigin, const std::string& distributionCenterDestination, double distance)
    : id(id), distributionCenterOrigin(distributionCenterOrigin), distributionCenterDestination(distributionCenterDestination), distance(distance) {}

void Connection::display() const {
    std::cout << "ID: " << id << ", Origen: " << distributionCenterOrigin << ", Destino: " << distributionCenterDestination << ", Distancia: " << distance << std::endl;
}

int Connection::getId() const { return id; }
const std::string& Connection::getDistributionCenterOrigin() const { return distributionCenterOrigin; }
const std::string& Connection::getDistributionCenterDestination() const { return distributionCenterDestination; }
double Connection::getDistance() const { return distance; }