#include "employeeService.h"
#include <iostream>

EmployeeService::EmployeeService(List& employeesList) : employees(employeesList) {}

void EmployeeService::createEmployee(int id, const std::string& name, int distributionCenterId) {
    Employee newEmployee(id, name, distributionCenterId);
    employees.push(newEmployee);
    std::cout << "Employee created successfully." << std::endl;
}

Employee* EmployeeService::getEmployeeById(int id) {
    Node* current = employees.getHead();
    while (current != nullptr) {
        try {
            Employee emp = std::any_cast<Employee>(current->getData());
            if (emp.getId() == id) {
                return new Employee(emp); // Return a copy
            }
        } catch (const std::bad_any_cast& e) {
            // Skip invalid entries
        }
        current = current->getNext();
    }
    return nullptr;
}

void EmployeeService::updateEmployee(int id, const std::string& name, int distributionCenterId) {
    List newList;
    Node* current = employees.getHead();
    bool found = false;

    while (current != nullptr) {
        try {
            Employee emp = std::any_cast<Employee>(current->getData());
            if (emp.getId() == id) {
                Employee updatedEmployee(id, name, distributionCenterId);
                newList.push(updatedEmployee);
                found = true;
            } else {
                newList.push(emp);
            }
        } catch (const std::bad_any_cast& e) {
            // Skip invalid entries
        }
        current = current->getNext();
    }

    if (found) {
        employees = newList;
        std::cout << "Employee updated successfully." << std::endl;
    } else {
        std::cout << "Employee with ID " << id << " not found." << std::endl;
    }
}

void EmployeeService::deleteEmployee(int id) {
    List newList;
    Node* current = employees.getHead();
    bool found = false;

    while (current != nullptr) {
        try {
            Employee emp = std::any_cast<Employee>(current->getData());
            if (emp.getId() == id) {
                found = true;
            } else {
                newList.push(emp);
            }
        } catch (const std::bad_any_cast& e) {
            // Skip invalid entries
        }
        current = current->getNext();
    }

    if (found) {
        employees = newList;
        std::cout << "Employee deleted successfully." << std::endl;
    } else {
        std::cout << "Employee with ID " << id << " not found." << std::endl;
    }
}

void EmployeeService::displayAllEmployees() {
    std::cout << "Employee List:" << std::endl;
    Node* current = employees.getHead();
    while (current != nullptr) {
        try {
            Employee emp = std::any_cast<Employee>(current->getData());
            emp.display();
        } catch (const std::bad_any_cast& e) {
            std::cout << "Error displaying Employee" << std::endl;
        }
        current = current->getNext();
    }
}

int EmployeeService::getEmployeeCount() {
    return employees.getSize();
}