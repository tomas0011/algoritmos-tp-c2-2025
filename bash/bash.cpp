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
            case 0:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opcion invalida. Intente de nuevo.\n";
                break;
        }
    } while (choice != 0);
}