#include "controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

int **create_field(definition *game)
{
    srand(time(0));
    int i, j, k, x;

    int **field = (int **)malloc(game->TAM * sizeof(int *));
    for (i = 0; i < game->TAM; i++)
        field[i] = (int *)malloc(game->TAM * sizeof(int));

    // fill bombs in the field
    for (i = 0; i < game->amount_bombs; i++)
    {
        int a = rand() % game->TAM;
        int b = rand() % game->TAM;
        field[a][b] = BOMB;
    }

    // fill bomb count in adjacent squares
    for (i = 0; i < game->TAM; i++)
        for (j = 0; j < game->TAM; j++)
            if (field[i][j] != BOMB)
            {
                int count = 0;
                for (k = i - 1; k < i + 2; k++)
                    for (x = j - 1; x < j + 2; x++)
                    {
                        if (k >= 0 && x >= 0 && k < game->TAM && x < game->TAM)
                            if (field[k][x] == BOMB)
                                count++;
                    }
                field[i][j] = count;
            }
    return field;
}

int **create_hidden_field(definition *game)
{
    int **hidden_field = (int **)malloc(game->TAM * sizeof(int *));
    for (int i = 0; i < game->TAM; i++)
        hidden_field[i] = (int *)malloc(game->TAM * sizeof(int));

    for (int i = 0; i < game->TAM; i++)
        for (int j = 0; j < game->TAM; j++)
            hidden_field[i][j] = HIDDEN_SQUARE;

    return hidden_field;
}

void memory_release(int **field, int **hidden_field, definition *game)
{
    for (int i = 0; i < game->TAM; i++)
        free(field[i]);
    free(field);

    for (int i = 0; i < game->TAM; i++)
        free(hidden_field[i]);
    free(hidden_field);

    free(game);
}

void define_game(definition *game, int dificulty)
{
    game->playerWinStatus = PLAYING;

    switch (dificulty)
    {
    case EASY:
        game->amount_bombs = 5;
        game->TAM = 5;
        break;
    case MEDIUM:
        game->amount_bombs = 15;
        game->TAM = 8;
        break;
    case HARD:
        game->amount_bombs = 30;
        game->TAM = 10;
        break;
    }
}

void minefield(int **field, int **hidden_field, definition *game, int pos_i, int pos_j, char option)
{
    if (pos_j >= 0 && pos_j < game->TAM && pos_i >= 0 && pos_i < game->TAM && hidden_field[pos_i][pos_j] == HIDDEN_SQUARE)
    {
        int count = 0, count_flags = 0;
        int i, j;

        if (option == 'b')
        {
            hidden_field[pos_i][pos_j] = FLAG;

            for (i = 0; i < game->TAM; i++)
                for (j = 0; j < game->TAM; j++)
                    if (hidden_field[i][j] == FLAG)
                    {
                        if (field[i][j] == BOMB)
                            count++;
                        count_flags++;
                    }

            if (count == game->amount_bombs && count_flags == game->amount_bombs)
                game->playerWinStatus = WIN;
        }
        else
        {
            if (field[pos_i][pos_j] == BOMB)
                game->playerWinStatus = DEFEAT;

            else if (field[pos_i][pos_j] == 0)
            {
                for (int i = pos_i - 1; i < pos_i + 2; i++)
                    for (int j = pos_j - 1; j < pos_j + 2; j++)
                        if (i >= 0 && j >= 0 && i < game->TAM && j < game->TAM)
                            hidden_field[i][j] = field[i][j];
            }
            else
                hidden_field[pos_i][pos_j] = field[pos_i][pos_j];

            int count_revealed = 0;
            for (int i = 0; i < game->TAM; i++)
                for (int j = 0; j < game->TAM; j++)
                    if (hidden_field[i][j] != HIDDEN_SQUARE)
                        count_revealed++;

            if (count_revealed == (game->TAM * game->TAM - game->amount_bombs))
                game->playerWinStatus = WIN;
        }
    }
}
