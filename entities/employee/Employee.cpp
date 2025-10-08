#include "Employee.h"
#include <iostream>

Employee::Employee(int id, const std::string& name, const std::string& dni)
    : id(id), name(name), dni(dni) {}

void Employee::display() const {
    std::cout << "ID: " << id << ", Name: " << name << ", DNI: " << dni << std::endl;
}
