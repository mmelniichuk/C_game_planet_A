#include "header.h"

static t_trash_texture    *get_random_trash(t_game *game)
{
    t_trash_texture *new_trash = (t_trash_texture *)malloc(sizeof(t_trash_texture));

    int random_index = rand() % 17;

    new_trash->texture = CreateTexture(game, game->trash_texture_path[random_index],
            100 + rand() % (SCREEN_WIDTH - 200), 40, 20, 20);

    if (random_index < 2)
        new_trash->trash_type = 0;
    else if (random_index < 5)
        new_trash->trash_type = 1;
    else if (random_index < 10)
        new_trash->trash_type = 2;
    else if (random_index < 14)
        new_trash->trash_type = 3;
    else if (random_index < 15)
        new_trash->trash_type = 4;
    else
        new_trash->trash_type = 5;

    return new_trash;
}

static void add_trash(t_game *game)
{
    push_back(&game->trash, get_random_trash(game));
}  

void update_trash_list(t_game *game)
{
    int amount = game->max_trash_amount - list_size(&game->trash);

    while (amount--)
    {
        add_trash(game);
    }
}
        

void set_trash_pathes(t_game *game)
{
    game->trash_texture_path[0] = "resource/images/trash/glass/1.png";
    game->trash_texture_path[1] = "resource/images/trash/glass/2.png";
    game->trash_texture_path[2] = "resource/images/trash/metal/1.png";
    game->trash_texture_path[3] = "resource/images/trash/metal/2.png";
    game->trash_texture_path[4] = "resource/images/trash/metal/3.png";
    game->trash_texture_path[5] = "resource/images/trash/organic/1.png";
    game->trash_texture_path[6] = "resource/images/trash/organic/2.png";
    game->trash_texture_path[7] = "resource/images/trash/organic/3.png";
    game->trash_texture_path[8] = "resource/images/trash/organic/4.png";
    game->trash_texture_path[9] = "resource/images/trash/organic/5.png";
    game->trash_texture_path[10] = "resource/images/trash/paper/1.png";
    game->trash_texture_path[11] = "resource/images/trash/paper/2.png";
    game->trash_texture_path[12] = "resource/images/trash/paper/3.png";
    game->trash_texture_path[13] = "resource/images/trash/paper/4.png";
    game->trash_texture_path[14] = "resource/images/trash/plastic/1.png";
    game->trash_texture_path[15] = "resource/images/trash/e_waste/1.png";
    game->trash_texture_path[16] = "resource/images/trash/e_waste/2.png";
    game->trash_texture_path[17] = "resource/images/trash/e_waste/3.png";
}

