#include "cub.h"

int	open_map_file(int argc, char **argv)
{
	int	fd;

	if (argc < 2)
	{
		ft_putendl_fd("Error\nEnter map filename", STDERR_FILENO);
		return (-1);
	}
	if (argc > 2)
	{
		ft_putendl_fd("Error\nToo many arguments", STDERR_FILENO);
		return (-1);
	}
	if (ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub"))
	{
		ft_putendl_fd("Error", STDERR_FILENO);
		ft_putendl_fd("File has to be with the .cub extension", STDERR_FILENO);
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		perror(argv[1]);
	return (fd);
}

void	draw_image(t_game *game)
{
//	if (game->image.img)
//		mlx_destroy_image(game->mlx, game->image.img);
//	game->image.img = mlx_new_image(game->mlx, A, B);
//	game->image.addr = mlx_get_data_addr(
//			game->image.img,
//			&game->image.bpp,
//			&game->image.line_size,
//			&game->image.endian);
//	if (game->map2D.image.img)
//		mlx_destroy_image(game->mlx, game->map2D.image.img);
//	game->map2D.image.img = mlx_new_image(game->mlx, C, D);
//	game->map2D.image.addr = mlx_get_data_addr(
//			game->map2D.image.img,
//			&game->map2D.image.bpp,
//			&game->map2D.image.line_size,
//			&game->map2D.image.endian);
	
	draw_game(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image.img, 0, 0);
	if (game->minimap_on)
	{
		draw_minimap(game);
		mlx_put_image_to_window(game->mlx, game->win,
			game->map2D.image.img, A - C, B - D);
	}
}

int	main(int argc, char **argv)
{
	int		fd;
	t_game	game;

	fd = open_map_file(argc, argv);
	if (fd < 0)
		return (EXIT_FAILURE);
	if (!init_game(&game))
	{
		free_game(&game);
		return (EXIT_FAILURE);
	}
	printf("shcjkzxlhc\n");
	if (!parse_game_file(&game, fd))
	{
		free_game(&game);
		return (EXIT_FAILURE);
	}
	if (!init_minimap(&game))
	{
		free_game(&game);
		return (EXIT_FAILURE);
	}
//	init_minimap(&game);
	printf("%f %f\n", game.player.x, game.player.y);
	draw_image(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.image.img, 0, 0);
	mlx_do_key_autorepeaton(game.mlx);
	mlx_hook(game.win, 2, (1L << 0), key_hook, &game);
	mlx_hook(game.win, 17, 0, close_win, &game);
	mlx_loop(game.mlx);
}
