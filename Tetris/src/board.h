#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "tetrimino.h"
#include <random>
#include <vector>

// Class Board: Manages the logic and state of the Tetris game.
class Board : public sf::Drawable, public sf::Transformable, public sf::NonCopyable {
public:
    // Constructor: Initializes the game board.
    Board();

    // Destructor: Handles cleanup when a Board object is destroyed.
    ~Board();

    // Updates the game state based on player input and time.
    void update(bool leftPressed, bool rightPressed, bool upPressed, bool downPressed);

    // Spawns a new Tetrimino piece on the board.
    void spawnPiece();

    // Returns true if the game is over, false otherwise.
    bool isGameOver() const { return mGameOver; }

    // Resets the game state to a clear board.
    void clearState();

    // Returns the number of lines completed in the last update.
    int getNoLinesCompleted() const { return mNoLinesCompleted; }

    // Resets the count of lines completed to zero.
    void clearNoLinesCompleted() { mNoLinesCompleted = 0; }

    // Sets the speed of falling Tetriminos.
    void setSpeed(float speed) { mDt = 1.0f / speed; }

    // Gets the current speed of falling Tetriminos.
    float getSpeed() const { return 1.0f / mDt; }

private:
    // Constant representing an empty cell on the board.
    static const int EMPTY = -1;

    // Number of columns and rows in the game board.
    static const int mCols = 10;
    static const int mRows = 2 * mCols;

    // Arrays to store horizontal and vertical grid lines for rendering.
    std::vector<sf::VertexArray> mHLines; // Horizontal lines
    std::vector<sf::VertexArray> mVLines; // Vertical lines

    // Logical representation of the grid (game board).
    int mGridContent[mRows][mCols];

    // Dimensions and margins for rendering the grid.
    float mLeftMargin = 70.f;
    float mTopMargin = 70.0f;
    float mWidth = 300.f;
    float mHeight = 2 * mWidth;

    // Dimensions of grid cells.
    float mDx, mDy;

    // Time delay for Tetrimino fall (in seconds).
    float mDt = 0.3f;

    // Flag to indicate if the game is over.
    bool mGameOver = false;

    // Number of lines completed in one move (can be 0, 1, 2, 3, or 4).
    int mNoLinesCompleted = 0;

    // Random number generation for spawning new Tetriminos.
    std::random_device r;
    std::default_random_engine mRNE;
    std::uniform_int_distribution<> mUniformDist;

    // Current active Tetrimino piece.
    Tetrimino mPiece;

    // Overridden draw method for rendering the board.
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    // Checks if there is space to place the current Tetrimino.
    bool checkSpace();

    // Places the Tetrimino on the board. Assumes checkSpace() is true.
    void placePiece();

    // Removes the Tetrimino from the board.
    void removePiece();

    // Moves the Tetrimino to a new position if possible. Returns true if successful.
    bool movePiece(int x, int y);

    // Rotates the Tetrimino if possible. Returns true if successful.
    bool rotatePiece();

    // Checks if a specific line is full and needs to be cleared.
    bool isLineFull(int y) const;

    // Clears complete lines from the board and returns the number of lines cleared.
    int clearLines();

    // Method to delete a specific line and shift lines above it down.
    // void deleteLine(int y);
};

#endif // BOARD_H
