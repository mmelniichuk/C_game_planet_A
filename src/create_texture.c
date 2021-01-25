#include "header.h"

t_texture CreateTexture(t_game *game, char *path, int x, int y, int w, int h)
{
  
    t_texture new_texture;

    new_texture.texture = IMG_LoadTexture(game->renderer, path);

    SDL_QueryTexture(new_texture.texture, NULL, NULL, &w, &h);

    SDL_Rect texr;
    texr.x = x;
    texr.y = y;
    texr.w = w;
    texr.h = h;

    new_texture.texture_info = texr;
    return new_texture;
}
