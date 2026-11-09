#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "gamestate.h"

/* Class Game: Manages the main game loop, window, and different game states.
 *
 * The class maintains three states in the array mAllStates: WelcomeState, PlayState, and SpeedState.
 */
class Game {
public:
    // Constructor: Initializes the game, setting up the window and states.
    Game();

    // Virtual Destructor: Ensures proper cleanup of derived classes.
    virtual ~Game();

    // Main game loop: Processes events, updates state, and renders.
    void run();

    // Sets the current game state based on the provided state.
    void setState(GameState::State);

    // Returns a pointer to the SFML window for rendering.
    sf::RenderWindow *getWindow();

private:
    // SFML RenderWindow for handling all the rendering tasks.
    sf::RenderWindow mWindow;

    // Pointer to the current active game state.
    GameState *mpGameState;

    // Array of pointers to game states (Welcome, Playing, Speed).
    std::array<GameState *, GameState::SIZE> mAllStates;

    // Speed of the game, affecting how fast Tetriminos fall.
    float mGameSpeed;

    // Current score of the game.
    int mGameScore;

    // Processes all events (like input or window events).
    void processEvents();

    // Updates the game logic in the current game state.
    void update();

    // Renders the current game state to the window.
    void render();

    // Granting access to private members for these specific classes.
    friend class PlayState;

    friend class SpeedState;
};
