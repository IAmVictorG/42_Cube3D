#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "includes/get_next_line/get_next_line.h"
#include "includes/libft/libft.h"
#include "includes/mlx/mlx.h"
#include <fcntl.h>
# include <pthread.h>

#define WIDTH 500
#define HEIGHT 300

#define FOV 60
#define MAX_DISTANCE 20 // BLOCK_LENGTH

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

#define ROTATION_SPEED M_PI / 30


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
	t_coord	coord_ini;
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
	int		size_wall;
} t_map;

typedef struct s_scene 
{
	int			mini_map;
	t_vec		sky_color;
	t_vec		floor_color;
	t_map		map;
	t_sprite	sprite;
	t_player	player;
	
} t_scene;

typedef struct s_keys {
    int w;
    int a;
    int s;
    int d;

    int q;
	int r;
	int	arrow_r;
	int	arrow_l;
} t_keys;

typedef struct general
{
	t_scene *scene;
	t_mlib	*mlib;
	t_keys	*keys;
} t_general;


/* display.c */
void    printVec(t_vec vector);
void    printCoord(t_coord coord);
void    print_player(t_player player);
void    print_scene(t_scene *scene);


/* copy_files_utils */
int		get_size_file(const char *filename);
char	**copy_file(const char *filename, int size_file);


t_vec	draw_rays(t_general *general, int x0, int y0, int x1, int y1, int size_wall, int window_width, int window_height);
void	render_wall2D(t_general *general);


void    printVec(t_vec vector);
void    print_scene(t_scene *scene);
t_coord	get_player_coord(char **matrix);
void    print_player(t_player player);


/* init_window.c*/
void	init_window(t_mlib *mlib, t_scene *scene);
int		position_is_valid(t_general *general, float pos_x, float pos_y);

void	launch_mid_ray(t_general *general);


/* hook.c */

int mouse_press(int button, int x, int y, t_mlib *mlib);
int key_release(int keycode, t_general *general);
int key_pression(int keycode, t_general *general);
int close_window(t_mlib *mlib);
//int key_press(int keycode, t_general *general);
int		key_press_exit(int keycode, t_general *general);

/* utils.c*/
void	my_mlx_pixel_put(t_data *img, int x, int y, int color);
int	create_trgb(int t, int r, int g, int b);
t_vec vec_normalize(t_vec v);


/* render.c*/
int render(t_general *general);
void launch_mid_ray(t_general *general);
int hit_a_wall(t_general *general, int x, int y);
int hit_corner(t_general *general, int x, int y);



/* mini_map.c */

/* ray_caster.c*/
//int		render(t_general *general);
int 	render_game(t_general *general);
int 	render_mini_map(t_general *general);
void 	move(t_general *general);

/* parse_utils.c */
int		is_space(char c);
int		size_tab(char **tab);
void	print_tab(char **tab);
int		string_is_only_space(char *str);
void	ft_free_tabs(char **tab);




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
int		get_size_wall (int map_w, int map_h);
int		map_parser(t_scene *scene, char **copy, int end_parse_1);



t_vec	get_player_orientation(char **matrix, t_coord coord_ini);
t_vec	get_player_position(t_coord coord_ini, int size_wall);


 t_vec	create_ray(t_scene *scene, int pixel_x, int pixel_y);

#endif