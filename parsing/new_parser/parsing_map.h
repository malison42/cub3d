#ifndef PARSING_MAP_H
# define PARSING_MAP_H

#define VALID_CHARS "01NSEW "

#include "../../cub.h"

typedef	enum e_sunny_side
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	ERROR,
} t_sunny_side;

typedef enum e_config_flags
{
    FLAG_NO = 1 << 0,
    FLAG_SO = 1 << 1,
    FLAG_WE = 1 << 2,
	FLAG_EA = 1 << 3,
    FLAG_F  = 1 << 4, // 16
    FLAG_C  = 1 << 5, // 32
} t_config_flags;


typedef struct s_filename_texture
{
	t_sunny_side side;
	//char	*side;
	char	*path_texture;
	//int		is_find;
} t_filename_texture;

typedef struct s_parsing_var
{
	t_config_flags		flags_mask;
	t_filename_texture	texturs[4];
	t_color				ceiling;
	t_color				floor;
	t_player			start;
	// int		is_find_floor;
	// int		is_find_ceiling;
	char				**map;
}	t_parsing_var;

char	**get_specificers(int mode);
int parsing_configs(int fd, t_parsing_var *game_var);
void free_map_array(char **map, int rows_to_free);
int	is_mape_closure(t_game *game, char **map);
void	free_tokens(char **tokens);
int	parse_game_file(t_game *game, char *argv, int argc);

int	uniqueness_verification(t_config_flags flags_mask, char *specificer);
int	set_flags(char *specificer, int *flags_mask);
#endif
