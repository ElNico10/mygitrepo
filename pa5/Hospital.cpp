#include "Hospital.h"
#include <iostream>

void Hospital::addPatient(const Patient& patient) {
    patientQueue.insert(patient);
}

Patient Hospital::treatNextPatient() {
    if (!hasPatients()) {
        throw std::runtime_error("No patients to treat");
    }
    return patientQueue.extractMax();
}

Patient Hospital::peekNextPatient() const {
    return patientQueue.peekMax();
}

void Hospital::mergePatientQueue(PriorityQueue& other) {
    // Merge the other queue into this hospital's queue
    patientQueue.merge(other);
}