#ifndef DISTRIBUTION_CENTER_H
#define DISTRIBUTION_CENTER_H

#include <string>
#include <vector>
#include "../package/Package.h"

class DistributionCenter {
private:
    int id;
    std::string name;
    std::string city;
    int capacity;
    std::vector<Package> warehouse;

public:
    DistributionCenter(
        int id,
        const std::string& name,
        const std::string& city,
        int capacity,
        const std::vector<Package>& warehouse
    );
    void display() const;

    // Getters
    int getId() const;
    const std::string& getName() const;
    const std::string& getCity() const;
    int getCapacity() const;
    const std::vector<Package>& getWarehouse() const;
};

#endif // DISTRIBUTION_CENTER_H
