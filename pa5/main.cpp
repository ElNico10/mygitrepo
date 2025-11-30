// main.cpp
/*
 * PA5: Micro Project - Emergency Management System
 * CPTS 223 Advanced Data Structures
 * 
 * Skeleton Code - main.cpp
 * 
 * This file provides the basic REPL structure and command parsing.
 * You need to implement the actual functionality for each command.
 * 
 * AI USAGE POLICY:
 * - You MAY use AI assistance for: priority queue, graph structure, REPL logic
 * - You MUST NOT use AI for: Dijkstra's algorithm (use your MA3 implementation)
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Graph.h"
#include "Hospital.h"
#include "EmergencySystem.h"

using namespace std;

// Global emergency system instance
EmergencySystem emergencySystem;

/*
 * Initialize the hospital network graph with the 5 cities and their connections.
 * 
 * Cities: Pullman, Moscow, Colfax, Lewiston, Spokane
 * 
 * Connections:
 * - Pullman <-> Moscow: 8 miles
 * - Pullman <-> Colfax: 17 miles
 * - Pullman <-> Lewiston: 30 miles
 * - Moscow <-> Lewiston: 32 miles
 * - Moscow <-> Spokane: 85 miles
 * - Colfax <-> Spokane: 50 miles
 */
void initializeNetwork() {
    emergencySystem.initialize();
}


/*
 * Handle the emergency command.
 * Format: emergency "<name>" <severity> <city>
 * 
 * @param name - Patient name
 * @param severity - Severity level (1-10)
 * @param city - City where emergency occurred
 */
void handleEmergency(const string& name, int severity, const string& city) {
    emergencySystem.handleEmergency(name, severity, city);
}


/*
 * Handle the hospital close command.
 * Format: hospital close <city>
 * 
 * @param city - City whose hospital to close
 */
void handleHospitalClose(const string& city) {
    emergencySystem.handleHospitalClose(city);
}


/*
 * Handle the hospital open command.
 * Format: hospital open <city>
 * 
 * @param city - City whose hospital to reopen
 */
void handleHospitalOpen(const string& city) {
    emergencySystem.handleHospitalOpen(city);
}


/*
 * Handle the treat command.
 * Format: treat <city>
 * 
 * @param city - City whose hospital should treat next patient
 */
void handleTreat(const string& city) {
    emergencySystem.handleTreat(city);
}


/*
 * Handle the status command.
 * Format: status
 * 
 * Displays for each hospital:
 * - Hospital name/city
 * - Status (Open or Closed)
 * - Number of patients waiting
 * - Next patient info (if any): name, severity, original city
 */
void handleStatus() {
    emergencySystem.handleStatus();
}


/*
 * Parse and execute a command from user input.
 * 
 * @param input - The full command line entered by user
 * @return true if should continue, false if should quit
 */
bool processCommand(const string& input) {
    istringstream iss(input);
    string command;
    iss >> command;
    
    if (command == "quit" || command == "exit") {
        return false;
    }
    else if (command == "emergency") {
        // Parse: emergency "<name>" <severity> <city>
        string name;
        int severity;
        string city;
        
        // Handle quoted name
        char ch;
        iss >> ch; // Get opening quote
        if (ch == '"') {
            getline(iss, name, '"'); // Read until closing quote
        } else {
            // Name might not be quoted, read as single word
            iss.putback(ch);
            iss >> name;
        }
        
        iss >> severity >> city;
        
        if (severity < 1 || severity > 10) {
            cout << "Error: Severity must be between 1 and 10." << endl;
        } else {
            handleEmergency(name, severity, city);
        }
    }
    else if (command == "hospital") {
        string action, city;
        iss >> action >> city;
        
        if (action == "close") {
            handleHospitalClose(city);
        }
        else if (action == "open") {
            handleHospitalOpen(city);
        }
        else {
            cout << "Unknown hospital action: " << action << endl;
        }
    }
    else if (command == "treat") {
        string city;
        iss >> city;
        handleTreat(city);
    }
    else if (command == "status") {
        handleStatus();
    }
    else if (command == "help") {
        cout << "\nAvailable commands:" << endl;
        cout << "  emergency \"<name>\" <severity> <city> - Register new emergency" << endl;
        cout << "  hospital close <city>                 - Close a hospital" << endl;
        cout << "  hospital open <city>                  - Reopen a hospital" << endl;
        cout << "  treat <city>                          - Treat next patient" << endl;
        cout << "  status                                - Show all hospital status" << endl;
        cout << "  help                                  - Show this help message" << endl;
        cout << "  quit/exit                             - Exit the program" << endl;
        cout << endl;
    }
    else {
        cout << "Unknown command: " << command << endl;
        cout << "Type 'help' for available commands." << endl;
    }
    
    return true;
}


int main() {
    cout << "========================================" << endl;
    cout << "  Emergency Management System" << endl;
    cout << "  PA5 - CPTS 223" << endl;
    cout << "========================================" << endl;
    
    // Initialize the hospital network
    initializeNetwork();
    
    cout << "\nType 'help' for available commands." << endl;
    cout << "Type 'quit' or 'exit' to end the program.\n" << endl;
    
    // Main REPL loop
    string input;
    bool running = true;
    
    while (running) {
        cout << "> ";
        getline(cin, input);
        
        // Skip empty input
        if (input.empty()) {
            continue;
        }
        
        running = processCommand(input);
    }
    
    cout << "Exiting Emergency Management System. Goodbye!" << endl;
    
    return 0;
}