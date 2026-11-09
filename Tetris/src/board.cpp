#include "board.h"

// Constructor for the Board class
Board::Board() : mUniformDist(0, 6), mRNE(r()) {
    // Initialize the game board to an empty state
    clearState();

    // Set up dimensions and margins for drawing the game board
    mDx = 30.0f;
    mDy = 30.0f;

    // Construct the grid lines for the board
    float y = 0.0f;
    // Horizontal lines
    for (int i = 0; i <= 20; ++i) {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(mLeftMargin, mTopMargin + y);
        line[1].position = sf::Vector2f(mLeftMargin + mWidth, mTopMargin + y);
        mHLines.push_back(line);
        y += mDy;
    }
    // Vertical lines
    for (int i = 0; i <= 10; ++i) {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(mLeftMargin + i * mDx, mTopMargin);
        line[1].position = sf::Vector2f(mLeftMargin + i * mDx, mTopMargin + mHeight);
        mVLines.push_back(line);
    }

    // Spawn the first Tetrimino
    spawnPiece();
}

// Destructor for the Board class
Board::~Board() {

}

// Update the state of the board and handle player inputs
void Board::update(bool leftPressed, bool rightPressed, bool upPressed, bool downPressed) {
    // Check if the Tetrimino should fall down based on the elapsed time
    if (mPiece.mClock.getElapsedTime() > sf::seconds(mDt)) {
        if (movePiece(mPiece.mXposition + 1, mPiece.mYposition)) {
            mPiece.mClock.restart();
        } else {
            // Tetrimino has reached the bottom or another piece
            mNoLinesCompleted = clearLines();
            spawnPiece();
        }
    }

    // Handle left, right, up (rotate), and down (drop) inputs
    if (leftPressed) {
        movePiece(mPiece.mXposition, mPiece.mYposition - 1);
    } else if (rightPressed) {
        movePiece(mPiece.mXposition, mPiece.mYposition + 1);
    } else if (upPressed) {
        rotatePiece();
    } else if (downPressed) {
        // Drop the piece quickly
        while (movePiece(mPiece.mXposition + 1, mPiece.mYposition));
    }
}

// Spawn a new Tetrimino at the top of the board
void Board::spawnPiece() {
    // Set the initial position of the piece
    mPiece.move(0, (mCols + 1) / 2);

    // Randomly choose the type of the new Tetrimino
    int tip = mUniformDist(mRNE);
    mPiece.mType = static_cast<Tetrimino::Types>(tip);
    mPiece.mRotacija = 0;
    mPiece.mClock.restart();

    // Check for game over condition
    if (!mGameOver) {
        mGameOver = !checkSpace();
    }
    if (mGameOver) {
        int y = mPiece.mYposition;

        bool flag = true;

        int k = 0;
        while (k < 3) {

            flag = true;
            for (int i = k; i < 3; ++i) {
                for (int j = -2; j < 2; ++j) {
                    if ((Tetrimino::mDijelovi[mPiece.mType][0][i + 1][j + 2] != 0) &&
                        (mGridContent[i - k][y + j] != EMPTY)) {
                        flag = false;
                    }
                }
            }
            if (flag) {
                for (int i = k; i < 3; ++i) {
                    for (int j = -2; j < 2; ++j) {
                        if (Tetrimino::mDijelovi[mPiece.mType][0][i + 1][j + 2] != 0)
                            mGridContent[i - k][y + j] = mPiece.mType;
                    }
                }
                break;
            }
            ++k;
        }
    } else {
        placePiece();
    }
}

// Clear the game board state
void Board::clearState() {
    // Reset each cell of the board to empty
    for (int i = 0; i < mRows; ++i)
        for (int j = 0; j < mCols; ++j)
            mGridContent[i][j] = EMPTY;

    // Reset the game over flag
    mGameOver = false;
}

// Draw the board and the pieces on it
void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // Draw grid lines
    for (auto x: mHLines)
        target.draw(x);
    for (auto x: mVLines)
        target.draw(x);

    // Draw each cell of the Tetriminos
    sf::RectangleShape celija;
    celija.setSize(sf::Vector2f(28.7, 28.7));
    for (int i = 0; i < mRows; ++i) {
        for (int j = 0; j < mCols; ++j) {
            if (mGridContent[i][j] != EMPTY) {
                // Set the color and position of the cell
                celija.setFillColor(Tetrimino::mColors[static_cast<Tetrimino::Types>(mGridContent[i][j])]);
                celija.setOrigin(1, 1);
                celija.setOutlineThickness(1);
                celija.setPosition(1.5 + mLeftMargin + j * mDy, 2 + mTopMargin + i * mDx);

                target.draw(celija);
            }
        }
    }
}

