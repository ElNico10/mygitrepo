#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "LinkedList.hpp"
#include "Command.hpp"
#include "LeaderboardEntry.hpp"
#include <string>
#include <vector>

class FileHandler {
public:
    static LinkedList<Command> loadCommands(const std::string& filename);
    static void saveCommands(const std::string& filename, const LinkedList<Command>& commands);
    
    static std::vector<LeaderboardEntry> loadLeaderboard(const std::string& filename);
    static void saveLeaderboard(const std::string& filename, const std::vector<LeaderboardEntry>& leaderboard);
    
private:
    static std::vector<std::string> parseCSVLine(const std::string& line);
};

#endif