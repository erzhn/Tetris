#pragma once

#include <SFML/Graphics.hpp>

// Score class: Manages the scoring logic and display for the Tetris game.
// Inherits from sf::Drawable and sf::Transformable for graphical representation.

class Score : public sf::Drawable, public sf::Transformable {
public:
    // Constructor: Initializes the score display settings.
    Score();

    // Adds the number of lines completed to the total count.
    void addNoLinesCompleted(int n);

    // Updates the score based on the total lines completed.
    void update();

    // Getter for the current score.
    int getScore() const { return mScore; }

    // Resets the score and the total number of lines completed.
    void restartScore() {
        mScore = 0;
        mTotalLinesCompleted = 0;
    }

private:
    // Font used for rendering the score text.
    sf::Font mFont;

    // Text object for displaying the score.
    sf::Text mScoreText;

    // Total number of lines completed during the game.
    int mTotalLinesCompleted = 0;

    // Current score of the game.
    int mScore = 0;

    // Overridden draw method from sf::Drawable for rendering the score.
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
