#include "score.h"
#include <iostream>

// Score class: Manages and displays the player's score in the Tetris game.

// Constructor: Initializes the Score object and loads the font for displaying the score.
Score::Score() {
    // Load the font file. Exit if the font cannot be loaded.
    if (!mFont.loadFromFile("data/Gasalt-Regular.ttf")) {
        std::cerr << "Cannot load font: Gasalt-Regular.ttf!" << std::endl;
        std::exit(1);
    }

    // Set up the text object for displaying the score.
    mScoreText.setFont(mFont); // Set the font for the score text.
    mScoreText.setCharacterSize(40); // Set the font size.
    mScoreText.setString("Score: " + std::to_string(mScore)); // Initialize score text.
    mScoreText.setPosition(440, 200); // Position the score text on the screen.
}

// addNoLinesCompleted method: Increments the total number of lines completed.
void Score::addNoLinesCompleted(int n) {
    mTotalLinesCompleted += n; // Add to the total count of lines completed.
    // Note: Make sure to update mScore accordingly.
}

// update method: Updates the score based on the number of lines completed.
void Score::update() {
    mScore = mTotalLinesCompleted * 10; // Calculate the score.
    mScoreText.setString("Score: " + std::to_string(mScore)); // Update the score display.
}

// draw method: Draws the score text to the screen.
void Score::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform(); // Apply the current transform.
    target.draw(mScoreText); // Draw the score text to the target.
}
