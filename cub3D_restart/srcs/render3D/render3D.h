#ifndef RENDER3D
# define RENDER3D

#include "../../header.h"

#define FOV_RAD (M_PI / 3)

/* render3D/ray_caster.c */
t_vec	calculate_rays(t_general *general, int x0, int y0, int x1, int y1, int size_wall, int window_width, int window_height);
t_tab   find_point_on_screen(t_general *general, t_coord c0, float angle);

void	trace_ray(t_general *general);
int 	render_game(t_general *general);

/* render3D/3D_wall_render.c */
void	draw_3d_line_north(t_general *general, t_coord ray, int wall_height, int imageincre);
void	draw_3d_line_south(t_general *general, t_coord ray, int wall_height, int imageincre);
void	draw_3d_line_east(t_general *general, t_coord ray, int wall_height, int imageincre);

void	draw_3d_line_west(t_general *general, t_coord ray, int wall_height, int imageincre);
void 	draw_3d_line_color(t_general *general, t_vec ray, int wall_height, int imageincre, unsigned int color);

/* render3D/get_color.c */
int		get_color_wall_north(t_general *general, int x, int h_wall, int max_wall_h);
int		get_color_wall_south(t_general *general, int x, int h_wall, int max_wall_h);
int		get_color_wall_east(t_general *general, int x, int h_wall, int max_wall_h);
int		get_color_wall_west(t_general *general, int x, int h_wall, int max_wall_h);

/* utils.c */
void	init_var(int *dx, int *dy, t_coord c0, t_coord c1);
void	set_var(t_coord *v1, t_coord *v2, t_coord c0);
int     should_stop(t_general *general, t_coord c0);

#endif