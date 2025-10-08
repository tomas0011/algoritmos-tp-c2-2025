#include "DistributionCenter.h"
#include <iostream>

DistributionCenter::DistributionCenter(
    int id,
    const std::string& name,
    const std::string& city,
    int capacity,
    int dalyPackages
)
    : id(id), name(name), city(city), capacity(capacity), dalyPackages(dalyPackages) {}

void DistributionCenter::display() const {
    std::cout << "ID: " << id << ", Name: " << name << ", City: " << city << ", Capacity: " << capacity << ", DalyPackages: " << dalyPackages << std::endl;
}
