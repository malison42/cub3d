#include "cub.h"

int	init_game(t_game *game)
{
	game = malloc(sizeof(t_game *));
	if (!game)
		return (perror("malloc"), EXIT_FAILURE);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, A, B, "GAME");
//	game->image.img = mlx_new_image(game->mlx, A, B);
//	game->image = malloc(sizeof(t_image));
//	game->image->img = mlx_new_image(game->mlx, A, B);
//	ft_putendl_fd("qwqw4", STDOUT_FILENO);
//	game->image->addr
//			= mlx_get_data_addr(game->image->img, &(game->image->bpp),
//								&(game->image->line_size), &(game->image->endian));
//	game->texture = malloc(sizeof(t_textures));
//	if (!game->texture)
//		return (perror("malloc"), EXIT_FAILURE);
	return (0);
}
//
//void	start_game()
//{
//	model->mlx = mlx_init();
//	model->win = mlx_new_window(model->mlx, A, B, model->name);
//	model->image.img = mlx_new_image(model->mlx, A, B);
//	model->image.addr
//			= mlx_get_data_addr(model->image.img, &(model->image.bpp),
//								&(model->image.line_size), &(model->image.endian));
//	dst = im->addr
//		  + (((int)c.y) * (im->line_size) + ((int)c.x) * (im->bpp / 8));
//	c.color[0] = fraction_color(a, b, fract(a.y, b.y, c.y), col);
//	*(unsigned int *) dst = create_color(c.color[0]);
//	mlx_put_image_to_window(model->mlx, model->win, model->image.img, 0, 0);
//}

void	print_map(t_game *game)
{
	int	x;
	int	y;
	char *pxl;
	
	printf("$\n\n");
	x = 0;
	while (x < 10)
	{
		y = 0;
		while (y < 10)
		{

//			printf("%c ", (game->map)[y][x]);
//			if (game->map[y][x] == '1')
			pxl = game->image.addr + (x * game->image.line_size + y * (game->image.bpp / 8));
			printf("%d %d\n", x, y);
			*(unsigned int *)pxl = (0 << 24 | 255 << 16 | 255 << 8 | 255);
			++y;
		}
		printf("$\n");
		++x;
	}
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_image	img;
	
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
	
	ft_putendl_fd("qwqw", STDOUT_FILENO);
	init_game(&game);
	ft_putendl_fd("asas", STDOUT_FILENO);
	parse_data(argv[1], &game);
	ft_putendl_fd("zxzx", STDOUT_FILENO);
	
//	t_model	model;
//	start_model(&model, argv[1]);
//	start_image(&model);

//	mlx_put_image_to_window(game.mlx, game.win, game.image->img, 0, 0);
//	mlx_do_key_autorepeaton(game.mlx);

//	mlx_key_hook(win, key_hook, &model);
//	mlx_hook(model.win, 17, 0, close_win, &model);
//	mlx_hook(model.win, 4, 0, mouse_hook, &model);

//	t_image img;


	img.img = mlx_new_image(game.mlx, A, B);
	ft_putendl_fd("lklk", STDOUT_FILENO);
	img.addr = mlx_get_data_addr(img.img, &(img.bpp), &(img.line_size), &(img.endian));
//	game.image.addr
//			= mlx_get_data_addr(game.image.img, &(game.image.bpp),
//								&(game.image.line_size), &(game.image.endian));
//	game.image = img;
//	print_map(&game);
	int x, y;
	x = 0;
	y = 0;
	char	*dst;
	while (y < 100)
	{
		while (x < 100)
		{
			printf("%d %d\n", x, y);
			dst = img.addr + (y * img.line_size) + (x * (img.bpp / 8));
			*(unsigned int *) dst = create_color(new_color(255, 255, 255));
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(game.mlx, game.win, game.image.img, 0, 0);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
