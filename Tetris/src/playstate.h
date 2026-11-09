#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <SFML/Window/Event.hpp>

#include "gamestate.h"
#include "board.h"
#include "score.h"

// PlayState class: Manages the main gameplay phase of the Tetris game.
// This class inherits from GameState and overrides necessary methods for gameplay.

class PlayState : public GameState {
public:
    // Constructor: Initializes the PlayState with a reference to the Game object.
    PlayState(Game *pGame);

    // start method: Overrides the start method from GameState to initialize gameplay.
    void start() override;

private:
    // mBoard: Represents the game board where Tetriminos are placed and manipulated.
    Board mBoard;

    // mScore: Tracks and displays the player's score during the game.
    Score mScore;

    // handleEvents method: Overrides to handle player input events specific to gameplay.
    virtual void handleEvents(sf::Event event) override;

    // update method: Overrides to update the game logic for each frame.
    virtual void update() override;

    // render method: Overrides to render the game state on the screen.
    virtual void render() override;
};

#endif // PLAY_STATE_H
