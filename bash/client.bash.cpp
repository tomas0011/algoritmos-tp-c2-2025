#include "client.bash.h"
#include "services/initializeServices.h"
#include <iostream>
#include <string>

void showClientMenu() {
    int choice;
    do {
        std::cout << "\n=== Gestion de Clientes ===\n";
        std::cout << "1. Crear un nuevo cliente\n";
        std::cout << "2. Mostrar informacion de un cliente por ID\n";
        std::cout << "3. Actualizar un cliente\n";
        std::cout << "4. Eliminar un cliente\n";
        std::cout << "5. Mostrar todos los clientes\n";
        std::cout << "0. Volver al menu principal\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                std::string name;

                std::cout << "Ingrese el ID del cliente: ";
                std::cin >> id;
                std::cout << "Ingrese el nombre: ";
                std::cin.ignore();
                std::getline(std::cin, name);

                clientService->createClient(id, name);
                break;
            }
            case 2: {
                int id;
                std::cout << "Ingrese el ID del cliente: ";
                std::cin >> id;

                Client* client = clientService->getClientById(id);
                if (client != nullptr) {
                    client->display();
                    delete client;
                } else {
                    std::cout << "Cliente no encontrado." << std::endl;
                }
                break;
            }
            case 3: {
                int id;
                std::string name;

                std::cout << "Ingrese el ID del cliente a actualizar: ";
                std::cin >> id;

                Client* existing = clientService->getClientById(id);
                if (existing == nullptr) {
                    std::cout << "Cliente no encontrado." << std::endl;
                    break;
                }
                delete existing;

                std::cout << "Ingrese el nuevo nombre: ";
                std::cin.ignore();
                std::getline(std::cin, name);

                clientService->updateClient(id, name);
                break;
            }
            case 4: {
                int id;
                std::cout << "Ingrese el ID del cliente a eliminar: ";
                std::cin >> id;

                char confirm;
                std::cout << "¿Esta seguro de eliminar el cliente con ID " << id << "? (s/n): ";
                std::cin >> confirm;

                if (confirm == 's' || confirm == 'S') {
                    clientService->deleteClient(id);
                } else {
                    std::cout << "Operacion cancelada." << std::endl;
                }
                break;
            }
            case 5:
                clientService->displayAllClients();
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
