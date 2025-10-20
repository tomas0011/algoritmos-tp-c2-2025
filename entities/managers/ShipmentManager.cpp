#include "ShipmentManager.h"
#include <fstream>
#include <sstream>
#include <iostream>


/*Clase que gestiona la colección de Shipment, se pueden cargar datos desde un
* archivo, crea Shipments e imprime los datos. Sobre las consultas que puede hacer:
* Cuenta envios por centro en un rango de fechas
* Hay varios metodos que podrían implementarse, agregando indices para optimizar búsquedas
*/ 

// Constructor
ShipmentManager::ShipmentManager() : indicesBuilt(false) {
}

// Método para cargar archivo y mostrar fechas
bool ShipmentManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cout << "Error: No se pudo abrir el archivo " << filename << std::endl;
        return false;
    }
    
    std::string line;
    int lineNumber = 1;
        int sumaTotal=0;
    
    std::cout << "Leyendo archivo " << filename << "..." << std::endl;
    std::cout << "================================" << std::endl;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string centerCode;
        int packageId, clientId, dateDay;
        double weight;
        // Formato: codigo_centro paquete_id cliente_id fecha_dia peso
        if (iss >> centerCode >> packageId >> clientId >> dateDay >> weight) {
            // Crear el objeto Shipment y agregarlo al vector
            Shipment shipment(centerCode, packageId, clientId, dateDay, weight);
            shipments.push_back(shipment);
            
            std::cout << "Centro: " << centerCode << ", ";
            std::cout << "Fecha: " << dateDay << " (";
            std::cout << "Peso: " << weight << " kg)";
            sumaTotal += weight;
            // Extraer año, mes y día de la fecha
            int year = dateDay / 10000;
            int month = (dateDay / 100) % 100;
            int day = dateDay % 100;
            
            std::cout << day << "/" << month << "/" << year << ")" << std::endl;
        } else {
            std::cout << "Error en línea " << lineNumber << ": formato incorrecto" << std::endl;
        }
        
        lineNumber++;
    }
    std::cout << "Peso total: " << sumaTotal << " kg" << std::endl;

    
    file.close();
    std::cout << "================================" << std::endl;
    std::cout << "Archivo procesado. Total de lineas: " << (lineNumber - 1) << std::endl;
    
    return true;
}

// Métodos stub para compilar
void ShipmentManager::buildIndices() {
    // Por implementar
}

void ShipmentManager::clearIndices() {
    // Por implementar
}

void ShipmentManager::addShipment(const Shipment& shipment) {
    // Por implementar
}

std::map<std::string, int> ShipmentManager::getShipmentsByCenter(int startDate, int endDate) {
    std::map<std::string, int> result;
    
    std::cout << "\n=== CALCULANDO ENVIOS POR CENTRO ===" << std::endl;
    std::cout << "Rango de fechas: " << startDate << " - " << endDate << std::endl;
    std::cout << "Formato: DD/MM/YYYY" << std::endl;
    
    // Convertir fechas para mostrar
    int startYear = startDate / 10000;
    int startMonth = (startDate / 100) % 100;
    int startDay = startDate % 100;
    
    int endYear = endDate / 10000;
    int endMonth = (endDate / 100) % 100;
    int endDayNum = endDate % 100;
    
    std::cout << "Desde: " << startDay << "/" << startMonth << "/" << startYear;
    std::cout << " Hasta: " << endDayNum << "/" << endMonth << "/" << endYear << std::endl;
    std::cout << "--------------------------------" << std::endl;
    
    // Algoritmo O(n): Recorrer todos los envíos
    for (const auto& shipment : shipments) {
        int shipmentDate = shipment.getDateDay();
        
        // Filtrar por rango de fechas
        if (shipmentDate >= startDate && shipmentDate <= endDate) {
            std::string center = shipment.getCenterCode();
            result[center]++; // Incrementar contador para este centro
            
            // Mostrar el envío que se está contando
            int year = shipmentDate / 10000;
            int month = (shipmentDate / 100) % 100;
            int day = shipmentDate % 100;
            std::cout << "Centro: " << center << " - Fecha: " << day << "/" << month << "/" << year << std::endl;
        }
    }
    
    std::cout << "--------------------------------" << std::endl;
    std::cout << "RESULTADO:" << std::endl;
    for (const auto& pair : result) {
        std::cout << "Centro " << pair.first << ": " << pair.second << " envios" << std::endl;
    }
    std::cout << "==================================" << std::endl;
    
    return result;
}

std::vector<std::string> ShipmentManager::getOverloadedCenters(int maxShipmentsPerWeek) {
    std::vector<std::string> result;
    // Por implementar
    return result;
}

std::vector<Shipment> ShipmentManager::getShipmentsByClient(int clientId) {
    std::vector<Shipment> result;
    // Por implementar
    return result;
}

std::vector<Shipment> ShipmentManager::getShipmentsByPackage(int packageId) {
    std::vector<Shipment> result;
    // Por implementar
    return result;
}

int ShipmentManager::getTotalShipments() const {
    return shipments.size();
}

void ShipmentManager::printStatistics() const {
    // Por implementar
}

void ShipmentManager::analyzeComplexity() const {
    // Por implementar
}