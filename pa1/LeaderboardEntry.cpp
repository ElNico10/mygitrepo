#include "LeaderboardEntry.hpp"

LeaderboardEntry::LeaderboardEntry() : name(""), score(0) {}

LeaderboardEntry::LeaderboardEntry(const std::string& name, int score) 
    : name(name), score(score) {}

std::string LeaderboardEntry::getName() const { return name; }
int LeaderboardEntry::getScore() const { return score; }

void LeaderboardEntry::setName(const std::string& name) { this->name = name; }
void LeaderboardEntry::setScore(int score) { this->score = score; }

bool LeaderboardEntry::operator<(const LeaderboardEntry& other) const {
    return score > other.score; // Descending order (higher scores first)
}