// Check if there is space for the current Tetrimino in its position
bool Board::checkSpace() {
    bool flag = true;
    int x = mPiece.mXposition;
    int y = mPiece.mYposition;
    for (int i = -1; i < 3; ++i) {
        for (int j = -2; j < 2; ++j) {
            // Check within the bounds of the board
            if (0 <= (x + i) && (x + i) < mRows && 0 <= (y + j) && (y + j) < mCols) {
                // Check if the Tetrimino overlaps with filled cells
                if ((Tetrimino::mDijelovi[mPiece.mType][mPiece.mRotacija][i + 1][j + 2] != 0)
                    && mGridContent[x + i][y + j] != EMPTY) {
                    flag = false;
                }
            }
                // If part of the Tetrimino is outside the board, no space is available
            else if (Tetrimino::mDijelovi[mPiece.mType][mPiece.mRotacija][i + 1][j + 2] != 0) {
                flag = false;
            }
        }
    }
    return flag;
}

// Place the Tetrimino on the board in its current position
void Board::placePiece() {
    int x = mPiece.mXposition;
    int y = mPiece.mYposition;
    for (int i = -1; i < 3; ++i) {
        for (int j = -2; j < 2; ++j) {
            // Only update cells within the board boundaries
            if (0 <= (x + i) && (x + i) < mRows && 0 <= (y + j) && (y + j) < mCols) {
                if (Tetrimino::mDijelovi[mPiece.mType][mPiece.mRotacija][i + 1][j + 2] != 0) {
                    mGridContent[x + i][y + j] = mPiece.mType;
                }
            }
        }
    }
}

// Remove the Tetrimino from its current position on the board
void Board::removePiece() {
    int x = mPiece.mXposition;
    int y = mPiece.mYposition;
    for (int i = -1; i < 3; ++i) {
        for (int j = -2; j < 2; ++j) {
            if (0 <= (x + i) && (x + i) < mRows && 0 <= (y + j) && (y + j) < mCols) {
                if (Tetrimino::mDijelovi[mPiece.mType][mPiece.mRotacija][i + 1][j + 2] != 0) {
                    mGridContent[x + i][y + j] = EMPTY;
                }
            }
        }
    }
}

// Move the Tetrimino to a new position if possible
bool Board::movePiece(int newX, int newY) {
    // Remember the old position
    int oldX = mPiece.mXposition;
    int oldY = mPiece.mYposition;

    // Remove the Tetrimino from its current position
    removePiece();

    // Try moving the Tetrimino to the new position
    mPiece.move(newX, newY);
    if (checkSpace()) {
        // If there's space at the new position, update the board
        placePiece();
        return true;
    } else {
        // If not, move back to the old position
        mPiece.move(oldX, oldY);
        placePiece();
        return false;
    }
}

// Rotate the Tetrimino if possible
bool Board::rotatePiece() {
    removePiece();
    bool canRotate = false;
    for (int i = 0; i < 4 && !canRotate; ++i) {
        mPiece.rotate();
        if (checkSpace()) {
            canRotate = true;
            placePiece();
        }
    }
    if (!canRotate) {
        // If rotation is not possible, revert to the original rotation
        mPiece.rotate(); // This will rotate it back to the original rotation after 4 rotations
        placePiece();
    }
    return canRotate;
}

// Check if a line is full and needs to be cleared
bool Board::isLineFull(int y) const {
    for (int j = 0; j < mCols; ++j) {
        if (mGridContent[y][j] == EMPTY)
            return false;
    }
    return true;
}

// Clear full lines from the board and return the number of lines cleared
int Board::clearLines() {
    int clearedLines = 0;
    for (int i = mRows - 1; i >= 0;) {
        if (isLineFull(i)) {
            // Clear the line and move down the rest of the lines
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < mCols; j++) {
                    mGridContent[k][j] = mGridContent[k - 1][j];
                }
            }
            // Set the top line to empty
            for (int j = 0; j < mCols; j++) {
                mGridContent[0][j] = EMPTY;
            }
            clearedLines++;
        } else {
            i--;
        }
    }
    return clearedLines;
}








