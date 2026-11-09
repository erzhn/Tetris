#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>

class Game;

// Abstract class GameState: Base class for different game states.
class GameState {
public:
    // Constructor: Initializes the GameState with a pointer to the Game object.
    GameState(Game *pGame) : mpGame(pGame) {}

    // Virtual Destructor: Ensures proper cleanup of derived classes.
    virtual ~GameState() {}

    // Enum for all possible game states.
    enum State {
        Welcome,  // Welcome screen state
        Playing,  // Main gameplay state
        Speed,    // Speed adjustment state
        SIZE      // Total number of states
    };

    // Pure virtual methods that must be implemented in derived classes.
    virtual void handleEvents(sf::Event event) = 0; // Handle user input events
    virtual void update() = 0;                      // Update game state logic
    virtual void render() = 0;                      // Render the game state

    // Virtual method for restarting the game, to be overridden in derived classes.
    virtual void start() {}

protected:
    // Pointer to the Game object to allow state interaction with the game.
    Game *const mpGame;
};

// WelcomeState: Manages the welcome screen of the game.
class WelcomeState : public GameState {
public:
    // Constructor: Initializes the welcome screen with necessary resources.
    WelcomeState(Game *pGame);

    // Override methods from the GameState class.
    virtual void handleEvents(sf::Event event) override; // Handle events in welcome state
    virtual void update() override;                      // Update logic for welcome state (typically empty)
    virtual void render() override;                      // Render welcome screen


private:
    // Text elements for displaying messages on the welcome screen.
    sf::Text mText1; // Main welcome message
    sf::Text mText2; // Instruction message
    sf::Font mFont;  // Font used for the text elements
    sf::Text playButton;
    sf::Text exitButton;
};

// SpeedState: Manages the game speed adjustment screen.
class SpeedState : public GameState {
public:
    // Constructor: Initializes the speed adjustment screen with necessary resources.
    SpeedState(Game *pGame);

    // Override methods from the GameState class.
    virtual void handleEvents(sf::Event event) override; // Handle events in speed state
    virtual void update() override;                      // Update logic for speed state
    virtual void render() override;                      // Render speed adjustment screen

private:
    // Text elements for displaying speed information and instructions.
    sf::Text mText0; // Display current score
    sf::Text mText1; // Display current speed
    sf::Text mText2; // Instructions for changing speed
    sf::Text mText3; // Instructions to continue
    sf::Font mFont;  // Font used for the text elements
};

#endif // GAMESTATE_H
