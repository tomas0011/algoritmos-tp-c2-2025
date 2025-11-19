#include "shipment.bash.h"
#include "services/initializeServices.h"
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <utils/algorithms/parseDate/parseDate.h>
#include "../utils/dataStructures/list/List.h"

void showShipmentMenu() {
    ShipmentService* shipmentServicePtr = shipmentService;

    int choice;
    do {
        
        std::cout << "\n=== Menu Envios ===" << std::endl;
        std::cout << "1. Crear envio" << std::endl;
        std::cout << "2. Ver envio por ID" << std::endl;
        std::cout << "3. Actualizar envio" << std::endl;
        std::cout << "4. Eliminar envio" << std::endl;
        std::cout << "5. Ver todos los envios" << std::endl;
        std::cout << "6. Contar envios por centro y fecha" << std::endl;
        std::cout << "7. Ver centros sobrecargados" << std::endl;
        std::cout << "8. Buscar envios por cliente" << std::endl;
        std::cout << "9. Preparar transporte en centro de distribucion.\n";
        std::cout << "0. Volver al menu principal" << std::endl;
        std::cout << "Ingrese su opcion: ";
    
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
                std::cin.ignore();
                std::getline(std::cin, originId);
                std::cout << "Ingrese el ID de destino: ";
                std::getline(std::cin, destinationId);
                std::cout << "Ingrese el ID del cliente: ";
                std::cin >> clientId;

                List packages; // vacío por simplicidad
                time_t now = time(nullptr);

                shipmentServicePtr->createShipment(id, state, cost, priority, totalPrice, totalWeight,
                                               shipmentManagerId, distributionCenterId, packages,
                                               originId, destinationId, clientId, now, now, now, now);
                break;
            }
            case 2: {
                int id;
                std::cout << "Ingrese el ID del envio: ";
                std::cin >> id;

                Shipment* shipment = shipmentServicePtr->getShipmentById(id);
                if (shipment != nullptr) {
                    shipment->display();
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

                Shipment* existing = shipmentServicePtr->getShipmentById(id);
                if (existing == nullptr) {
                    std::cout << "Envio no encontrado." << std::endl;
                    break;
                }

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
                std::cin.ignore();
                std::getline(std::cin, distributionCenterId);
                std::cout << "Ingrese el nuevo ID de origen: ";
                std::getline(std::cin, originId);
                std::cout << "Ingrese el nuevo ID de destino: ";
                std::getline(std::cin, destinationId);
                std::cout << "Ingrese el nuevo ID del cliente: ";
                std::cin >> clientId;

                List packages;
                time_t now = time(nullptr);

                shipmentServicePtr->updateShipment(id, state, cost, priority, totalPrice, totalWeight,
                                               shipmentManagerId, distributionCenterId, packages,
                                               originId, destinationId, clientId, now, now, now, now);
                break;
            }
            case 4: {
                int id;
                std::cout << "Ingrese el ID del envio a eliminar: ";
                std::cin >> id;
                shipmentServicePtr->deleteShipment(id);
                std::cout << "Envio eliminado." << std::endl;
                break;
            }
            case 5: {
                shipmentServicePtr->displayAllShipments();
                break;
            }
            case 6: {
                std::string centerId, startDateStr, endDateStr;
                std::cout << "Ingrese el ID del centro: ";
                std::cin.ignore();
                std::getline(std::cin, centerId);
                std::cout << "Ingrese la fecha de inicio (dd-mm-yyyy): ";
                std::getline(std::cin, startDateStr);
                std::cout << "Ingrese la fecha de fin (dd-mm-yyyy): ";
                std::getline(std::cin, endDateStr);

                time_t start = strToDate(startDateStr);
                time_t end = strToDate(endDateStr);

                int count = shipmentServicePtr->totalShipmentsByCenterAndDate(centerId, start, end);
                std::cout << "Total de envios en el centro " << centerId << " entre "
                         << startDateStr << " y " << endDateStr << ": " << count << std::endl;
                break;
            }
           case 7: {
                List overloaded = shipmentServicePtr->overloadedCenters();
                std::cout << "Centros sobrecargados:" << std::endl;
                Node* current = overloaded.getHead();
                while (current != nullptr) {
                    try {
                        std::string centerId = std::any_cast<std::string>(current->getData());
                        std::cout << "- " << centerId << std::endl;
                    } catch (const std::bad_any_cast&) {
                        std::cout << "- [Error en datos]" << std::endl;
                    }
                    current = current->getNext();
                }
                break;
            }
            case 8: {
                int clientId;
                std::cout << "Ingrese el ID del cliente: ";
                std::cin >> clientId;

                List clientShipments = shipmentServicePtr->findShipmentsByClient(clientId);
                std::cout << "Envios del cliente " << clientId << ":" << std::endl;
                Node* current = clientShipments.getHead();
                while (current != nullptr) {
                    try {
                        Shipment* shipment = std::any_cast<Shipment*>(current->getData());
                        shipment->display();
                        std::cout << "------------------------" << std::endl;
                    } catch (const std::bad_any_cast&) {
                        std::cout << "Error al procesar envio" << std::endl;
                    }
                    current = current->getNext();
                }
                break;
            }
            case 9: {
                std::string distributionCenterId;
                std::cout << "Ingrese el ID del centro de distribucion: ";
                std::cin >> distributionCenterId;

                int transportId;
                std::cout << "Ingrese el ID del Transporte: ";
                std::cin >> transportId;

                List packages = shipmentService->generateOptimalCargoForTransport(transportId, distributionCenterId);
                std::cout << "Transporte " << transportId << " en centro " << distributionCenterId
                    << " preparado con " << packages.getSize() << " paquetes optimos" << ":\n";

                Node* current = packages.getHead();
                std::cout << "-----------------" << std::endl;
                do {
                    try {
                        Package pkg = std::any_cast<Package>(current->getData());
                        pkg.display();
                    } catch (const std::bad_any_cast&) {
                        std::cout << "Error al procesar paquete" << std::endl;
                    }
                    std::cout << "-----------------" << std::endl;
                    current = current->getNext();
                } while (current != nullptr);
                break;
            }
            case 0:
                std::cout << "Volviendo al menu principal..." << std::endl;
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
        }
    } while (choice != 0);
}
