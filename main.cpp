#include "entities/distributionCenter/DistributionCenter.h"
#include "entities/employee/Employee.h"
#include <iostream>

int main() {
    Employee employee1(1, "Tomas Vasquez", "123456");
    employee1.display();

    DistributionCenter distributionCenter1(
        1,
        "Correo Argentino - Pedro diaz",
        "Tesei",
        100,
        5
    );
    distributionCenter1.display();

    return 0;
}
