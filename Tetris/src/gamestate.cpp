#include "gamestate.h"
#include "game.h"
#include <iostream>

// Constructor for WelcomeState: Initializes the state with text elements.
WelcomeState::WelcomeState(Game *pGame) : GameState(pGame) {
    // Load font for text display. Exit if font loading fails.
    if (!mFont.loadFromFile("data/Gasalt-Regular.ttf")) {
        std::cerr << "Cannot load font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }

    // Set font and character size for text elements.
    mText1.setFont(mFont);
    mText2.setFont(mFont);
    mText1.setCharacterSize(45);
    mText2.setCharacterSize(30);

    // Set the strings for the text elements.
    mText1.setString("Tetris by Subanbekova Aidana");
    mText2.setString("OOP");

    // Center the text elements based on their dimensions.
    mText1.setOrigin(mText1.getLocalBounds().width / 2, mText1.getLocalBounds().height / 2);
    mText2.setOrigin(mText2.getLocalBounds().width / 2, mText2.getLocalBounds().height / 2);

    // Position the text elements on the screen.
    mText1.setPosition(325, 200);
    mText2.setPosition(325, 250);

    // Initialize and position your buttons here
    playButton.setFont(mFont);
    playButton.setString("Play");
    playButton.setPosition(300, 350); // Set appropriate positions


    exitButton.setFont(mFont);
    exitButton.setString("Exit");
    exitButton.setPosition(300, 450);

}

// Handle keyboard events in the welcome state.
void WelcomeState::handleEvents(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(mpGame->getWindow()->
                mapPixelToCoords(sf::Mouse::getPosition(*mpGame->getWindow())));

        // Check if play button is clicked
        if (playButton.getGlobalBounds().contains(mousePos)) {
            // Start playing
            mpGame->setState(GameState::Playing);
        }
            // Check if exit button is clicked
        else if (exitButton.getGlobalBounds().contains(mousePos)) {
            // Exit game
            mpGame->getWindow()->close();
        }
    }
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(mpGame->getWindow()->
                mapPixelToCoords(sf::Mouse::getPosition(*mpGame->getWindow())));
        if (playButton.getGlobalBounds().contains(mousePos)) {
            playButton.setFillColor(sf::Color::Red);
        }
        else {
            playButton.setFillColor(sf::Color::White);
        }
         if (exitButton.getGlobalBounds().contains(mousePos)) {
            exitButton.setFillColor(sf::Color::Red);
        }
         else {
             exitButton.setFillColor(sf::Color::White);
         }
    }
}

// Update method for WelcomeState (no update logic needed here).
void WelcomeState::update() {
    // No specific update logic for the welcome screen.
}

// Render the text elements on the screen.
void WelcomeState::render() {
    mpGame->getWindow()->draw(mText1);
    mpGame->getWindow()->draw(mText2);
    mpGame->getWindow()->draw(playButton);
    mpGame->getWindow()->draw(exitButton);
}

// Constructor for SpeedState: Initializes the state with text elements.
SpeedState::SpeedState(Game *pGame) : GameState(pGame) {
    // Load font and setup text elements similar to WelcomeState.

    // The rest of the constructor sets up additional text elements
    // specific to the SpeedState, such as displaying the current speed
    // and score, and instructions for changing the speed.
    if (!mFont.loadFromFile("data/Gasalt-Regular.ttf")) {
        std::cerr << "Error font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }

    mText0.setFont(mFont);
    mText0.setCharacterSize(30);
    mText0.setString("Score " + std::to_string(mpGame->mGameScore));
    mText0.setOrigin(mText0.getLocalBounds().width / 2, mText0.getLocalBounds().height / 2);
    mText0.setPosition(325, 200);

    mText1.setFont(mFont);
    mText1.setCharacterSize(30);
    mText1.setString("Current speed " + std::to_string(mpGame->mGameSpeed));
    mText1.setOrigin(mText1.getLocalBounds().width / 2, mText1.getLocalBounds().height / 2);
    mText1.setPosition(325, 250);

    mText2.setFont(mFont);
    mText2.setCharacterSize(30);
    mText2.setString("Use keys Up and Down to change the speed");
    mText2.setOrigin(mText2.getLocalBounds().width / 2, mText2.getLocalBounds().height / 2);
    mText2.setPosition(325, 300);

    mText3.setFont(mFont);
    mText3.setCharacterSize(50);
    mText3.setString("Enter to continue");
    mText3.setOrigin(mText3.getLocalBounds().width / 2, mText3.getLocalBounds().height / 2);
    mText3.setPosition(325, 350);
}

// Handle keyboard events in the SpeedState.
void SpeedState::handleEvents(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Up:
                // Increase game speed.
                mpGame->mGameSpeed += 0.5;
                break;
            case sf::Keyboard::Down:
                // Decrease game speed, ensuring it doesn't go below a minimum.
                if (mpGame->mGameSpeed > 0.5)
                    mpGame->mGameSpeed -= 0.5;
                break;
            case sf::Keyboard::Return:
                // Change to Playing state when Enter is pressed.
                mpGame->setState(GameState::Playing);
                break;
        }
    }
}

// Update method for SpeedState: Updates the speed display text.
void SpeedState::update() {
    // Update the text displaying the current score and game speed.
    mText0.setString("Score = " + std::to_string(mpGame->mGameScore));
}

// Render the text elements on the screen for SpeedState.
void SpeedState::render() {
    // Draw all the text elements related to speed adjustment and score.
    mpGame->getWindow()->draw(mText0);
    mpGame->getWindow()->draw(mText1);
    mpGame->getWindow()->draw(mText2);
    mpGame->getWindow()->draw(mText3);
}
