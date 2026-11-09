//#include "game.h"
//
//// Entry point for the Tetris game application.
//int main() {
//    // Create a Game object.
//    // This initializes the game, setting up the window and game states.
//    Game game;
//
//    // Run the game.
//    // This starts the game loop which processes events, updates game states,
//    // and renders graphics until the game window is closed.
//    game.run();
//
//    // Return 0 to indicate successful execution of the program.
//    return 0;
//}
#include "game.h"
#include <iostream>

int main() {
    try {
        std::cout << "Starting game..." << std::endl;
        Game game;

        std::cout << "Entering game loop..." << std::endl;
        game.run();

        std::cout << "Game finished normally." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "CRASH! Error: " << e.what() << std::endl;
        system("pause"); // Чтобы консоль не закрылась
    }
    catch (...) {
        std::cerr << "Unknown error occurred!" << std::endl;
        system("pause");
    }
    return 0;
}
