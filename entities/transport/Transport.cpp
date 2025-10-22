#include "Transport.h"
#include <iostream>

Transport::Transport(int id, const std::string& type, double maxWeight)
    : id(id), type(type), maxWeight(maxWeight) {}

void Transport::display() const {
    std::cout << "ID: " << id << ", Type: " << type << ", MaxWeight: " << maxWeight << std::endl;
}

int Transport::getId() const { return id; }
const std::string& Transport::getType() const { return type; }
double Transport::getMaxWeight() const { return maxWeight; }