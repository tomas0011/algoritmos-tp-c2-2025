#include "shipment.bash.h"
#include "services/initializeServices.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <utils/algorithms/parseDate/parseDate.h>

void showShipmentMenu() {
    int choice;
    do {
        std::cout << "\n=== Gestion de Envios (Item B) ===\n";
        std::cout << "1. Crear un nuevo envio\n";
        std::cout << "2. Mostrar informacion de un envio por ID\n";
        std::cout << "3. Actualizar un envio\n";
        std::cout << "4. Eliminar un envio\n";
        std::cout << "5. Mostrar todos los envios\n";
        std::cout << "6. Calcular el total de envíos por centro por rango de fechas. (B.1)\n";
        std::cout << "7. Detectar centros con sobrecarga. (B.2)\n";
        std::cout << "8. Obtener envios de un cliente por paquete. (B.3)\n";
        std::cout << "0. Volver al menú principal\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int id, priority, shipmentManagerId, clientId;
                double cost, totalPrice, totalWeight;
                std::string state, distributionCenterId, originId, destinationId;

                std::cout << "Ingrese el ID del envio: ";
                std::cin >> id;
                std::cout << "Ingrese el estado: ";
                std::cin.ignore();
                std::getline(std::cin, state);
                std::cout << "Ingrese el costo: ";
                std::cin >> cost;
                std::cout << "Ingrese la prioridad: ";
                std::cin >> priority;
                std::cout << "Ingrese el precio total: ";
                std::cin >> totalPrice;
                std::cout << "Ingrese el peso total: ";
                std::cin >> totalWeight;
                std::cout << "Ingrese el ID del gestor de envio: ";
                std::cin >> shipmentManagerId;
                std::cout << "Ingrese el ID del centro de distribucion: ";
                std::cin >> distributionCenterId;
                std::cout << "Ingrese el ID de origen: ";
                std::cin >> originId;
                std::cout << "Ingrese el ID de destino: ";
                std::cin >> destinationId;
                std::cout << "Ingrese el ID del cliente: ";
                std::cin >> clientId;

                std::vector<Package> packages; // vacío por simplicidad
                time_t now = time(nullptr);

                shipmentService->createShipment(id, state, cost, priority, totalPrice, totalWeight,
                                               shipmentManagerId, distributionCenterId, packages,
                                               originId, destinationId, clientId, now, now, now, now);
                break;
            }
            case 2: {
                int id;
                std::cout << "Ingrese el ID del envio: ";
                std::cin >> id;

                Shipment* shipment = shipmentService->getShipmentById(id);
                if (shipment != nullptr) {
                    shipment->display();
                    delete shipment;
                } else {
                    std::cout << "Envio no encontrado." << std::endl;
                }
                break;
            }
            case 3: {
                int id, priority, shipmentManagerId, clientId;
                double cost, totalPrice, totalWeight;
                std::string state, distributionCenterId, originId, destinationId;

                std::cout << "Ingrese el ID del envio a actualizar: ";
                std::cin >> id;

                Shipment* existing = shipmentService->getShipmentById(id);
                if (existing == nullptr) {
                    std::cout << "Envio no encontrado." << std::endl;
                    break;
                }
                delete existing;

                std::cout << "Ingrese el nuevo estado: ";
                std::cin.ignore();
                std::getline(std::cin, state);
                std::cout << "Ingrese el nuevo costo: ";
                std::cin >> cost;
                std::cout << "Ingrese la nueva prioridad: ";
                std::cin >> priority;
                std::cout << "Ingrese el nuevo precio total: ";
                std::cin >> totalPrice;
                std::cout << "Ingrese el nuevo peso total: ";
                std::cin >> totalWeight;
                std::cout << "Ingrese el nuevo ID del gestor de envio: ";
                std::cin >> shipmentManagerId;
                std::cout << "Ingrese el nuevo ID del centro de distribucion: ";
                std::cin >> distributionCenterId;
                std::cout << "Ingrese el nuevo ID de origen: ";
                std::cin >> originId;
                std::cout << "Ingrese el nuevo ID de destino: ";
                std::cin >> destinationId;
                std::cout << "Ingrese el nuevo ID del cliente: ";
                std::cin >> clientId;

                std::vector<Package> packages;
                time_t now = time(nullptr);

                shipmentService->updateShipment(id, state, cost, priority, totalPrice, totalWeight,
                                               shipmentManagerId, distributionCenterId, packages,
                                               originId, destinationId, clientId, now, now, now, now);
                break;
            }
            case 4: {
                int id;
                std::cout << "Ingrese el ID del envio a eliminar: ";
                std::cin >> id;

                char confirm;
                std::cout << "¿Esta seguro de eliminar el envio con ID " << id << "? (s/n): ";
                std::cin >> confirm;

                if (confirm == 's' || confirm == 'S') {
                    shipmentService->deleteShipment(id);
                } else {
                    std::cout << "Operacion cancelada." << std::endl;
                }
                break;
            }
            case 5:
                shipmentService->displayAllShipments();
                break;
            case 6: {
                std::string distributionCenterId;
                std::cout << "Ingrese el ID del centro de distribucion: ";
                std::cin >> distributionCenterId;

                std::string startDateStr;
                std::cout << "Ingrese la fecha de inicio (dd-mm-aaaa): ";
                std::cin >> startDateStr;

                std::string endDateStr;
                std::cout << "Ingrese la fecha de fin (dd-mm-aaaa): ";
                std::cin >> endDateStr;

                // Parse dates
                time_t start = parseDate(startDateStr);
                time_t end = parseDate(endDateStr);

                if (start == -1 || end == -1) {
                    std::cout << "Formato de fecha invalido. Use dd-mm-aaaa." << std::endl;
                    break;
                }

                int count = shipmentService->totalShipmentsByCenterAndDate(distributionCenterId, start, end);
                std::cout << "Total de envios en el centro " << distributionCenterId
                          << " entre las fechas: " << startDateStr << " y " << endDateStr
                          << " es: " << count << std::endl;
                break;
            }
            case 7: {
                std::vector<std::string> overloadedCenters = shipmentService->overloadedCenters();
                std::cout << "Centros con sobrecarga (mas de su limite de envios semanal):\n";
                for (const auto& centerId : overloadedCenters) {
                    std::cout << "- " << centerId << std::endl;
                }
                break;
            }
            case 8: {
                int clientId;
                std::cout << "Ingrese el ID del Cliente: ";
                std::cin >> clientId;

                std::vector<Shipment> shipments = shipmentService->findShipmentsByClient(clientId);
                std::cout << "Envios del cliente " << clientId << ":\n";
                for (const auto& shipment : shipments) {
                    shipment.display();
                }
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
