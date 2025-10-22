#ifndef CONNECTION_H
#define CONNECTION_H

class Connection {
private:
    int id;
    int distributionCenterOrigin;
    int distributionCenterDestination;
    double distance;

public:
    Connection(int id, int distributionCenterOrigin, int distributionCenterDestination, double distance);
    void display() const;

    // Getters
    int getId() const;
    int getDistributionCenterOrigin() const;
    int getDistributionCenterDestination() const;
    double getDistance() const;
};

#endif // CONNECTION_H