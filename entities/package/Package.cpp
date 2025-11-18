#include "Package.h"
#include <iostream>

Package::Package(int id, double price, int priority, double weight)
    : id(id), price(price), priority(priority), weight(weight) {}

void Package::display() const {
    std::cout << "ID: " << id << ", Price: " << price << ", Priority: " << priority << ", Weight: " << weight << std::endl;
}

int Package::getId() const { return id; }
double Package::getPrice() const { return price; }
int Package::getPriority() const { return priority; }
double Package::getWeight() const { return weight; }
