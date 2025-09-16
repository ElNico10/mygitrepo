#pragma once
#define GAME_H

#include "LinkedList.hpp"
#include "Command.hpp"
#include "FileHandler.hpp"
#include "LeaderboardEntry.hpp"
#include <vector>
#include <string>

class Game {
private:
    LinkedList<Command> commands;
    std::vector<LeaderboardEntry> leaderboard;
    std::string commandsFile;
    std::string leaderboardFile;
    
public:
    Game(const std::string& commandsFile = "commands.csv", 
         const std::string& leaderboardFile = "leaderboard.csv");
    ~Game();
    
    void run();
    
private:
    void displayMenu() const;
    void viewRules() const;
    void playGame();
    void addCommand();
    void removeCommand();
    void displayAllCommands() const;
    void showLeaderboard() const;
    void saveAndExit();
    
    void updateLeaderboard(const std::string& name, int score);
    Command* getRandomCommandExcept(const Command* exclude = nullptr) const;
};