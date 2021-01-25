#pragma once

//фреймворки
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

//системные библиотеки
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>

#include "list.h"

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

typedef enum            enum_trash_type
{
    GLASS,
    METAL,
    ORGANIC,
    PAPER,
    PLASTIC,
    E_WASTE
}                       e_trash_type;

typedef struct          s_vector
{
    int x;
    int y;
}                       t_vector;

typedef struct          s_texture
{
    SDL_Texture         *texture;
    SDL_Rect            texture_info;
}                       t_texture;

typedef struct          s_trash_texture
{
    t_texture           texture;
    e_trash_type        trash_type;
    
}                       t_trash_texture;

typedef struct          s_game
{
    SDL_Window          *window;
    SDL_Renderer        *renderer;
    SDL_Event           event;

    TTF_Font            *font;

    t_texture           background;
    t_texture           play_button;
    t_texture           game_over_pic;

    t_trash_texture     trash_buckets[6];
    t_trash_texture     *HoldingTrash;

    t_list              *trash;

    char                *trash_buckets_paths[6];
    char                *trash_texture_path[18];
    
    bool                isMenu;
    bool                game_over;
    
    int                 score;
    int                 health;
    int                 max_trash_amount;

}                       t_game;

t_texture               CreateTexture(t_game *game, char *path, int x, int y, int w, int h);

void                    trash_bucket_creating(t_game *game);

void                    update_trash_list(t_game *game);
void                    set_trash_pathes(t_game *game);

void                    CreateTextWidget(t_game *game, const char *text, SDL_Color color, int x, int y, int w, int h);
void                    DrawUI(t_game *game);








