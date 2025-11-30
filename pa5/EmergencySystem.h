#ifndef EMERGENCYSYSTEM_H
#define EMERGENCYSYSTEM_H

#include <map>
#include <string>
#include "Graph.h"
#include "Hospital.h"

class EmergencySystem {
private:
    Graph network;
    std::map<std::string, Hospital> hospitals;
    std::map<std::string, std::map<std::string, int>> shortestPaths;

public:
    void initialize();
    void handleEmergency(const std::string& name, int severity, const std::string& city);
    void handleHospitalClose(const std::string& city);
    void handleHospitalOpen(const std::string& city);
    void handleTreat(const std::string& city);
    void handleStatus();
    
private:
    std::string findNearestOpenHospital(const std::string& fromCity);
    Hospital& getHospital(const std::string& city);
    bool hospitalExists(const std::string& city) const;
};

#endif