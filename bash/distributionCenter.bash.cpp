#include "distributionCenter.bash.h"
#include "bash.h"
#include "services/initializeServices.h"
#include <iostream>
#include <string>
#include <ctime>
#include "../utils/dataStructures/list/List.h"

void showDistributionCenterMenu() {
    int choice;
    do {
        std::cout << "\n=== Gestion de Centros de Distribucion (Item A) ===\n";
        std::cout << "1. Obtener centro de distribucion. (A.1)\n";
        std::cout << "2. Agregar centro de distribucion. (A.2)\n";
        std::cout << "3. Eliminar centro de distribucion. (A.3)\n";
        std::cout << "4. Actualizar centro de distribucion.\n";
        std::cout << "5. Obtener centros de distribucion. (A.4)\n";
        std::cout << "6. Conectar centros de distribucion.\n";
        std::cout << "7. Mostrar estadisticas generales.\n";
        std::cout << "8. Calcular camino minimo entre centros. (A.5)\n";
        std::cout << "9. Agregar paquete a un centro.\n";
        std::cout << "10. Mostrar paquetes del warehouse de un centro.\n";
        std::cout << "0. Volver al menu principal\n";
        std::cout << "Seleccione una opcion: ";
        choice = getValidIntInput(0, 8);

        switch (choice) {
            case 1: {
                std::string code;
                std::cout << "Ingrese el codigo del centro (ej: CBA, MZA, BUE): ";
                code = getValidStringInput();
                distributionCenterService->showCenterInfo(code);
                break;
            }
            case 2: {
                std::string code, name, city;
                int capacity, dailyPackages, numEmployees;
                
                std::cout << "Ingrese el codigo del centro (3 letras, ej: CBA): ";
                code = getValidStringInput();
                std::cout << "Ingrese el nombre del centro: ";
                name = getValidStringInput();
                std::cout << "Ingrese la ciudad: ";
                city = getValidStringInput();
                std::cout << "Ingrese la capacidad: ";
                capacity = getValidIntInput(1, 10000);
                std::cout << "Ingrese los paquetes diarios: ";
                dailyPackages = getValidIntInput(1, 1000);
                std::cout << "Ingrese el número de empleados: ";
                numEmployees = getValidIntInput(1, 100);
                
                distributionCenterService->addCenter(code, name, city, capacity, dailyPackages, numEmployees);
                break;
            }
            case 3: {
                std::string code;
                std::cout << "Ingrese el codigo del centro a eliminar: ";
                code = getValidStringInput();
                
                char confirm;
                std::cout << "¿Esta seguro de eliminar el centro '" << code << "'? (s/n): ";
                std::string confirmStr = getValidStringInput();
                confirm = confirmStr.empty() ? 'n' : confirmStr[0];
                
                if (confirm == 's' || confirm == 'S') {
                    distributionCenterService->removeCenter(code);
                } else {
                    std::cout << "Operacion cancelada." << std::endl;
                }
                break;
            }
            case 4: {
                std::string code;
                int capacity, dailyPackages, numEmployees;
                
                std::cout << "Ingrese el codigo del centro a actualizar: ";
                code = getValidStringInput();
                
                if (!distributionCenterService->centerExists(code)) {
                    std::cout << "Error: Centro no encontrado." << std::endl;
                    break;
                }
                
                std::cout << "Ingrese la nueva capacidad: ";
                capacity = getValidIntInput(1, 10000);
                std::cout << "Ingrese los nuevos paquetes diarios: ";
                dailyPackages = getValidIntInput(1, 1000);
                std::cout << "Ingrese el nuevo número de empleados: ";
                numEmployees = getValidIntInput(1, 100);
                
                distributionCenterService->updateCenter(code, capacity, dailyPackages, numEmployees);
                break;
            }
            case 5:
                showDisplayAllDistributionCenterMenu();
                break;
            case 6: {
                std::string origin, destination;
                int distance;
                std::cout << "Ingrese el codigo del centro origen: ";
                origin = getValidStringInput();
                std::cout << "Ingrese el codigo del centro destino: ";
                destination = getValidStringInput();
                std::cout << "Ingrese la distancia entre estos centros: ";
                distance = getValidIntInput(1, 10000);
                distributionCenterService->addConnection(origin, destination, distance);
                break;
            }
            case 7:
                distributionCenterService->displayStatistics();
                break;
            case 8: {
                std::string origin, destination;
                std::cout << "Ingrese el codigo del centro origen: ";
                origin = getValidStringInput();
                std::cout << "Ingrese el codigo del centro destino: ";
                destination = getValidStringInput();
                
                distributionCenterService->calculateShortestPath(origin, destination);
                break;
            }
            case 9: {

                std::string centerCode, pkgId, recipient, address;
                float weight;


                std::cout << "Ingrese el codigo del centro: ";
                std::cin >> centerCode;

                std::cout << "Ingrese el ID del paquete: ";
                std::cin >> pkgId;

                std::cout << "Ingrese el destinatario: ";
                std::cin.ignore();
                std::getline(std::cin, recipient);

                std::cout << "Ingrese la direccion: ";
                std::getline(std::cin, address);

                std::cout << "Ingrese el peso (kg): ";
                std::cin >> weight;

                int id = std::stoi(pkgId);          
                double price = 0;                    
                int priority = 1;                    
                double weightDouble = static_cast<double>(weight);

                Package pkg(id, recipient, price, priority, weightDouble);


                distributionCenterService->addPackageToCenter(centerCode, pkg);
                break;
            }

            case 10: {
                std::string centerCode;
                std::cout << "Ingrese el codigo del centro: ";
                std::cin >> centerCode;

                // 1. Obtener la lista del warehouse
                List warehouse = distributionCenterService->getWarehouseOfCenter(centerCode);

                // 2. Validar si está vacío
                if (warehouse.isEmpty()) {
                    std::cout << "[INFO] No se encontraron paquetes en el centro: " 
                            << centerCode << "\n";
                    break;
                }

                // 3. Mostrar los paquetes
                std::cout << "\n=== Paquetes en warehouse del centro " 
                        << centerCode << " ===\n";

                Node* current = warehouse.getHead();

                while (current != nullptr) {
                    try {
                        Package pkg = std::any_cast<Package>(current->getData());
                        pkg.display();

                    } catch (const std::bad_any_cast&) {
                        std::cout << "[ERROR] Un elemento del warehouse no es un Package válido.\n";
                    }

                    current = current->getNext();
                }

                break;
            }
            case 0:
                std::cout << "Volviendo al menu principal...\n";
                break;
            default:
                std::cout << "Opcion invalida. Intente de nuevo.\n";
                break;
        }
    } while (choice != 0);
}

void showDisplayAllDistributionCenterMenu() {
    int choice;
    do {
        std::cout << "\n=== Obtener Centros de Distribucion (Item A.4) ===\n";
        std::cout << "1. Obtener todos los centros de distribucion.\n";
        std::cout << "2. Obtener centros ordenados por capacidad.\n";
        std::cout << "3. Obtener centros ordenados por paquetes procesados.\n";
        std::cout << "4. Obtener centros ordenados por cantidad de empleados.\n";
        std::cout << "0. Volver al menu principal\n";
        std::cout << "Seleccione una opcion: ";
        choice = getValidIntInput(0, 4);

        switch (choice) {
            case 1:
                distributionCenterService->displayAllCenters();
                break;
            case 2:
                distributionCenterService->displayCentersSortedByCapacity();
                break;
            case 3:
                distributionCenterService->displayCentersSortedByPackages();
                break;
            case 4:
                distributionCenterService->displayCentersSortedByEmployees();
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
