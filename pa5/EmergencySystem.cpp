#include "EmergencySystem.h"
#include <iostream>
#include <algorithm>

void EmergencySystem::initialize() {
    network.initializeHospitalNetwork();
    
    // Initialize all hospitals as OPEN
    std::vector<std::string> cities = network.getCities();
    for (const std::string& city : cities) {
        hospitals.emplace(city, Hospital(city));
    }
    
    // Pre-compute shortest paths for optimization
    shortestPaths = network.precomputeAllShortestPaths();
    
    std::cout << "Hospital network initialized." << std::endl;
}

Hospital& EmergencySystem::getHospital(const std::string& city) {
    auto it = hospitals.find(city);
    if (it != hospitals.end()) {
        return it->second;
    }
    throw std::runtime_error("Hospital not found: " + city);
}

bool EmergencySystem::hospitalExists(const std::string& city) const {
    return hospitals.find(city) != hospitals.end();
}

void EmergencySystem::handleEmergency(const std::string& name, int severity, const std::string& city) {
    if (!hospitalExists(city)) {
        std::cout << "Error: Hospital in " << city << " does not exist." << std::endl;
        return;
    }
    
    std::string targetHospital = city;
    
    // If the city's hospital is closed, find the nearest open hospital
    if (!getHospital(city).isOpen()) {
        targetHospital = findNearestOpenHospital(city);
    }
    
    // Add patient to the hospital's priority queue
    Patient patient(name, severity, city);
    getHospital(targetHospital).addPatient(patient);
    
    std::cout << "Patient " << name << " (severity " << severity << ") from " 
              << city << " admitted to " << targetHospital << " hospital." << std::endl;
}

void EmergencySystem::handleHospitalClose(const std::string& city) {
    if (!hospitalExists(city)) {
        std::cout << "Error: Hospital in " << city << " does not exist." << std::endl;
        return;
    }
    
    Hospital& hospital = getHospital(city);
    
    if (!hospital.isOpen()) {
        std::cout << "Hospital in " << city << " is already closed." << std::endl;
        return;
    }
    
    hospital.setStatus(HospitalStatus::CLOSED);
    
    // Transfer patients to nearest open hospital
    if (hospital.hasPatients()) {
        std::string nearestOpen = findNearestOpenHospital(city);
        
        // Get the number of patients BEFORE transferring
        size_t patientCount = hospital.getPatientCount();
        
        // Get the patient queue and merge it with the target hospital's queue
        PriorityQueue& patientQueue = hospital.getPatientQueue();
        getHospital(nearestOpen).mergePatientQueue(patientQueue);
        
        std::cout << city << " hospital closed. " << patientCount 
                  << " patients transferred to " << nearestOpen << " hospital." << std::endl;
    } else {
        std::cout << city << " hospital closed. No patients to transfer." << std::endl;
    }
}

void EmergencySystem::handleHospitalOpen(const std::string& city) {
    if (!hospitalExists(city)) {
        std::cout << "Error: Hospital in " << city << " does not exist." << std::endl;
        return;
    }
    
    getHospital(city).setStatus(HospitalStatus::OPEN);
    std::cout << city << " hospital is now open." << std::endl;
}

void EmergencySystem::handleTreat(const std::string& city) {
    if (!hospitalExists(city)) {
        std::cout << "Error: Hospital in " << city << " does not exist." << std::endl;
        return;
    }
    
    Hospital& hospital = getHospital(city);
    
    if (!hospital.isOpen()) {
        std::cout << "Cannot treat patients at " << city << " hospital - it is closed." << std::endl;
        return;
    }
    
    if (!hospital.hasPatients()) {
        std::cout << "No patients waiting at " << city << " hospital." << std::endl;
        return;
    }
    
    Patient patient = hospital.treatNextPatient();
    std::cout << "Treating " << patient.name << " (severity " << patient.severity 
              << ") originally from " << patient.originalCity << " at " << city << " hospital." << std::endl;
}

void EmergencySystem::handleStatus() {
    std::vector<std::string> cities = network.getCities();
    
    for (const std::string& city : cities) {
        const Hospital& hospital = getHospital(city);
        
        std::cout << "\nHospital: " << city << std::endl;
        std::cout << "Status: " << (hospital.isOpen() ? "OPEN" : "CLOSED") << std::endl;
        std::cout << "Patients Waiting: " << hospital.getPatientCount() << std::endl;
        
        if (hospital.hasPatients()) {
            Patient nextPatient = hospital.peekNextPatient();
            std::cout << "Next Patient: " << nextPatient.name 
                      << ", Severity: " << nextPatient.severity 
                      << ", From: " << nextPatient.originalCity << std::endl;
        }
    }
    std::cout << std::endl;
}

std::string EmergencySystem::findNearestOpenHospital(const std::string& fromCity) {
    std::string nearestHospital;
    int minDistance = INF;
    
    std::vector<std::string> cities = network.getCities();
    for (const std::string& city : cities) {
        if (hospitalExists(city) && getHospital(city).isOpen() && city != fromCity) {
            int distance = shortestPaths[fromCity][city];
            if (distance < minDistance) {
                minDistance = distance;
                nearestHospital = city;
            }
        }
    }
    
    if (nearestHospital.empty()) {
        throw std::runtime_error("No open hospitals found near " + fromCity);
    }
    
    return nearestHospital;
}