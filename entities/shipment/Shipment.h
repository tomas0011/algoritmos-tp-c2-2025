#ifndef SHIPMENT_H
#define SHIPMENT_H

#include <string>

class Shipment {
private:
    std::string centerCode;
    int packageId;
    int clientId;
    int dateDay;  // formato YYYYMMDD
    double weight;

public:
    Shipment(const std::string& centerCode, int packageId, int clientId, int dateDay, double weight);
    
    std::string getCenterCode() const;
    int getPackageId() const;
    int getClientId() const;
    int getDateDay() const;
    double getWeight() const;
    
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    bool isInDateRange(int startDate, int endDate) const;
    int getWeekOfYear() const;  
    
    std::string toString() const;
    
    bool operator<(const Shipment& other) const;
    bool operator==(const Shipment& other) const;
};

#endif