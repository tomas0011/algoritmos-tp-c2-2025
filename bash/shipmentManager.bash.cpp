#include "shipmentManager.bash.h"
#include "services/initializeServices.h"
#include <iostream>

void showShipmentManagerMenu() {
    int choice;
    do {
        std::cout << "\n=== Gestion de Gestores de Envios ===\n";
        std::cout << "1. Crear un nuevo gestor de envio\n";
        std::cout << "2. Mostrar informacion de un gestor por ID\n";
        std::cout << "3. Actualizar un gestor de envio\n";
        std::cout << "4. Eliminar un gestor de envio\n";
        std::cout << "5. Mostrar todos los gestores de envios\n";
        std::cout << "0. Volver al menú principal\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int id, transportId, distributionCenterId;

                std::cout << "Ingrese el ID del gestor: ";
                std::cin >> id;
                std::cout << "Ingrese el ID del transporte: ";
                std::cin >> transportId;
                std::cout << "Ingrese el ID del centro de distribucion: ";
                std::cin >> distributionCenterId;

                List path;// vacío por simplicidad

                shipmentManagerService->createShipmentManager(id, transportId, path, distributionCenterId);
                break;
            }
            case 2: {
                int id;
                std::cout << "Ingrese el ID del gestor: ";
                std::cin >> id;

                ShipmentManager* sm = shipmentManagerService->getShipmentManagerById(id);
                if (sm != nullptr) {
                    sm->display();
                    delete sm;
                } else {
                    std::cout << "Gestor no encontrado." << std::endl;
                }
                break;
            }
            case 3: {
                int id, transportId, distributionCenterId;

                std::cout << "Ingrese el ID del gestor a actualizar: ";
                std::cin >> id;

                ShipmentManager* existing = shipmentManagerService->getShipmentManagerById(id);
                if (existing == nullptr) {
                    std::cout << "Gestor no encontrado." << std::endl;
                    break;
                }
                delete existing;

                std::cout << "Ingrese el nuevo ID del transporte: ";
                std::cin >> transportId;
                std::cout << "Ingrese el nuevo ID del centro de distribucion: ";
                std::cin >> distributionCenterId;

                List path;

                shipmentManagerService->updateShipmentManager(id, transportId, path, distributionCenterId);
                break;
            }
            case 4: {
                int id;
                std::cout << "Ingrese el ID del gestor a eliminar: ";
                std::cin >> id;

                char confirm;
                std::cout << "¿Esta seguro de eliminar el gestor con ID " << id << "? (s/n): ";
                std::cin >> confirm;

                if (confirm == 's' || confirm == 'S') {
                    shipmentManagerService->deleteShipmentManager(id);
                } else {
                    std::cout << "Operacion cancelada." << std::endl;
                }
                break;
            }
            case 5:
                shipmentManagerService->displayAllShipmentManagers();
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
