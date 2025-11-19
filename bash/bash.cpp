#include "bash.h"
#include "package.bash.h"
#include "shipment.bash.h"
#include "transport.bash.h"
#include "client.bash.h"
#include "connection.bash.h"
#include "distributionCenter.bash.h"
#include "employee.bash.h"
#include <iostream>
#include <string>

void showMenu() {
    int choice;
    do {
        std::cout << "\n=== Menu de Entidades ===\n";
        std::cout << "1. Sistema de gestion\n";
        std::cout << "2. Ejercicios del TP\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                showManagementMenu();
                break;
            case 2:
                showTPMenu();
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

void showManagementMenu() {
    int choice;
    do {
        std::cout << "\n=== Menu de Entidades ===\n";
        std::cout << "1. Paquetes\n";
        std::cout << "2. Envios\n";
        std::cout << "3. Transportes\n";
        std::cout << "4. Clientes\n";
        std::cout << "5. Conexiones\n";
        std::cout << "6. Centros de Distribucion\n";
        std::cout << "7. Empleados\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                showPackageMenu();
                break;
            case 2:
                showShipmentMenu();
                break;
            case 3:
                showTransportMenu();
                break;
            case 4:
                showClientMenu();
                break;
            case 5:
                showConnectionMenu();
                break;
            case 6:
                showDistributionCenterMenu();
                break;
            case 7:
                showEmployeeMenu();
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

void showTPMenu() {
    int choice;
    do {
        std::cout << "\n=== Menu de Entidades ===\n";
        std::cout << "1. Gestion de Centros (Ejercicio A)\n";
        std::cout << "2. Analisis de Envios (Ejercicio B)\n";
        std::cout << "3. Optimizacion con Backtracking (Ejercicio C)\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                showDistributionCenterMenu();
                break;
            case 2:
                showShipmentMenu();
                break;
            case 3:
                std::cout << "No implementado...\n";
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
