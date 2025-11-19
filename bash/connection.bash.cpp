#include "connection.bash.h"
#include "bash.h"
#include "services/initializeServices.h"
#include <iostream>

void showConnectionMenu() {
    int choice;
    do {
        std::cout << "\n=== Gestion de Conexiones ===\n";
        std::cout << "1. Crear una nueva conexion\n";
        std::cout << "2. Mostrar informacion de una conexion por ID\n";
        std::cout << "3. Actualizar una conexion\n";
        std::cout << "4. Eliminar una conexion\n";
        std::cout << "5. Mostrar todas las conexiones\n";
        std::cout << "0. Volver al menu principal\n";
        std::cout << "Seleccione una opcion: ";
        choice = getValidIntInput(0, 5);

        switch (choice) {
            case 1: {
                std::string origin, destination;
                double distance;

                std::cout << "Ingrese el codigo del centro origen (ej: BUE, MZA, CBA): ";
                origin = getValidStringInput();
                std::cout << "Ingrese el codigo del centro destino (ej: BUE, MZA, CBA): ";
                destination = getValidStringInput();
                std::cout << "Ingrese la distancia (km): ";
                distance = getValidDoubleInput(0.1, 10000.0);

                connectionService->createConnection(origin, destination, distance);
                break;
            }
            case 2: {
                int id;
                std::cout << "Ingrese el ID de la conexion: ";
                id = getValidIntInput(1, 99999);

                Connection* connection = connectionService->getConnectionById(id);
                if (connection != nullptr) {
                    connection->display();
                    delete connection;
                } else {
                    std::cout << "Conexion no encontrada." << std::endl;
                }
                break;
            }
            case 3: {
                int id;
                std::string origin, destination;
                double distance;

                std::cout << "Ingrese el ID de la conexion a actualizar: ";
                id = getValidIntInput(1, 99999);

                Connection* existing = connectionService->getConnectionById(id);
                if (existing == nullptr) {
                    std::cout << "Conexion no encontrada." << std::endl;
                    break;
                }
                delete existing;

                std::cout << "Ingrese el nuevo codigo del centro origen (ej: BUE, MZA, CBA): ";
                origin = getValidStringInput();
                std::cout << "Ingrese el nuevo codigo del centro destino (ej: BUE, MZA, CBA): ";
                destination = getValidStringInput();
                std::cout << "Ingrese la nueva distancia (km): ";
                distance = getValidDoubleInput(0.1, 10000.0);

                connectionService->updateConnection(id, origin, destination, distance);
                break;
            }
            case 4: {
                int id;
                std::cout << "Ingrese el ID de la conexion a eliminar: ";
                id = getValidIntInput(1, 99999);

                char confirm;
                std::cout << "¿Esta seguro de eliminar la conexion con ID " << id << "? (s/n): ";
                std::cin >> confirm;

                if (confirm == 's' || confirm == 'S') {
                    connectionService->deleteConnection(id);
                } else {
                    std::cout << "Operacion cancelada." << std::endl;
                }
                break;
            }
            case 5:
                connectionService->displayAllConnections();
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
