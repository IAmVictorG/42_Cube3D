#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "includes/get_next_line/get_next_line.h"
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
	char const *est;
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
	int			sky_color;
	int			floor_color;

	t_map		map;
	t_sprite	sprite;
	t_player	player;
	
} t_scene;

int		parse_map(char **map);
int		height_map(int fd);
char	**map_creator(char *file_name);
void	display_map(char **map);

#endif