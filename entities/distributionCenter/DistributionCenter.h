#ifndef DISTRIBUTION_CENTER_H
#define DISTRIBUTION_CENTER_H

#include <string>

class DistributionCenter {
private:
    int id;
    std::string name;
    std::string city;
    int capacity;
    int dalyPackages;
    // std::string Employee;

public:
    DistributionCenter(
        int id,
        const std::string& name,
        const std::string& city,
        int capacity,
        int dalyPackages
    );
    void display() const;
};

#endif // DISTRIBUTION_CENTER_H
