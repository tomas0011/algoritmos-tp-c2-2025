#ifndef EMPLOYEE_SERVICE_H
#define EMPLOYEE_SERVICE_H

#include "../../entities/employee/Employee.h"
#include "../../utils/dataStructures/list/List.h"

class EmployeeService {
private:
    List& employees;
public:
    EmployeeService(List& employeesList);

    // CRUD operations
    void createEmployee(int id, const std::string& name, int distributionCenterId);
    Employee* getEmployeeById(int id);
    void updateEmployee(int id, const std::string& name, int distributionCenterId);
    void deleteEmployee(int id);

    // Utility functions
    void displayAllEmployees();
    int getEmployeeCount();
};

#endif // EMPLOYEE_SERVICE_H