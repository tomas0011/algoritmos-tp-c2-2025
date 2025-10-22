#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class Employee {
private:
    int id;
    std::string name;
    int distributionCenterId;

public:
    Employee(int id, const std::string& name, int distributionCenterId);
    void display() const;

    // Getters
    int getId() const;
    const std::string& getName() const;
    int getDistributionCenterId() const;
};

#endif // EMPLOYEE_H
