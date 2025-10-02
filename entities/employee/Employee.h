#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class Employee {
private:
    int id;
    std::string name;
    std::string dni;

public:
    Employee(int id, const std::string& name, const std::string& dni);
    void display() const;
};

#endif // EMPLOYEE_H
