#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "includes/get_next_line/get_next_line.h"
#include "includes/libft/libft.h"
#include <fcntl.h>


typedef struct	s_utils 
{
	void	*mlx;
	void	*win;
} t_utils;

typedef struct	s_data 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_data;

typedef struct	s_mlib 
{
	t_data	data;
	t_utils	utils;
} t_mlib;

typedef struct s_vec 
{
	float x;
	float y;
	float z;
} t_vec;

typedef struct s_player 
{
	t_vec	pos;
	t_vec	dir;
	float	speed;
} t_player;

typedef struct s_sprite 
{
	char const *north;
	char const *south;
	char const *east;
	char const *west;

	char const *bonus;
} t_sprite;

typedef struct s_map
{
	char	**map;
	int		height_map;
	int		width_map;
} t_map;

typedef struct s_scene 
{
	t_vec		sky_color;
	t_vec		floor_color;

	t_map		map;
	t_sprite	sprite;
	t_player	player;
	
} t_scene;


/* parse_utils.c */
int		is_space(char c);
int		size_tab(char **tab);

/* parsing.c */
void	parse_line(t_scene *scene, char *line);

/* map_parser.c */
int		check_first_one(char *line);
int		check_last_one(char *line);
int		check_last_first_one(char **map);
int		find_largest_line(char **map);
int		find_map(const char *filename);
int		parse_first_wall(char *line);
int		parse_map(char **map);
int		height_map(const char *filename, int ind_map);
char	**map_creator(const char *filename, int h_map, int ind_map);
void	display_map(t_scene *scene);

#endif