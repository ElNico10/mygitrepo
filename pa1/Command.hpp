#pragma once
#define COMMAND_H

#include <string>

class Command {
private:
    std::string name;
    std::string description;
    int points;

public:
    Command();
    Command(const std::string& name, const std::string& description, int points);
    
    // Getters
    std::string getName() const;
    std::string getDescription() const;
    int getPoints() const;
    
    // Setters
    void setName(const std::string& name);
    void setDescription(const std::string& description);
    void setPoints(int points);
    
    // Utility
    bool operator==(const Command& other) const;
    std::string toString() const;
};