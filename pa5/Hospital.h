#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <string>
#include "PriorityQueue.h"

enum class HospitalStatus {
    OPEN,
    CLOSED
};

class Hospital {
private:
    std::string city;
    HospitalStatus status;
    PriorityQueue patientQueue;

public:
    Hospital(const std::string& cityName) : city(cityName), status(HospitalStatus::OPEN) {}
    
    std::string getCity() const { return city; }
    HospitalStatus getStatus() const { return status; }
    void setStatus(HospitalStatus newStatus) { status = newStatus; }
    bool isOpen() const { return status == HospitalStatus::OPEN; }
    
    void addPatient(const Patient& patient);
    Patient treatNextPatient();
    Patient peekNextPatient() const;
    bool hasPatients() const { return !patientQueue.isEmpty(); }
    size_t getPatientCount() const { return patientQueue.size(); }
    
    PriorityQueue& getPatientQueue() { return patientQueue; }
    void mergePatientQueue(PriorityQueue& other);
};

#endif