#include "Game.hpp"
#include "LeaderboardEntry.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

Game::Game(const std::string& commandsFile, const std::string& leaderboardFile)
    : commandsFile(commandsFile), leaderboardFile(leaderboardFile) {
    
    srand(time(0));
    commands = FileHandler::loadCommands(commandsFile);
    leaderboard = FileHandler::loadLeaderboard(leaderboardFile);
    
    if (commands.getSize() < 3) {
        std::cout << "Warning: Need at least 3 commands to play the game." << std::endl;
        std::cout << "Please add more commands using the menu option." << std::endl;
    }
}

Game::~Game() {
    saveAndExit();
}

void Game::run() {
    int choice;
    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                viewRules();
                break;
            case 2:
                playGame();
                break;
            case 3:
                addCommand();
                break;
            case 4:
                removeCommand();
                break;
            case 5:
                displayAllCommands();
                break;
            case 6:
                showLeaderboard();
                break;
            case 7:
                saveAndExit();
                std::cout << "Goodbye!" << std::endl;
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
        
    } while (true);
}

void Game::displayMenu() const {
    std::cout << "\n=== Linux Commands Matching Game ===" << std::endl;
    std::cout << "1. View rules" << std::endl;
    std::cout << "2. Play a new game" << std::endl;
    std::cout << "3. Add a command" << std::endl;
    std::cout << "4. Remove a command" << std::endl;
    std::cout << "5. Display all commands" << std::endl;
    std::cout << "6. Show leaderboard" << std::endl;
    std::cout << "7. Save and exit" << std::endl;
    std::cout << "Enter your choice (1-7): ";
}

void Game::viewRules() const {
    std::cout << "\n=== Game Rules ===" << std::endl;
    std::cout << "1. You will be presented with 20 multiple-choice questions" << std::endl;
    std::cout << "2. Each question shows a Linux command and 3 possible descriptions" << std::endl;
    std::cout << "3. Choose the correct description (1, 2, or 3)" << std::endl;
    std::cout << "4. Your score will be tracked and added to the leaderboard" << std::endl;
}

void Game::playGame() {
    if (commands.getSize() < 20) {
        std::cout << "Not enough commands to play. Please add at least 20 commands first." << std::endl;
        return;
    }
    
    std::string playerName;
    std::cout << "Enter your name: ";
    std::getline(std::cin, playerName);
    
    int score = 0;
    std::vector<const Command*> usedCommands;
    
    int maxQuestions = 20;
    int maxIterations = 1000;
    for (int i = 0; i < maxQuestions; i++) {
        const Command* correctCommand = nullptr;
        const Command* wrongCommand1 = nullptr;
        const Command* wrongCommand2 = nullptr;

        int tries = 0;
        do {
            correctCommand = commands.getRandom();
            tries++;
            if (tries > maxIterations) {
                std::cout << "Error: Unable to select a unique command for question " << (i+1) << ". Possible data corruption." << std::endl;
                return;
            }
        } while ((!correctCommand) || std::find(usedCommands.begin(), usedCommands.end(), correctCommand) != usedCommands.end());

        usedCommands.push_back(correctCommand);

        tries = 0;
        do {
            wrongCommand1 = getRandomCommandExcept(correctCommand);
            tries++;
            if (tries > maxIterations) {
                std::cout << "Error: Unable to select wrong command 1 for question " << (i+1) << ". Possible data corruption." << std::endl;
                return;
            }
        } while (!wrongCommand1 || wrongCommand1 == correctCommand);

        tries = 0;
        do {
            wrongCommand2 = getRandomCommandExcept(correctCommand);
            tries++;
            if (tries > maxIterations) {
                std::cout << "Error: Unable to select wrong command 2 for question " << (i+1) << ". Possible data corruption." << std::endl;
                return;
            }
        } while (!wrongCommand2 || wrongCommand2 == correctCommand || wrongCommand2 == wrongCommand1);

        const Command* options[3] = {correctCommand, wrongCommand1, wrongCommand2};

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(options, options + 3, g);

        int correctIndex = -1;
        for (int j = 0; j < 3; j++) {
            if (options[j] == correctCommand) {
                correctIndex = j + 1;
                break;
            }
        }

        std::cout << "\nQuestion " << (i + 1) << "/" << maxQuestions << std::endl;
        std::cout << "Command: " << correctCommand->getName() << std::endl;
        std::cout << "1. " << options[0]->getDescription() << std::endl;
        std::cout << "2. " << options[1]->getDescription() << std::endl;
        std::cout << "3. " << options[2]->getDescription() << std::endl;

        int answer;
        std::cout << "Your answer (1-3): ";
        std::cin >> answer;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (answer == correctIndex) {
            std::cout << "Correct! +" << correctCommand->getPoints() << " points" << std::endl;
            score += correctCommand->getPoints();
        } else {
            std::cout << "Wrong! The correct answer was: " << correctCommand->getDescription() << std::endl;
        }
    }
    
    std::cout << "\nGame over! Your final score: " << score << std::endl;
    updateLeaderboard(playerName, score);
}

