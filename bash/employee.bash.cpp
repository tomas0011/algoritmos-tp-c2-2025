#include "employee.bash.h"
#include "services/initializeServices.h"
#include <iostream>
#include <string>

void showEmployeeMenu() {
    int choice;
    do {
        std::cout << "\n=== Gestion de Empleados ===\n";
        std::cout << "1. Crear un nuevo empleado\n";
        std::cout << "2. Mostrar informacion de un empleado por ID\n";
        std::cout << "3. Actualizar un empleado\n";
        std::cout << "4. Eliminar un empleado\n";
        std::cout << "5. Mostrar todos los empleados\n";
        std::cout << "0. Volver al menú principal\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int id, distributionCenterId;
                std::string name;

                std::cout << "Ingrese el ID del empleado: ";
                std::cin >> id;
                std::cout << "Ingrese el nombre: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Ingrese el ID del centro de distribucion: ";
                std::cin >> distributionCenterId;

                employeeService->createEmployee(id, name, distributionCenterId);
                break;
            }
            case 2: {
                int id;
                std::cout << "Ingrese el ID del empleado: ";
                std::cin >> id;

                Employee* employee = employeeService->getEmployeeById(id);
                if (employee != nullptr) {
                    employee->display();
                    delete employee;
                } else {
                    std::cout << "Empleado no encontrado." << std::endl;
                }
                break;
            }
            case 3: {
                int id, distributionCenterId;
                std::string name;

                std::cout << "Ingrese el ID del empleado a actualizar: ";
                std::cin >> id;

                Employee* existing = employeeService->getEmployeeById(id);
                if (existing == nullptr) {
                    std::cout << "Empleado no encontrado." << std::endl;
                    break;
                }
                delete existing;

                std::cout << "Ingrese el nuevo nombre: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Ingrese el nuevo ID del centro de distribucion: ";
                std::cin >> distributionCenterId;

                employeeService->updateEmployee(id, name, distributionCenterId);
                break;
            }
            case 4: {
                int id;
                std::cout << "Ingrese el ID del empleado a eliminar: ";
                std::cin >> id;

                char confirm;
                std::cout << "¿Esta seguro de eliminar el empleado con ID " << id << "? (s/n): ";
                std::cin >> confirm;

                if (confirm == 's' || confirm == 'S') {
                    employeeService->deleteEmployee(id);
                } else {
                    std::cout << "Operacion cancelada." << std::endl;
                }
                break;
            }
            case 5:
                employeeService->displayAllEmployees();
                break;
            case 0:
                std::cout << "Volviendo al menú principal...\n";
                break;
            default:
                std::cout << "Opcion invalida. Intente de nuevo.\n";
                break;
        }
    } while (choice != 0);
}