#include "cub.h"


void	draw_image(t_game *game)
{
	if (game->image.img)
		mlx_destroy_image(game->mlx, game->image.img);
	game->image.img = mlx_new_image(game->mlx, A, B);
	game->image.addr = mlx_get_data_addr(game->image.img,
										 &game->image.bpp,
										 &game->image.line_size,
										 &game->image.endian);
	if (game->map2D.image.img)
		mlx_destroy_image(game->mlx, game->map2D.image.img);
	game->map2D.image.img = mlx_new_image(game->mlx, C, D);
	game->map2D.image.addr = mlx_get_data_addr(game->map2D.image.img,
										 &game->map2D.image.bpp,
										 &game->map2D.image.line_size,
										 &game->map2D.image.endian);
	draw_game(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image.img, 0, 0);
	if (game->minimap_on)
	{
		draw_minimap(game);
		mlx_put_image_to_window(game->mlx, game->win, game->map2D.image.img, \
								A - C, B - D);
	}
}

int	main(int argc, char **argv)
{
	// if (argc != 2)
	// {
	// 	ft_putstr_fd("Error\nEnter map filename", STDERR_FILENO);
	// 	return (EXIT_FAILURE);
	// }
	// if (ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub"))
	// {
	// 	ft_putstr_fd("Error\n"
	// 				 "File has to be with the .cub extension", STDERR_FILENO);
	// 	return (EXIT_FAILURE);
	// }

	t_game game;
	// game = malloc(sizeof(t_game));
	// if (!game)
	// 	return (EXIT_FAILURE);
	// ft_bzero(game, sizeof(t_game));
	init_game(&game);
	game.texture = malloc(sizeof(t_textures));
	if (!game.texture)
	{
		// free(game);
		return (EXIT_FAILURE);
	}
	printf("shcjkzxlhc\n");
	if (!parse_game_file(&game, argv, argc))
	{
		 free_game(&game);

		return (EXIT_FAILURE);
	}

	// t_game game;
	// parse_data(argv[1], &game);
	init_minimap(&game);
	printf("%f %f\n", game.player.x, game.player.y);

	// need to check initialization success
	draw_image(&game);
	
	mlx_put_image_to_window(game.mlx, game.win, game.image.img, 0, 0);
	mlx_do_key_autorepeaton(game.mlx);
//	mlx_key_hook(game.win, key_hook, &game);
	mlx_hook(game.win, 2, (1L << 0), key_hook, &game);
	mlx_hook(game.win, 17, 0, close_win, &game);
//	mlx_hook(model.win, 4, 0, mouse_hook, &model);
	mlx_loop(game.mlx);
}
