#include "packageService.h"
#include <iostream>

PackageService::PackageService(List& packagesList) : packages(packagesList) {}

void PackageService::createPackage(int id, const std::string& name, double price, int priority, double weight) {
    Package newPackage(id, name, price, priority, weight);
    packages.push(newPackage);
    std::cout << "Package created successfully." << std::endl;
}

Package* PackageService::getPackageById(int id) {
    Node* current = packages.getHead();
    while (current != nullptr) {
        try {
            Package pkg = std::any_cast<Package>(current->getData());
            if (pkg.getId() == id) {
                return new Package(pkg); // Return a copy
            }
        } catch (const std::bad_any_cast& e) {
            // Skip invalid entries
        }
        current = current->getNext();
    }
    return nullptr;
}

void PackageService::updatePackage(int id,const std::string& name, double price, int priority, double weight) {
    List newList;
    Node* current = packages.getHead();
    bool found = false;

    while (current != nullptr) {
        try {
            Package pkg = std::any_cast<Package>(current->getData());
            if (pkg.getId() == id) {
                Package updatedPackage(id, name, price, priority, weight);
                newList.push(updatedPackage);
                found = true;
            } else {
                newList.push(pkg);
            }
        } catch (const std::bad_any_cast& e) {
            // Skip invalid entries
        }
        current = current->getNext();
    }

    if (found) {
        packages = newList;
        std::cout << "Package updated successfully." << std::endl;
    } else {
        std::cout << "Package with ID " << id << " not found." << std::endl;
    }
}

void PackageService::deletePackage(int id) {
    List newList;
    Node* current = packages.getHead();
    bool found = false;

    while (current != nullptr) {
        try {
            Package pkg = std::any_cast<Package>(current->getData());
            if (pkg.getId() != id) {
                newList.push(pkg);
            } else {
                found = true;
            }
        } catch (const std::bad_any_cast& e) {
            // Skip invalid entries
        }
        current = current->getNext();
    }

    if (found) {
        packages = newList;
        std::cout << "Package deleted successfully." << std::endl;
    } else {
        std::cout << "Package with ID " << id << " not found." << std::endl;
    }
}

void PackageService::displayAllPackages() {
    std::cout << "All Packages:" << std::endl;
    Node* current = packages.getHead();
    while (current != nullptr) {
        try {
            Package pkg = std::any_cast<Package>(current->getData());
            pkg.display();
        } catch (const std::bad_any_cast& e) {
            std::cout << "Error displaying package" << std::endl;
        }
        current = current->getNext();
    }
}

int PackageService::getPackageCount() {
    return packages.getSize();
}
