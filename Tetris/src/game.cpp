#include "game.h"
#include "playstate.h"

#include <iostream>

// Constructor: Initializes the game with a window and initial settings.
Game::Game() : mWindow(sf::VideoMode(650, 750), "Tetris"), mGameSpeed(3.0f),
               mGameScore(0) {
    // Initialize game states here
    mAllStates[GameState::Welcome] = new WelcomeState(this);
    mAllStates[GameState::Playing] = new PlayState(this);
    mAllStates[GameState::Speed] = new SpeedState(this);

    // Set the initial game state to Welcome
    setState(GameState::Welcome);
}

// Destructor: Handles cleanup, specifically deallocating game states.
Game::~Game() {
    for (std::size_t i = 0; i < GameState::SIZE; ++i) {
        delete mAllStates[i];
    }
}

// Main game loop: Processes events, updates game logic, and renders frames.
void Game::run() {
    while (mWindow.isOpen()) {
        processEvents();
        update();
        render();
    }
}

// Set the current game state.
void Game::setState(GameState::State st) {
    mpGameState = mAllStates[st];
    mpGameState->start();
}

// Getter for the game window.
sf::RenderWindow *Game::getWindow() {
    return &mWindow;
}

// Process all events like input or window closing.
void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            mWindow.close();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            mWindow.close();
        } else if (event.type == sf::Event::Resized) {
            // Prevent object deformation when resizing the window
            sf::FloatRect viewRect(0, 0, event.size.width, event.size.height);
            mWindow.setView(sf::View(viewRect));
        } else {
            // Delegate event handling to the current game state
            mpGameState->handleEvents(event);
        }
    }
}

// Update the current game state.
void Game::update() {
    mpGameState->update();
}

// Render the current game state.
void Game::render() {
    mWindow.clear();
    mpGameState->render();
    mWindow.display();
}
