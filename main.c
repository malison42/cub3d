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
	// print_2D_map(game);
	draw_game(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image.img, 0, 0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\nEnter map filename", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub"))
	{
		ft_putstr_fd("Error\n"
					 "File has to be with the .cub extension", STDERR_FILENO);
		return (EXIT_FAILURE);
	}

	t_game game;
	parse_data(argv[1], &game);
	printf("%f %f\n", game.player.x, game.player.y);
	init_game(&game);
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