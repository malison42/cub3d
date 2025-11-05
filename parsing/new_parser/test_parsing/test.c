#include "parsing_map.h"

int main(int argc, char *argv[])
{
    t_game  *game;

    game = calloc(sizeof(t_game), 1);
    game->texture = malloc(sizeof(t_textures));
	if (!game->texture)
		return (perror("malloc"), 1);
    for (size_t i = 0; i < 4; i++)
    {
        printf("p_text %p\n", game->texture);
        printf("%zu\n", i);
        game->texture->fd_texture[i] = -1;
    }
    
    if (!parse_game_file(game, argv, argc))
        return -1;
    free(game);
    return 0;
}