#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <string>

class Transport {
private:
    int id;
    std::string type;
    double maxWeight;

public:
    Transport(int id, const std::string& type, double maxWeight);
    void display() const;

    // Getters
    int getId() const;
    const std::string& getType() const;
    double getMaxWeight() const;
};

#endif // TRANSPORT_H