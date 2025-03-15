#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <stdbool.h>

enum
{
    BOMB = -1,
    HIDDEN_SQUARE = -2,
    FLAG = -3,
    PLAYING = 0,
    WIN = 1,
    DEFEAT = 2,
    EASY = 1,
    MEDIUM = 2,
    HARD = 3
};

typedef struct
{
    int TAM, amount_bombs, playerWinStatus;
} definition;

// creation of game field
int **create_field(definition *game);

// creation of hidden field
int **create_hidden_field(definition *game);

// function for memory release from allocate variables
void memory_release(int **field, int **hidden_field, definition *game);

// define amount bombs and matrix size
void define_game(definition *game, int dificulty);

// game logic
void minefield(int **field, int **hidden_field, definition *game, int pos_i, int pos_j, char option);

#endif
