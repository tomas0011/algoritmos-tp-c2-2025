#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>

class Connection {
private:
    int id;
    std::string distributionCenterOrigin;
    std::string distributionCenterDestination;
    double distance;

public:
    Connection(int id, const std::string& distributionCenterOrigin, const std::string& distributionCenterDestination, double distance);
    void display() const;

    // Getters
    int getId() const;
    const std::string& getDistributionCenterOrigin() const;
    const std::string& getDistributionCenterDestination() const;
    double getDistance() const;
};

#endif // CONNECTION_H