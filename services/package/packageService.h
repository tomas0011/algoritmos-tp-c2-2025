#ifndef PACKAGE_SERVICE_H
#define PACKAGE_SERVICE_H

#include "../../entities/package/Package.h"
#include "../../utils/dataStructures/list/List.h"

class PackageService {
private:
    List& packages;

public:
    PackageService(List& packagesList);

    // CRUD operations
    void createPackage(int id, const std::string& nombre, double price, int priority, double weight);
    Package* getPackageById(int id);
    void updatePackage(int id, const std::string& nombre, double price, int priority, double weight);
    void deletePackage(int id);

    // Utility functions
    void displayAllPackages();
    int getPackageCount();
};

#endif // PACKAGE_SERVICE_H
