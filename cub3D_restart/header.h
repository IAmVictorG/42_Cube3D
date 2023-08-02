#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <pthread.h>

#include "includes/get_next_line/get_next_line.h"
#include "includes/libft/libft.h"
#include "includes/mlx/mlx.h"

#define WIDTH 1600
#define HEIGHT 960

#define FOV 60
#define SIZE_WALL 64

#define MLX_SYNC_IMAGE_WRITABLE		1
#define MLX_SYNC_WIN_FLUSH_CMD		2
#define MLX_SYNC_WIN_CMD_COMPLETED	3

#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_Q 12
#define KEY_W 13
#define KEY_R 15
#define KEY_M 46
#define KEY_ESC 53
#define	KEY_ARR_R 124
#define	KEY_ARR_L 123

#define SKY_COLOR 0x2211FF
#define FLOOR_COLOR 0x556B2F

#define ROTATION_SPEED M_PI / 60
#define	SPEED 5

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

typedef struct	s_tab_of_vec
{
	t_vec v1;
	t_vec v2;
	t_vec v3;
} t_tab;

typedef struct s_coord 
{
	int	x;
	int	y;
	int	z;
} t_coord;

typedef struct s_player 
{
	t_coord	coord_ini;
	t_coord	pos;
	t_coord pos2D;


	t_vec	dir;
	float	speed;
} t_player;

typedef struct s_map
{
	char	**matrix;
	int		height_matrix;
	int		width_matrix;
	int		height_map;
	int		width_map;
	int		size_wall;
} t_map;

typedef struct s_scene 
{
	int			mini_map;
	int			sky_color;
	int			floor_color;
	t_map		map;
	t_player	player;
	
} t_scene;

typedef struct s_keys 
{
    int w;
    int a;
    int s;
    int d;

    int q;
	int r;
	int	arrow_r;
	int	arrow_l;
} t_keys;

typedef struct s_sprite 
{
	char	*path;
	t_data	data_spr;

	int sprite_w;
	int sprite_h;
} t_sprite;

typedef struct s_sprites
{
	t_sprite *wall_north;
	t_sprite *wall_south;
	t_sprite *wall_east;
	t_sprite *wall_west;
} t_sprites;

typedef struct s_general
{
	t_scene		*scene;
	t_mlib		*mlib;
	t_keys		*keys;
	t_sprites	*sprites;

} t_general;

int		convert_coord_for_2D_X(int x, int width_map);
int		convert_coord_for_2D_Y(int y, int heigth_map);
t_coord	convert_coord_for_2D(t_coord pos, int width_map, int heigth_map);

void move(t_general *general);

void	init_window(t_general *general, t_mlib *mlib);

void    printVec(t_vec vector);
void    printCoord(t_coord coord);

/* hook.c */
int		key_pression(int keycode, t_general *general);
int		key_release(int keycode, t_general *general);

int		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		hit_a_wall(t_general *general, int x, int y);

int		load_texture_png(t_general *general);

int 	render_game(t_general *general);
#endif