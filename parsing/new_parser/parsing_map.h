#ifndef PARSING_MAP_H
# define PARSING_MAP_H

#define VALID_CHARS "01NSEW #"

#include "../../cub.h"



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
int	parse_game_file(t_game *game, int fd);

int	uniqueness_verification(t_config_flags flags_mask, char *specificer);
int	set_flags(char *specificer, t_config_flags *flags_mask);
int	is_rgb_coloor(char	*specificer);
int	is_path_texture(char *specificer);
char	**get_token_config(int fd);
int	fill_rgb_color(char *specificer, t_parsing_var *game_var, char *rgb_collors);
int	fill_path_texture(t_parsing_var *game_var, char	*specificer, char *path_texture);
int	is_valid_sym(t_game *game, char **map, char *set);
int	validate_token_config(char **token_config, char **config_specificers);
int parsing_configs(int fd, t_parsing_var *game_var);
char	**get_normalized_map(t_game *game, t_list *map_list);
t_list	*read_map_to_list(int fd, int *map_x);
int validate_player_start(t_game *game, char **map);
char	**parse_map(int fd, t_game *game);
char	*get_line(int fd);
int 	is_empty_line(char *line);
void	resize_map_y(t_game *game, char **map);
#endif