void Game::addCommand() {
    std::string name, description;
    int points;
    
    std::cout << "Enter command name: ";
    std::getline(std::cin, name);
    
    std::cout << "Enter command description: ";
    std::getline(std::cin, description);
    
    std::cout << "Enter points (difficulty): ";
    std::cin >> points;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    Command newCommand(name, description, points);
    
    if (commands.contains(newCommand)) {
        std::cout << "Error: Command '" << name << "' already exists." << std::endl;
    } else {
        commands.insert(newCommand);
        std::cout << "Command '" << name << "' added successfully." << std::endl;
    }
}

void Game::removeCommand() {
    std::string name;
    std::cout << "Enter command name to remove: ";
    std::getline(std::cin, name);
    
    Command tempCommand(name, "", 0);
    if (commands.remove(tempCommand)) {
        std::cout << "Command '" << name << "' removed successfully." << std::endl;
    } else {
        std::cout << "Error: Command '" << name << "' not found." << std::endl;
    }
}

void Game::displayAllCommands() const {
    std::cout << "\n=== All Commands ===" << std::endl;
    Node<Command>* current = commands.getHead();
    int count = 1;
    
    int maxIterations = commands.getSize() * 2;
    while (current && maxIterations-- > 0) {
        if (&(current->data) != nullptr) {
            const std::string& name = current->data.getName();
            const std::string& desc = current->data.getDescription();
            int pts = current->data.getPoints();
            
            if (!name.empty() && !desc.empty() && pts > 0) {
                std::cout << count << ". " << name << " - "
                          << desc << " ("
                          << pts << " points)" << std::endl;
                count++;
            } else {
                std::cout << count << ". [INVALID COMMAND DATA]" << std::endl;
                count++;
            }
        } else {
            std::cout << count << ". [NULL COMMAND POINTER]" << std::endl;
            count++;
        }
        current = current->next;
    }
    
    if (maxIterations <= 0) {
        std::cout << "Warning: Command list traversal exceeded safe limit." << std::endl;
    }
    
    if (count == 1) {
        std::cout << "No commands available." << std::endl;
    }
}

void Game::showLeaderboard() const {
    std::cout << "\n=== Leaderboard (Top 3) ===" << std::endl;
    
    if (leaderboard.empty()) {
        std::cout << "No scores yet. Be the first to play!" << std::endl;
        return;
    }
    
    for (size_t i = 0; i < std::min(leaderboard.size(), size_t(3)); i++) {
        std::cout << (i + 1) << ". " << leaderboard[i].getName() << " - " 
                  << leaderboard[i].getScore() << " points" << std::endl;
    }
}

void Game::saveAndExit() {
    FileHandler::saveCommands(commandsFile, commands);
    FileHandler::saveLeaderboard(leaderboardFile, leaderboard);
}

void Game::updateLeaderboard(const std::string& name, int score) {
    leaderboard.emplace_back(name, score);
    std::sort(leaderboard.begin(), leaderboard.end());
    
    if (leaderboard.size() > 10) {
        leaderboard.resize(10);
    }
}
const Command* Game::getRandomCommandExcept(const Command* exclude) const {
    if (commands.getSize() <= 1) return nullptr;
    
    const Command* randomCmd = nullptr;
    int tries = 0;
    int maxTries = commands.getSize() * 2;
    
    do {
        randomCmd = commands.getRandom();
        tries++;
        if (tries > maxTries) {
            std::cerr << "Warning: Could not find unique random command" << std::endl;
            return nullptr;
        }
    } while (randomCmd == exclude);
    
    return randomCmd;
}

