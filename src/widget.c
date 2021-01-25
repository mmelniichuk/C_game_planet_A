#include "header.h"

static SDL_Color MakeColor(int r, int g, int b, int a)
{
	SDL_Color NewColor;

	NewColor.r = r;
	NewColor.g = g;
	NewColor.b = b;
	NewColor.a = a;
	
	return NewColor;
}

void DrawUI(t_game *game)
{	
	char text[512];

	sprintf(text, "SCORE: %d", game->score);
	CreateTextWidget(game, text, MakeColor(0, 0, 255, 255), 25, 2, 150, 100);

	sprintf(text, "HEALTH: %d", game->health);
	CreateTextWidget(game, text, MakeColor(255, 0, 0, 255), SCREEN_WIDTH - 175, 2, 150, 100);
}

void CreateTextWidget(t_game *game, const char *text, SDL_Color color, int x, int y, int w, int h)
{
    SDL_Surface *scoreSur = TTF_RenderText_Solid(game->font, text, color);
    SDL_Texture *scoreTex = SDL_CreateTextureFromSurface(game->renderer, scoreSur);
    SDL_Rect scoreRect = {x, y, w, h};
    
    SDL_RenderCopy(game->renderer, scoreTex, NULL, &scoreRect);
    SDL_FreeSurface(scoreSur);
    SDL_DestroyTexture(scoreTex);

}
