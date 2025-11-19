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
#include <limits>

// Función para validar input numérico de forma robusta
int getValidIntInput(int min, int max) {
    int value;
    while (true) {
        if (std::cin >> value) {
            // Input numérico válido
            if (value >= min && value <= max) {
                return value;
            } else {
                std::cout << "Numero fuera de rango. Ingrese un valor entre " << min << " y " << max << ": ";
            }
        } else {
            // Input no numérico - limpiar el buffer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input invalido. Por favor ingrese un numero: ";
        }
    }
}

// Función para validar input double de forma robusta
double getValidDoubleInput(double min, double max) {
    double value;
    while (true) {
        if (std::cin >> value) {
            // Input numérico válido
            if (value >= min && value <= max) {
                return value;
            } else {
                std::cout << "Numero fuera de rango. Ingrese un valor entre " << min << " y " << max << ": ";
            }
        } else {
            // Input no numérico - limpiar el buffer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input invalido. Por favor ingrese un numero decimal: ";
        }
    }
}

// Función para validar input string de forma robusta
std::string getValidStringInput() {
    std::string value;
    
    // Limpiar buffer si hay un newline residual
    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }
    
    while (true) {
        std::getline(std::cin, value);
        if (!value.empty()) {
            return value;
        } else {
            std::cout << "Input no puede estar vacio. Por favor ingrese texto: ";
        }
    }
}

void showMenu() {
    int choice;
    do {
        std::cout << "\n=== Menu de Entidades ===\n";
        std::cout << "1. Sistema de gestion\n";
        std::cout << "2. Ejercicios del TP\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opcion: ";
        choice = getValidIntInput(0, 2);

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
        choice = getValidIntInput(0, 7);

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
        choice = getValidIntInput(0, 3);

        switch (choice) {
            case 1:
                showDistributionCenterMenu();
                break;
            case 2:
                showShipmentMenu();
                break;
            case 3:
                showShipmentMenu();
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
