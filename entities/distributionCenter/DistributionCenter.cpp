#include "DistributionCenter.h"
#include <iostream>

DistributionCenter::DistributionCenter(
    int id,
    const std::string& name,
    const std::string& city,
    int capacity,
    const std::vector<Package>& warehouse
)
    : id(id), name(name), city(city), capacity(capacity), warehouse(warehouse) {}

void DistributionCenter::display() const {
    std::cout << "ID: " << id << ", Name: " << name << ", City: " << city << ", Capacity: " << capacity << std::endl;
    std::cout << "Warehouse Packages:" << std::endl;
    for (const auto& pkg : warehouse) {
        pkg.display();
    }
}

int DistributionCenter::getId() const { return id; }
const std::string& DistributionCenter::getName() const { return name; }
const std::string& DistributionCenter::getCity() const { return city; }
int DistributionCenter::getCapacity() const { return capacity; }
const std::vector<Package>& DistributionCenter::getWarehouse() const { return warehouse; }
