#include "render.h"

void    ne(t_general *general, t_tab tab, int imageincre, int dist)
{
	t_vec ray_bef;
	t_vec ray;

	ray_bef.x = tab.v1.x;
	ray_bef.y = tab.v1.y;
	if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y + 1)
		draw_3D_line_north(general,ray, imageincre, dist);
	else if (ray_bef.x == ray.x && ray_bef.y == ray.y + 1)
		draw_3D_line_north(general,ray, imageincre, dist);
	else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y + 1)
		draw_3D_line_east(general,ray, imageincre, dist);
	else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y)
		draw_3D_line_east(general,ray, imageincre, dist);
	else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y - 1)
		draw_3D_line_east(general,ray, imageincre, dist);
}

void    nw(t_general *general, t_tab tab, int imageincre, int dist)
{
	t_vec ray_bef;
	t_vec ray;

	ray_bef.x = tab.v1.x;
	ray_bef.y = tab.v1.y;
	if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y - 1)
		draw_3D_line_west(general,ray, imageincre, dist);
	else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y)
		draw_3D_line_west(general,ray, imageincre, dist);
	else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y + 1)
		draw_3D_line_north(general,ray, imageincre, dist);
	else if (ray_bef.x == ray.x && ray_bef.y == ray.y + 1)
		draw_3D_line_north(general,ray, imageincre, dist);
	else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y + 1)
		draw_3D_line_north(general,ray, imageincre, dist);
}

void se(t_general *general, t_tab tab, int imageincre, int dist)
{
	t_vec ray_bef;
	t_vec ray;

	ray_bef.x = tab.v1.x;
	ray_bef.y = tab.v1.y;
	if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y + 1)
		draw_3D_line_east(general,ray, imageincre, dist);
	else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y)
		draw_3D_line_east(general,ray, imageincre, dist);
	else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y - 1)
		draw_3D_line_south(general,ray, imageincre, dist);
	else if (ray_bef.x == ray.x && ray_bef.y == ray.y - 1)
		draw_3D_line_south(general,ray, imageincre, dist);
	else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y - 1)
		draw_3D_line_south(general,ray, imageincre, dist);
}

void sw(t_general *general, t_tab tab, int imageincre, int dist)
{
	t_vec ray_bef;
	t_vec ray;

	ray_bef.x = tab.v1.x;
	ray_bef.y = tab.v1.y;
	if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y - 1)
		draw_3D_line_south(general,ray, imageincre, dist);
	else if (ray_bef.x == ray.x && ray_bef.y == ray.y - 1)
		draw_3D_line_south(general,ray, imageincre, dist);
	else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y - 1)
		draw_3D_line_south(general,ray, imageincre, dist);
	else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y)
		draw_3D_line_west(general,ray, imageincre, dist);
	else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y + 1)
		draw_3D_line_west(general,ray, imageincre, dist);
}