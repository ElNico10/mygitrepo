#include "FileHandler.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <cctype>

LinkedList<Command> FileHandler::loadCommands(const std::string& filename) {
    LinkedList<Command> commands;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cout << "Warning: " << filename << " not found. Creating new file." << std::endl;
        return commands;
    }
    
    std::string line;
    int lineNumber = 0;
    int loadedCount = 0;
    
    while (std::getline(file, line)) {
        lineNumber++;
        
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        
        if (line.empty()) continue;
        
        std::vector<std::string> parts = parseCSVLine(line);
        if (parts.size() != 3) {
            std::cerr << "Warning: Invalid format on line " << lineNumber << ": " << line << std::endl;
            continue;
        }
        
        std::string name = parts[0];
        std::string description = parts[1];
        
        if (description.size() >= 2 && description.front() == '"' && description.back() == '"') {
            description = description.substr(1, description.size() - 2);
        }
        
        int points = 0;
        try {
            points = std::stoi(parts[2]);
        } catch (const std::exception& e) {
            std::cerr << "Warning: Invalid points value '" << parts[2] << "' on line " << lineNumber << std::endl;
            continue;
        }
        
        if (name.empty()) {
            std::cerr << "Warning: Empty name on line " << lineNumber << std::endl;
            name = "unknown_command";
        }
        
        if (description.empty()) {
            std::cerr << "Warning: Empty description on line " << lineNumber << std::endl;
            description = "No description available";
        }
        
        if (points < 1) {
            std::cerr << "Warning: Invalid points (" << points << ") on line " << lineNumber << ", setting to 1" << std::endl;
            points = 1;
        }
        
        Command cmd(name, description, points);
        commands.insert(cmd);
        loadedCount++;
    }
    
    file.close();
    std::cout << "Loaded " << loadedCount << " commands from " << filename << std::endl;
    return commands;
}

void FileHandler::saveCommands(const std::string& filename, const LinkedList<Command>& commands) {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << " for writing." << std::endl;
        return;
    }
    
    Node<Command>* current = commands.getHead();
    while (current) {
        file << current->data.getName() << ",\"" 
             << current->data.getDescription() << "\"," 
             << current->data.getPoints() << std::endl;
        current = current->next;
    }
    
    file.close();
}

std::vector<LeaderboardEntry> FileHandler::loadLeaderboard(const std::string& filename) {
    std::vector<LeaderboardEntry> leaderboard;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        return leaderboard;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        
        if (line.empty()) continue;
        
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) {
            std::string name = line.substr(0, commaPos);
            std::string scoreStr = line.substr(commaPos + 1);
            
            name.erase(0, name.find_first_not_of(" \t"));
            name.erase(name.find_last_not_of(" \t") + 1);
            scoreStr.erase(0, scoreStr.find_first_not_of(" \t"));
            scoreStr.erase(scoreStr.find_last_not_of(" \t") + 1);
            
            try {
                int score = std::stoi(scoreStr);
                leaderboard.emplace_back(name, score);
            } catch (const std::exception& e) {
                std::cerr << "Warning: Invalid score format: " << line << std::endl;
            }
        }
    }
    
    file.close();
    std::sort(leaderboard.begin(), leaderboard.end());
    return leaderboard;
}

void FileHandler::saveLeaderboard(const std::string& filename, const std::vector<LeaderboardEntry>& leaderboard) {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << " for writing." << std::endl;
        return;
    }
    
    for (const auto& entry : leaderboard) {
        file << entry.getName() << "," << entry.getScore() << std::endl;
    }
    
    file.close();
}

std::vector<std::string> FileHandler::parseCSVLine(const std::string& line) {
    std::vector<std::string> fields;
    std::string field;
    bool inQuotes = false;
    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (c == '"') {
            inQuotes = !inQuotes;
            field += c;
        } else if (c == ',' && !inQuotes) {
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
        }
    }
    fields.push_back(field);
    if (fields.size() != 3) fields.clear();
    return fields;
}