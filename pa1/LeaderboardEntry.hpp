#pragma once
#define LEADERBOARDENTRY_H

#include <string>

class LeaderboardEntry {
private:
    std::string name;
    int score;

public:
    LeaderboardEntry();
    LeaderboardEntry(const std::string& name, int score);
    
    // Getters
    std::string getName() const;
    int getScore() const;
    
    // Setters
    void setName(const std::string& name);
    void setScore(int score);
    
    // Comparison operator for sorting
    bool operator<(const LeaderboardEntry& other) const;
};