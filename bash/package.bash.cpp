#include "package.bash.h"
#include "services/initializeServices.h"
#include <iostream>
#include <string>

void showPackageMenu() {
    int choice;
    do {
        std::cout << "\n=== Gestion de Paquetes ===\n";
        std::cout << "1. Crear un nuevo paquete\n";
        std::cout << "2. Mostrar informacion de un paquete por ID\n";
        std::cout << "3. Actualizar un paquete\n";
        std::cout << "4. Eliminar un paquete\n";
        std::cout << "5. Mostrar todos los paquetes\n";
        std::cout << "0. Volver al menú principal\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int id, priority;
                double price, weight;

                std::cout << "Ingrese el ID del paquete: ";
                std::cin >> id;
                std::string name;
                std::cout << "Ingrese el nombre: ";
                std::cin >> name;
                std::cout << "Ingrese el precio: ";
                std::cin >> price;
                std::cout << "Ingrese la prioridad (1-5): ";
                std::cin >> priority;
                std::cout << "Ingrese el peso: ";
                std::cin >> weight;

                packageService->createPackage(id, name, price, priority, weight);
                break;
            }
            case 2: {
                int id;
                std::cout << "Ingrese el ID del paquete: ";
                std::cin >> id;

                Package* pkg = packageService->getPackageById(id);
                if (pkg != nullptr) {
                    pkg->display();
                } else {
                    std::cout << "Paquete no encontrado." << std::endl;
                }
                break;
            }
            case 3: {
                int id, priority;
                double price, weight;

                std::cout << "Ingrese el ID del paquete a actualizar: ";
                std::cin >> id;

                Package* existingPkg = packageService->getPackageById(id);
                if (existingPkg == nullptr) {
                    std::cout << "Paquete no encontrado." << std::endl;
                    break;
                }

                                
                std::string name;
                std::cout << "Ingrese el nuevo nombre: ";
                std::cin >> name;
                std::cout << "Ingrese el nuevo precio: ";
                std::cin >> price;
                std::cout << "Ingrese la nueva prioridad (1-5): ";
                std::cin >> priority;
                std::cout << "Ingrese el nuevo peso: ";
                std::cin >> weight;

                packageService->updatePackage(id, name, price, priority, weight);
                break;
            }
            case 4: {
                int id;
                std::cout << "Ingrese el ID del paquete a eliminar: ";
                std::cin >> id;

                char confirm;
                std::cout << "¿Esta seguro de eliminar el paquete con ID " << id << "? (s/n): ";
                std::cin >> confirm;

                if (confirm == 's' || confirm == 'S') {
                    packageService->deletePackage(id);
                } else {
                    std::cout << "Operacion cancelada." << std::endl;
                }
                break;
            }
            case 5:
                packageService->displayAllPackages();
                break;
            case 0:
                std::cout << "Volviendo al menu principal...\n";
                break;
            default:
                std::cout << "Opcion invalida. Intente de nuevo.\n";
                break;
        }
    } while (choice != 0);
}
