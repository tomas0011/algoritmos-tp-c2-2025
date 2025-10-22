#ifndef PACKAGE_H
#define PACKAGE_H

class Package {
private:
    int id;
    double price;
    int priority;
    double weight;

public:
    Package(int id, double price, int priority, double weight);
    void display() const;

    // Getters
    int getId() const;
    double getPrice() const;
    int getPriority() const;
    double getWeight() const;
};

#endif // PACKAGE_H