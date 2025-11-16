#include "bash.h"
#include "services/initializeServices.h"
#include "storage/mockData.h"
#include <iostream>
#include <string>


void showMenu() {
    int choice;
    do {
        std::cout << "\n=== Menu de Entidades ===\n";
        std::cout << "1. Listar Paquetes\n";
        std::cout << "2. Listar Envios\n";
        std::cout << "3. Listar Gestores de Envios\n";
        std::cout << "4. Listar Transportes\n";
        std::cout << "5. Listar Clientes\n";
        std::cout << "6. Listar Conexiones\n";
        std::cout << "7. Listar Centros de Distribucion\n";
        std::cout << "8. Listar Empleados\n";
        std::cout << "9. Listar Gestores de Centros de Distribucion\n";
        std::cout << "10. ITEM A - Gestion de Centros (HashTable)\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                packageService->displayAllPackages();
                break;
            case 2:
                shipmentService->displayAllShipments();
                break;
            case 3:
                displayMockShipmentManagers();
                break;
            case 4:
                displayMockTransports();
                break;
            case 5:
                displayMockClients();
                break;
            case 6:
                displayMockConnections();
                break;
            case 7:
                displayMockDistributionCenters();
                break;
            case 8:
                displayMockEmployees();
                break;
            case 9:
                displayMockDistributionCenterManagers();
                break;
            case 10:
                showDistributionCenterMenu();
                break;
            case 0:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opcion invalida. Intente de nuevo.\n";
                break;
        }
    } while (choice != 0);
}


void showDistributionCenterMenu() {
    int choice;
    do {
        std::cout << "\n=== Gestion de Centros de Distribucion (Item A) ===\n";
        std::cout << "1. Mostrar informacion de un centro especifico\n";
        std::cout << "2. Agregar un nuevo centro\n";
        std::cout << "3. Eliminar un centro existente\n";
        std::cout << "4. Actualizar informacion de un centro\n";
        std::cout << "5. Mostrar todos los centros\n";
        std::cout << "6. Mostrar centros ordenados por capacidad\n";
        std::cout << "7. Mostrar centros ordenados por paquetes procesados\n";
        std::cout << "8. Mostrar centros ordenados por cantidad de empleados\n";
        std::cout << "9. Mostrar estadisticas generales\n";
        std::cout << "10. Calcular camino minimo entre centros (proximamente)\n";
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
                distributionCenterService->displayAllCenters();
                break;
            case 6:
                distributionCenterService->displayCentersSortedByCapacity();
                break;
            case 7:
                distributionCenterService->displayCentersSortedByPackages();
                break;
            case 8:
                distributionCenterService->displayCentersSortedByEmployees();
                break;
            case 9:
                distributionCenterService->displayStatistics();
                break;
            case 10: {
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


