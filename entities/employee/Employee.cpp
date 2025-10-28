#include "Employee.h"
#include <iostream>

Employee::Employee(int id, const std::string& name, int distributionCenterId)
    : id(id), name(name), distributionCenterId(distributionCenterId) {}

void Employee::display() const {
    std::cout << "ID: " << id << ", Name: " << name << ", DistributionCenterId: " << distributionCenterId << std::endl;
}

int Employee::getId() const { return id; }
const std::string& Employee::getName() const { return name; }
int Employee::getDistributionCenterId() const { return distributionCenterId; }
