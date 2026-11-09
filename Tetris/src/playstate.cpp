#include "playstate.h"
#include "game.h"

#include <thread>         // Used for pausing the thread
#include <chrono>         // Used for time durations

// PlayState class: Manages the gameplay state of the Tetris game.

// Constructor: Initializes the PlayState with a pointer to the Game object.
PlayState::PlayState(Game *pGame) : GameState(pGame) {

}

float temp = 0;

// start method: Resets and initializes the gameplay elements.
void PlayState::start() {
    // Clear the board state and set the game speed.
    mBoard.clearState();
    mBoard.setSpeed(mpGame->mGameSpeed);

    // Reset the game score.
    mpGame->mGameScore = 0;

    // Reset the score manager.
    mScore.restartScore();
}

// handleEvents method: Responds to keyboard inputs during gameplay.
void PlayState::handleEvents(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Left:
                // Move the Tetrimino left.
                mBoard.update(1, 0, 0, 0);
                break;
            case sf::Keyboard::Right:
                // Move the Tetrimino right.
                mBoard.update(0, 1, 0, 0);
                break;
            case sf::Keyboard::Up:
                // Rotate the Tetrimino.
                mBoard.update(0, 0, 1, 0);
                break;
            case sf::Keyboard::Space:
                // Drop the Tetrimino.
                mBoard.update(0, 0, 0, 1);
                break;
            case sf::Keyboard::Down:
                temp += mBoard.getSpeed() + 2.0f;
                mBoard.setSpeed(temp);
                break;
        }
    }
}

// update method: Updates the game logic.
void PlayState::update() {
    if (!mBoard.isGameOver()) {
        // Update the score based on the number of lines completed.
        mScore.addNoLinesCompleted(mBoard.getNoLinesCompleted());

        // Clear the count of lines completed.
        mBoard.clearNoLinesCompleted();

        // Update the board state.
        mBoard.update(0, 0, 0, 0);

        // Update the score display.
        mScore.update();

        mBoard.setSpeed(3.0f);
        // Update the game score.
        mpGame->mGameScore = mScore.getScore();

    } else {
        // If the game is over, pause briefly and then switch to the Speed state.
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        mpGame->setState(GameState::Speed);
    }
}

// render method: Renders the game elements to the screen.
void PlayState::render() {
    // Draw the game board and score on the window.
    mpGame->getWindow()->draw(mBoard);
    mpGame->getWindow()->draw(mScore);
}
