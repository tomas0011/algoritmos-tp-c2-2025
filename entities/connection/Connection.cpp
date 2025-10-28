#include "Connection.h"
#include <iostream>

Connection::Connection(int id, int distributionCenterOrigin, int distributionCenterDestination, double distance)
    : id(id), distributionCenterOrigin(distributionCenterOrigin), distributionCenterDestination(distributionCenterDestination), distance(distance) {}

void Connection::display() const {
    std::cout << "ID: " << id << ", Origin: " << distributionCenterOrigin << ", Destination: " << distributionCenterDestination << ", Distance: " << distance << std::endl;
}

int Connection::getId() const { return id; }
int Connection::getDistributionCenterOrigin() const { return distributionCenterOrigin; }
int Connection::getDistributionCenterDestination() const { return distributionCenterDestination; }
double Connection::getDistance() const { return distance; }