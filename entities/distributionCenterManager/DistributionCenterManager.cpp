#include "DistributionCenterManager.h"
#include <iostream>

void DistributionCenterManager::createDistributionCenter(int id, std::string name, std::string city, int capacity, int dailyPackages, int employees) {
    DistributionCenter center(id, name, city, capacity, dailyPackages, employees);
    centers[id] = center;
    
    std::cout << "Distribution Center created: " << name << " in " << city << std::endl;

}

void DistributionCenterManager::getCenters() {
    std::cout << "List of Distribution Centers:" << std::endl;
    for (const auto& par : centers) {
        const DistributionCenter& center = par.second;
        std::cout << "ID: " << center.id 
                  << ", Name: " << center.name 
                  << ", City: " << center.city 
                  << ", Capacity: " << center.capacity 
                  << ", Daily Packages: " << center.dailyPackages 
                  << ", Employees: " << center.employees 
                  << std::endl;
    }
}