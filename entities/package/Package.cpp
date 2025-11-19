#include "Package.h"
#include <iostream>

Package::Package(int id, const std::string& name, double price, int priority, double weight)
    : id(id), name(name), price(price), priority(priority), weight(weight) {}

void Package::display() const {
    std::cout << "ID: " << id << ", Name: " << name << ", Price: " << price << ", Priority: " << priority << ", Weight: " << weight << std::endl;
}

int Package::getId() const { return id; }
std::string Package::getName() const { return name; }
double Package::getPrice() const { return price; }
int Package::getPriority() const { return priority; }
double Package::getWeight() const { return weight; }
