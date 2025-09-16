/*
 Linux Commands Matching Game
 CptS 223: Advanced Data Structures
 
 Design Reflection:
 
 Advantage of using linked list:
 - Dynamic memory allocation allows for efficient insertion and deletion of commands
   without needing to resize or shift elements like in an array. This is particularly
   useful for the add/remove command functionality.
 
 Disadvantage of using linked list:
 - Random access is O(n) complexity, which makes getting random commands for the game
   less efficient compared to an array where random access is O(1). However, for our
   use case with ~30-100 commands, this is acceptable.
 */

#include "Game.hpp"

int main() {
    Game game;
    game.run();
    return 0;
}