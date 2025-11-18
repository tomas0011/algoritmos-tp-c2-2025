#include "distributionCenter.bash.h"
#include "services/initializeServices.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

void showDistributionCenterMenu() {
    int choice;
    do {
        std::cout << "\n=== Gestion de Centros de Distribucion (Item A) ===\n";
        std::cout << "1. Obtener centro de distribucion. (A.1)\n";
        std::cout << "2. Agregar centro de distribucion. (A.2)\n";
        std::cout << "3. Eliminar centro de distribucion. (A.3)\n";
        std::cout << "4. Actualizar centro de distribucion.\n";
        std::cout << "5. Obtener centros de distribucion. (A.4)\n";
        std::cout << "6. Mostrar estadisticas generales.\n";
        std::cout << "7. Calcular camino minimo entre centros. (A.5)\n";
        std::cout << "0. Volver al menú principal\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string code;
                std::cout << "Ingrese el codigo del centro (ej: CBA, MZA, BUE): ";
                std::cin >> code;
                distributionCenterService->showCenterInfo(code);
                break;
            }
            case 2: {
                std::string code, name, city;
                int capacity, dailyPackages, numEmployees;
                
                std::cout << "Ingrese el codigo del centro (3 letras, ej: CBA): ";
                std::cin >> code;
                std::cout << "Ingrese el nombre del centro: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Ingrese la ciudad: ";
                std::getline(std::cin, city);
                std::cout << "Ingrese la capacidad: ";
                std::cin >> capacity;
                std::cout << "Ingrese los paquetes diarios: ";
                std::cin >> dailyPackages;
                std::cout << "Ingrese el número de empleados: ";
                std::cin >> numEmployees;
                
                distributionCenterService->addCenter(code, name, city, capacity, dailyPackages, numEmployees);
                break;
            }
            case 3: {
                std::string code;
                std::cout << "Ingrese el codigo del centro a eliminar: ";
                std::cin >> code;
                
                char confirm;
                std::cout << "¿Esta seguro de eliminar el centro '" << code << "'? (s/n): ";
                std::cin >> confirm;
                
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
                std::cin >> code;
                
                if (!distributionCenterService->centerExists(code)) {
                    std::cout << "Error: Centro no encontrado." << std::endl;
                    break;
                }
                
                std::cout << "Ingrese la nueva capacidad: ";
                std::cin >> capacity;
                std::cout << "Ingrese los nuevos paquetes diarios: ";
                std::cin >> dailyPackages;
                std::cout << "Ingrese el nuevo número de empleados: ";
                std::cin >> numEmployees;
                
                distributionCenterService->updateCenter(code, capacity, dailyPackages, numEmployees);
                break;
            }
            case 5:
                showDisplayAllDistributionCenterMenu();
                break;
            case 6:
                distributionCenterService->displayStatistics();
                break;
            case 7: {
                std::string origin, destination;
                std::cout << "Ingrese el codigo del centro origen: ";
                std::cin >> origin;
                std::cout << "Ingrese el codigo del centro destino: ";
                std::cin >> destination;
                
                distributionCenterService->calculateShortestPath(origin, destination);
                break;
            }
            case 0:
                std::cout << "Volviendo al menú principal...\n";
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
        std::cout << "0. Volver al menú principal\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> choice;

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
                std::cout << "Volviendo al menú principal...\n";
                break;
            default:
                std::cout << "Opcion invalida. Intente de nuevo.\n";
                break;
        }
    } while (choice != 0);
}
