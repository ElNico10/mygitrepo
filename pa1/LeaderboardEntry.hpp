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
    
    std::string getName() const;
    int getScore() const;
    
    void setName(const std::string& name);
    void setScore(int score);
    
    bool operator<(const LeaderboardEntry& other) const;
};