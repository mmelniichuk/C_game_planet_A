#include "header.h"

void trash_bucket_creating(t_game *game)
{
    game->trash_buckets_paths[0] = "resource/images/trash glass.png";
    game->trash_buckets_paths[1] = "resource/images/trash metal.png";
    game->trash_buckets_paths[2] = "resource/images/trash organic.png";
    game->trash_buckets_paths[3] = "resource/images/trash paper.png";
    game->trash_buckets_paths[4] = "resource/images/basket_plastic.png";
    game->trash_buckets_paths[5] = "resource/images/trash e-waste.png";

    for (int trash_bucket_index = 0; trash_bucket_index < 6; ++trash_bucket_index)
    {
        game->trash_buckets[trash_bucket_index].trash_type = trash_bucket_index;
        game->trash_buckets[trash_bucket_index].texture =
            CreateTexture(game, game->trash_buckets_paths[trash_bucket_index],
            10 + 180 * trash_bucket_index, SCREEN_HEIGHT - 240, 160, 240);
    }
}
