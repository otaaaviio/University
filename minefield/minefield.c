#include "controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#define screenWidth 800
#define screenHeight 600

// gcc minefield.c controller.c -o minefield -lallegro -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_image  && ./minefield

ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_DISPLAY *disp;
ALLEGRO_FONT *font;
ALLEGRO_TIMER *timer;
bool display_close;

// initialize allegro functions
void init_allegro()
{
    al_init();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    disp = al_create_display(screenWidth, screenHeight);
    queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60.0);
    font = al_load_font("rainyhearts.ttf", 40, 0);
    display_close = false;
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_start_timer(timer);
}

// finalize allegro functions
void destroy_allegro()
{
    al_unregister_event_source(queue, al_get_display_event_source(disp));
    al_unregister_event_source(queue, al_get_timer_event_source(timer));
    al_unregister_event_source(queue, al_get_mouse_event_source());
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
}

// draw the initial screen
void draw_home_screen()
{
    int x = 300;
    int _x = 500;
    al_clear_to_color(al_map_rgb(194, 219, 189));
    al_draw_textf(font, al_map_rgb(0, 0, 0), (800) / 2, 10, ALLEGRO_ALIGN_CENTER, "Selecione a dificuldade!");

    al_draw_filled_rectangle(x, 100, _x, 150, al_map_rgb(167, 217, 72));
    al_draw_textf(font, al_map_rgb(0, 0, 0), screenWidth / 2, 105, ALLEGRO_ALIGN_CENTER, "FÁCIL!");
    al_draw_filled_rectangle(x, 180, _x, 230, al_map_rgb(167, 217, 72));
    al_draw_textf(font, al_map_rgb(0, 0, 0), screenWidth / 2, 185, ALLEGRO_ALIGN_CENTER, "MÉDIO!");
    al_draw_filled_rectangle(x, 260, _x, 310, al_map_rgb(167, 217, 72));
    al_draw_textf(font, al_map_rgb(0, 0, 0), screenWidth / 2, 265, ALLEGRO_ALIGN_CENTER, "DIFÍCIL!");

    al_flip_display();
}

// select the square color
void select_color(int *r, int *g, int *b, int i, int j, int **hidden_field)
{
    int parity = (i + j) % 2;
    *r = hidden_field[i][j] == HIDDEN_SQUARE ? (parity == 0 ? 167 : 142) : (parity == 0 ? 229 : 215);
    *g = hidden_field[i][j] == HIDDEN_SQUARE ? (parity == 0 ? 217 : 204) : (parity == 0 ? 194 : 184);
    *b = hidden_field[i][j] == HIDDEN_SQUARE ? (parity == 0 ? 72 : 57) : (parity == 0 ? 159 : 153);
}

// draw the minefield
void draw_field(definition *game, int **field, double game_time)
{
    al_clear_to_color(al_map_rgb(194, 219, 189));

    if (game->playerWinStatus == WIN)
        al_draw_textf(font, al_map_rgb(0, 0, 0), (800 - 8) / 2, 10, ALLEGRO_ALIGN_CENTER, "VITÓRIA!");
    else if (game->playerWinStatus == DEFEAT)
        al_draw_textf(font, al_map_rgb(0, 0, 0), (800 - 8) / 2, 10, ALLEGRO_ALIGN_CENTER, "DEROTA!");
    else
        al_draw_textf(font, al_map_rgb(0, 0, 0), (800 - 8) / 2, 10, ALLEGRO_ALIGN_CENTER, "Tempo: %.0f", game_time);

    for (int i = 0; i < game->TAM; i++)
        for (int j = 0; j < game->TAM; j++)
        {
            int x = ((screenWidth - game->TAM * 42) / 2) + j * 42;
            int y = ((screenHeight - game->TAM * 42) / 2) + i * 42;
            int r, g, b;
            select_color(&r, &g, &b, i, j, field);
            al_draw_filled_rectangle(x, y, x + 40, y + 40, al_map_rgb(r, g, b));
            if (field[i][j] == BOMB)
                al_draw_filled_circle(x + 20, y + 20, 12, al_map_rgb(100, 100, 100));
            else if (field[i][j] != HIDDEN_SQUARE)
                al_draw_textf(font, al_map_rgb(0, 0, 0), x + 20, y, ALLEGRO_ALIGN_CENTER, "%d", field[i][j]);
        }

    al_flip_display();
}

// draw the final screen
void final_screen(definition *game, int **field)
{
    while (!display_close)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER)
            draw_field(game, field, 0);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            display_close = true;
    }
}

// receive player input and send this for game logic function
void game_loop(int **field, int **hidden_field, definition *game)
{
    if (!display_close)
    {
        double game_time = -1;
        while (game->playerWinStatus == PLAYING && !display_close)
        {
            game_time++;
            game_time = game_time / 60;
            ALLEGRO_EVENT event;
            al_wait_for_event(queue, &event);

            if (event.type == ALLEGRO_EVENT_TIMER)
            {
                draw_field(game, hidden_field, game_time);
            }
            else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            {
                int pos_i, pos_j;
                char option;
                int mouseX = event.mouse.x;
                int mouseY = event.mouse.y;
                for (int i = 0; i < game->TAM; i++)
                    for (int j = 0; j < game->TAM; j++)
                    {
                        int cellSize = 40;
                        int offsetX = ((screenWidth - game->TAM * 42) / 2) + i * 42;
                        int offsetY = ((screenHeight - game->TAM * 42) / 2) + j * 42;
                        if (mouseX > offsetX && mouseX < offsetX + cellSize && mouseY > offsetY && mouseY < offsetY + cellSize)
                        {
                            pos_j = i;
                            pos_i = j;
                        }
                    }
                option = 'r';
                minefield(field, hidden_field, game, pos_i, pos_j, option);
            }
            else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                display_close = true;
            }
        }
    }
}

// draw the initial screen
void home_screen(definition *game)
{
    int dificulty = 0;
    while (dificulty == 0 && !display_close)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            draw_home_screen();
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            int mouseX = event.mouse.x;
            int mouseY = event.mouse.y;
            if (mouseX > 300 && mouseX < 500)
            {
                if (mouseY > 100 && mouseY < 150)
                    dificulty = EASY;
                else if (mouseY > 180 && mouseY < 230)
                    dificulty = MEDIUM;
                else if (mouseY > 260 && mouseY < 310)
                    dificulty = HARD;
            }
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            display_close = true;
        }
    }
    define_game(game, dificulty);
}

int main()
{
    definition *game = (definition *)malloc(sizeof(definition));
    init_allegro();

    home_screen(game);
    int **field = create_field(game), **hidden_field = create_hidden_field(game);

    game_loop(field, hidden_field, game);

    final_screen(game, field);

    destroy_allegro();
    memory_release(field, hidden_field, game);

    return 0;
}
