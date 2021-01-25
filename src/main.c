#include "header.h"

static void     LoseHealth(t_game *game)
{
    game->health = game->health - 1;
    if (game->health <= 0)
    {
        //free(game->trash->next);
        //free(game->trash->data);
        game->score = 0;
        game->health = 3;
        //TEMPORARY GAME OVER LOGIC
        //game->game_over = true;
        game->isMenu = true;
    }
}

static double GetDistance(t_vector v1, t_vector v2)
{
    return sqrt(pow((v2.x - v1.x), 2) + pow((v2.y - v1.y), 2));
}

static bool IsMouseOverlappWithTexture(int MouseX, int MouseY, const SDL_Rect *texture_info)
{
    return (MouseX > texture_info->x
            && (MouseX <= texture_info->x + texture_info->w)
            &&  MouseY > texture_info->y
            && (MouseY <= texture_info->y + texture_info->h));
}

static bool IsTextureOverlappWithTexture(const SDL_Rect *texture_info1, const SDL_Rect *texture_info2)
{
    t_vector C1;
    C1.x = texture_info1->x + texture_info1->w / 2;
    C1.y = texture_info1->y + texture_info1->h / 2;

    t_vector C2;
    C2.x = texture_info2->x + texture_info2->w / 2;
    C2.y = texture_info2->y + texture_info2->h / 2;

    double DistanceBetweenCenters = GetDistance(C1, C2);

    return ((DistanceBetweenCenters <= (texture_info1->w + texture_info2->w) / 2)
        || (DistanceBetweenCenters <= (texture_info1->h + texture_info2->h) / 2));
}

static void CheckCollision(t_game *game, t_trash_texture *trash)
{
    for (int i = 0; i < 6; ++i)
    {
        if (IsTextureOverlappWithTexture(&trash->texture.texture_info, &game->trash_buckets[i].texture.texture_info))
        {
            if (trash->trash_type == game->trash_buckets[i].trash_type)
            {
                game->score++;
            }
            else
            {
                LoseHealth(game);   
            }
            SDL_DestroyTexture(trash->texture.texture);
            remove_elem(&game->trash, trash);
            break;
        }
    }
}

static int processEvents(t_game *game) {
    while(SDL_PollEvent(&game->event))
    {
        switch(game->event.type)
        {
            case SDL_WINDOWEVENT_CLOSE:
                if (game->window)
                {
                    SDL_DestroyWindow(game->window);
                    game->window = NULL;
                }
                break;
            case SDL_KEYDOWN:
                switch (game->event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        return 1;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (game->event.button.button == SDL_BUTTON_LEFT)
                {
                    int x = game->event.button.x;
                    int y = game->event.button.y;

                    if (game->isMenu)
                    {
                        if (IsMouseOverlappWithTexture(x, y, &game->play_button.texture_info))
                        {
                            trash_bucket_creating(game);
                            game->isMenu = false;
                        }
                    }
                    else
                    {
                        t_list *tmp = game->trash;
                        while (tmp)
                        {
                            t_trash_texture *trash_texture = (t_trash_texture *)tmp->data;
                            if (IsMouseOverlappWithTexture(x, y, &trash_texture->texture.texture_info))
                            {
                                game->HoldingTrash = trash_texture;
                                break;
                            }
                            tmp = tmp->next;
                        }
                    } 
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (game->HoldingTrash)
                {
                    CheckCollision(game, game->HoldingTrash);
                    game->HoldingTrash = NULL;
                }            
                break;
            case SDL_QUIT:
                return 1;
            }
    }
    return 0;
}

int main()
{
    int done = 0;

    t_game game;
    
    game.isMenu = true;
    game.game_over = false;
    game.HoldingTrash = NULL;
    game.score = 0;
    game.health = 3;
    game.max_trash_amount = 2;

    set_trash_pathes(&game);
 
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    Mix_Music *music = NULL;

    game.font = TTF_OpenFont("resource/Crazy-Pixel.ttf", 24);

    if (!game.font)
    {
        printf("Bad path to font.\n");
        return -1;
    }
    
    game.window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    if (game.window == NULL)
    {
        printf("Could not create window: %s\n", SDL_GetError());
        return -1;
    }

    game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);
    game.background = CreateTexture(&game, "resource/images/backgroundcopy.png", 0, 0, 1080, 720);
    game.play_button = CreateTexture(&game, "resource/images/PlayButton.png", 390, 200, 300, 225);

   if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	return -1;

    music = Mix_LoadMUS("resource/tt.mp3");
    if (music)
    {
	Mix_PlayMusic(music, -1);
    }
    else
	printf("Didn't load nusic\n");

    while (!done)
    {
        done = processEvents(&game);
        
        SDL_RenderClear(game.renderer);

        if (game.isMenu)
        {          
            SDL_RenderCopy(game.renderer, game.background.texture, NULL, &game.background.texture_info);
            SDL_RenderCopy(game.renderer, game.play_button.texture, NULL, &game.play_button.texture_info);
            SDL_RenderPresent(game.renderer);
        }
        else
        {
            SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, 0);
            SDL_RenderFillRect(game.renderer, &game.background.texture_info);
            
            for (int i = 0; i < 6; ++i)
            {
                SDL_RenderCopy(game.renderer, game.trash_buckets[i].texture.texture,
                    NULL, &game.trash_buckets[i].texture.texture_info);
            }

            update_trash_list(&game);

            t_list *tmp = game.trash;

            while (tmp)
            {
                t_trash_texture *trash_texture = (t_trash_texture *)tmp->data;
                if (trash_texture != game.HoldingTrash)
                {
                    SDL_RenderCopy(game.renderer, trash_texture->texture.texture, 
                                    NULL, &trash_texture->texture.texture_info);
                    trash_texture->texture.texture_info.y++;
                    CheckCollision(&game, trash_texture);
                }
                else
                {
                    int MouseX, MouseY;

                    SDL_GetMouseState(&MouseX, &MouseY);

                    game.HoldingTrash->texture.texture_info.x = MouseX - game.HoldingTrash->texture.texture_info.w / 2;
                    game.HoldingTrash->texture.texture_info.y = MouseY - game.HoldingTrash->texture.texture_info.h / 2;

                    SDL_RenderCopy(game.renderer, game.HoldingTrash->texture.texture, 
                    NULL, &game.HoldingTrash->texture.texture_info); 
                }
                tmp = tmp->next;
            }

            DrawUI(&game);

            int speed = (25 - game.score / 2);

            SDL_Delay(speed < 5 ? 5 : speed);

            SDL_RenderPresent(game.renderer);

            /*if (game.game_over)
            {
                for (int i = 0; i < 6; ++i)
                {
                    SDL_DestroyTexture(game.trash_buckets[i].texture.texture);
                }
                    SDL_DestroyTexture(game.trash->new_elem->data);
                    //SDL_DestroyTexture(tmp->game->trash->next);
                
                SDL_Delay(1000);
                game.game_over_pic = CreateTexture(&game, "resource/images/game_over.png", 0, 0, 1080, 720);
                SDL_RenderCopy(game.renderer, game.game_over_pic.texture, NULL, &game.game_over_pic.texture_info);

                //SDL_RenderPresent(game.renderer);
                //SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 0);
                //SDL_RenderFillRect(game->renderer, &game->background.texture_info);
                //game.isMenu = true;
            }*/

        }
        
    }
    
    SDL_DestroyTexture(game.background.texture);
    SDL_DestroyTexture(game.play_button.texture);
    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);
    SDL_Quit();
    return 0;
}
