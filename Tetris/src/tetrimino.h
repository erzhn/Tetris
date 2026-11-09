#ifndef TETRIMINO_H
#define TETRIMINO_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>

// Tetrimino class: Represents the Tetrimino pieces in the Tetris game.
class Tetrimino {
public:
    // Types: Enum for different types of Tetrimino pieces.
    // There are 7 different types (SIZE=7).
    enum Types {
        O = 0, I, S, Z, L, J, T, SIZE
    };

    // The number of rotations each piece can have.
    static const int N_ROTACIJA = 4;

    // Matrix size for representing each Tetrimino piece.
    // Each piece is represented in a MAT_SIZExMAT_SIZE matrix.
    static const int MAT_SIZE = 4;

    // All Tetrimino shapes and their rotations are defined in this table.
    static const int mDijelovi[SIZE][N_ROTACIJA][MAT_SIZE][MAT_SIZE];

    // Colors for each type of Tetrimino.
    static const sf::Color mColors[SIZE];

    // Current type of the Tetrimino piece.
    Types mType = O;

    // Current rotation of the piece.
    int mRotacija = 0;

    // Current position of the piece on the game board.
    int mXposition = 0, mYposition = 0;

    // Clock for measuring elapsed time.
    sf::Clock mClock;

    // Method to move the Tetrimino piece to a new position.
    void move(int x, int y) {
        mXposition = x;
        mYposition = y;
    }

    // Method to rotate the Tetrimino piece to the next rotation.
    void rotate() { mRotacija = (mRotacija + 1) % N_ROTACIJA; }

private:
    // Private members can be added here if necessary.
};

#endif // TETRIMINO_H
