#include "transport.bash.h"
#include "services/initializeServices.h"
#include <iostream>
#include <string>

void showTransportMenu() {
    int choice;
    do {
        std::cout << "\n=== Gestion de Transportes ===\n";
        std::cout << "1. Crear un nuevo transporte\n";
        std::cout << "2. Mostrar informacion de un transporte por ID\n";
        std::cout << "3. Actualizar un transporte\n";
        std::cout << "4. Eliminar un transporte\n";
        std::cout << "5. Mostrar todos los transportes\n";
        std::cout << "0. Volver al menú principal\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                double maxWeight;
                std::string type;

                std::cout << "Ingrese el ID del transporte: ";
                std::cin >> id;
                std::cout << "Ingrese el tipo: ";
                std::cin.ignore();
                std::getline(std::cin, type);
                std::cout << "Ingrese el peso maximo: ";
                std::cin >> maxWeight;

                transportService->createTransport(id, type, maxWeight);
                break;
            }
            case 2: {
                int id;
                std::cout << "Ingrese el ID del transporte: ";
                std::cin >> id;

                Transport* transport = transportService->getTransportById(id);
                if (transport != nullptr) {
                    transport->display();
                    delete transport;
                } else {
                    std::cout << "Transporte no encontrado." << std::endl;
                }
                break;
            }
            case 3: {
                int id;
                double maxWeight;
                std::string type;

                std::cout << "Ingrese el ID del transporte a actualizar: ";
                std::cin >> id;

                Transport* existing = transportService->getTransportById(id);
                if (existing == nullptr) {
                    std::cout << "Transporte no encontrado." << std::endl;
                    break;
                }
                delete existing;

                std::cout << "Ingrese el nuevo tipo: ";
                std::cin.ignore();
                std::getline(std::cin, type);
                std::cout << "Ingrese el nuevo peso maximo: ";
                std::cin >> maxWeight;

                transportService->updateTransport(id, type, maxWeight);
                break;
            }
            case 4: {
                int id;
                std::cout << "Ingrese el ID del transporte a eliminar: ";
                std::cin >> id;

                char confirm;
                std::cout << "¿Esta seguro de eliminar el transporte con ID " << id << "? (s/n): ";
                std::cin >> confirm;

                if (confirm == 's' || confirm == 'S') {
                    transportService->deleteTransport(id);
                } else {
                    std::cout << "Operacion cancelada." << std::endl;
                }
                break;
            }
            case 5:
                transportService->displayAllTransports();
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
