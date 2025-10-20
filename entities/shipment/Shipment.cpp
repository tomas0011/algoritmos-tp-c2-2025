#include "Shipment.h"
#include <sstream>
#include <iomanip>

/*
* Objeto que representa un envío, contiene información sobre el centro, paquete, cliente, fecha y peso.
*/ 

// Constructor
Shipment::Shipment(const std::string& centerCode, int packageId, int clientId, int dateDay, double weight)
    : centerCode(centerCode), packageId(packageId), clientId(clientId), dateDay(dateDay), weight(weight) {
}

// Getters
std::string Shipment::getCenterCode() const {
    return centerCode;
}

int Shipment::getPackageId() const {
    return packageId;
}

int Shipment::getClientId() const {
    return clientId;
}

int Shipment::getDateDay() const {
    return dateDay;
}

double Shipment::getWeight() const {
    return weight;
}

// Métodos de utilidad para fechas
int Shipment::getYear() const {
    return dateDay / 10000;
}

int Shipment::getMonth() const {
    return (dateDay / 100) % 100;
}

int Shipment::getDay() const {
    return dateDay % 100;
}

bool Shipment::isInDateRange(int startDate, int endDate) const {
    return dateDay >= startDate && dateDay <= endDate;
}

// Implementar cálculo de semana del año (implementación simple)
int Shipment::getWeekOfYear() const {
    // Por ahora implementación básica - se puede mejorar después
    return 1; // Placeholder
}

std::string Shipment::toString() const {
    std::ostringstream oss;
    oss << "Centro: " << centerCode 
        << ", Paquete: " << packageId 
        << ", Cliente: " << clientId 
        << ", Fecha: " << dateDay 
        << ", Peso: " << weight;
    return oss.str();
}