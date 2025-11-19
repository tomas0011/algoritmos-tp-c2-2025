#ifndef PACKAGE_H
#define PACKAGE_H
#include <string>

class Package {
private:
    int id;
    std::string name;
    double price;
    int priority;
    double weight;


public:
    Package(int id, const std::string& name, double price, int priority, double weight);
    void display() const;

    // Getters
    int getId() const;
    std::string getName() const;
    double getPrice() const;
    int getPriority() const;
    double getWeight() const;

};

#endif // PACKAGE_H