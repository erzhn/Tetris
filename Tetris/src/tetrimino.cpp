#include "tetrimino.h"

// Array of colors corresponding to different types of Tetriminos.
const sf::Color Tetrimino::mColors[SIZE] = {
        sf::Color::Blue,    // Color for the first type of Tetrimino.
        sf::Color::Red,     // Color for the second type.
        sf::Color::Green,   // Color for the third type.
        sf::Color::Cyan,    // Color for the fourth type.
        sf::Color::Magenta, // Color for the fifth type.
        sf::Color::Yellow,  // Color for the sixth type.
        sf::Color(195, 132, 58) // Custom color for the seventh type.
};

// Multi-dimensional array representing the shapes of Tetriminos in different rotations.
// SIZE - Number of Tetrimino types.
// N_ROTACIJA - Number of possible rotations.
// MAT_SIZE - Size of the matrix representing the shape of a Tetrimino.
const int Tetrimino::mDijelovi[SIZE][N_ROTACIJA][MAT_SIZE][MAT_SIZE] = {
        { // O
                {
                        {0, 0, 0, 0},
                        {0, 1, 2, 0},
                        {0, 1, 1, 0},
                        {0, 0, 0, 0}
                },
                {
                        {0, 0, 0, 0},
                        {0, 1, 2, 0},
                        {0, 1, 1, 0},
                        {0, 0, 0, 0}
                },
                {
                        {0, 0, 0, 0},
                        {0, 1, 2, 0},
                        {0, 1, 1, 0},
                        {0, 0, 0, 0}
                },
                {
                        {0, 0, 0, 0},
                        {0, 1, 2, 0},
                        {0, 1, 1, 0},
                        {0, 0, 0, 0}
                }
        },
        {//I
                {
                        {0, 0, 0, 0},
                        {1, 1, 2, 1},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0}
                },
                {
                        {0, 0, 1, 0},
                        {0, 0, 2, 0},
                        {0, 0, 1, 0},
                        {0, 0, 1, 0}
                },
                {
                        {0, 0, 0, 0},
                        {1, 1, 2, 1},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0}
                },
                {
                        {0, 0, 1, 0},
                        {0, 0, 2, 0},
                        {0, 0, 1, 0},
                        {0, 0, 1, 0}
                }
        },
        {//S
                {
                        {0, 0, 0, 0},
                        {0, 0, 2, 1},
                        {0, 1, 1, 0},
                        {0, 0, 0, 0}
                },
                {
                        {0, 0, 1, 0},
                        {0, 0, 2, 1},
                        {0, 0, 0, 1},
                        {0, 0, 0, 0}
                },
                {
                        {0, 0, 0, 0},
                        {0, 0, 2, 1},
                        {0, 1, 1, 0},
                        {0, 0, 0, 0}
                },
                {
                        {0, 0, 1, 0},
                        {0, 0, 2, 1},
                        {0, 0, 0, 1},
                        {0, 0, 0, 0}
                }
        },
        {//Z
                {
                        {0, 0, 0, 0},
                        {0, 1, 2, 0},
                        {0, 0, 1, 1},
                        {0, 0, 0, 0}
                },
                {
                        {0, 0, 0, 1},
                        {0, 0, 2, 1},
                        {0, 0, 1, 0},
                        {0, 0, 0, 0}
                },
                {
                        {0, 0, 0, 0},
                        {0, 1, 2, 0},
                        {0, 0, 1, 1},
                        {0, 0, 0, 0}
                },
                {
                        {0, 0, 0, 1},
                        {0, 0, 2, 1},
                        {0, 0, 1, 0},
                        {0, 0, 0, 0}
                }
        },
        {//L
                {
                        {0, 0, 0, 0},
                        {0, 1, 2, 1},
                        {0, 1, 0, 0},
                        {0, 0, 0, 0}
                },
                {
                        {0, 0, 1, 0},
                        {0, 0, 2, 0},
                        {0, 0, 1, 1},
                        {0, 0, 0, 0}
                },
                {
                        {0, 0, 0, 1},
                        {0, 1, 2, 1},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0}
                },
                {
                        {0, 1, 1, 0},
                        {0, 0, 2, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 0}
                }
        },
        {//J
                {
                        {0, 0, 0, 0},
                        {0, 1, 2, 1},
                        {0, 0, 0, 1},
                        {0, 0, 0, 0}
                },
                {
                        {0, 0, 1, 1},
                        {0, 0, 2, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 0}
                },
                {
                        {0, 1, 0, 0},
                        {0, 1, 2, 1},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0}
                },
                {
                        {0, 0, 1, 0},
                        {0, 0, 2, 0},
                        {0, 1, 1, 0},
                        {0, 0, 0, 0}
                }
        },
        {//T
                {
                        {0, 0, 0, 0},
                        {0, 1, 2, 1},
                        {0, 0, 1, 0},
                        {0, 0, 0, 0}
                },
                {
                        {0, 0, 1, 0},
                        {0, 0, 2, 1},
                        {0, 0, 1, 0},
                        {0, 0, 0, 0}
                },
                {
                        {0, 0, 1, 0},
                        {0, 1, 2, 1},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0}
                },
                {
                        {0, 0, 1, 0},
                        {0, 1, 2, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 0}
                }
        }
};

