#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "includes/get_next_line/get_next_line.h"
#include "includes/libft/libft.h"
#include "includes/mlx_opengl/mlx.h"
#include <fcntl.h>

#define WIDTH 300
#define HEIGHT 300
#define FOV 60
#define MAX_DISTANCE 20 // BLOCK_LENGTH


typedef struct	s_utils 
{
	void	*mlx;
	void	*win;
} t_utils;

typedef struct	s_data 
{
	void	*img_ptr;
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

typedef struct s_coord 
{
	int	x;
	int	y;
} t_coord;

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
	char	**matrix;
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

typedef struct general
{
	t_scene *scene;
	t_mlib	*mlib;
} t_general;


void    print_scene(t_scene *scene);


/* init_window.c*/
void init_window(t_mlib *mlib, t_scene *scene);

/* utils.c*/
void	my_mlx_pixel_put(t_data *img, int x, int y, int color);
int	create_trgb(int t, int r, int g, int b);
t_vec vec_normalize(t_vec v);

/* ray_caster.c*/
//int		render(t_general *general);
int		render(t_mlib *mlib, t_scene *scene);

/* parse_utils.c */
int		is_space(char c);
int		size_tab(char **tab);
void	print_tab(char **tab);
int		string_is_only_space(char *str);


/* parsing.c */
int parser(t_scene *scene, char **copy);

/* map_parser.c */
char	*line_matrix_creator(char *line, int w_matrix);
int		check_first_one(char *line);
int		check_last_one(char *line);
int		check_last_first_one(char **map);
int		find_largest_line(char **map);
int		find_map(char **copy_file, int end_part_1);
int		parse_first_wall(char *line);
int		parse_map(char **map);
int		height_map(char **copy_file, int ind_map);
char	**map_creator(char **copy_file, int h_map, int ind_map);
void	display_map(t_scene *scene);
int		check_caract_line(char *line);
int		check_caract_map(char **map_unc);
char	**matrix_creator(char **map_unc, int h_matrix, int w_matrix);
int		wall_inspector(char **matrix, int h_matrix, int w_matrix);
int		check_player(char **matrix);
int		check_EOF(char **copy_file, int ind_map, int h_map);


#endif