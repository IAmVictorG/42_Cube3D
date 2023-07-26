#include "render.h"

static void	display_sky(t_mlib *mlib, int wall_height, int imageincre, unsigned int sky_color)
{
	for (int i = 0; i < (HEIGHT - wall_height) / 2; i++)
	{
		if (imageincre < WIDTH && i < HEIGHT) 
		{
			my_mlx_pixel_put(&mlib->data, imageincre, i, sky_color);
		}
	}
}

static void	display_floor(t_mlib *mlib, int wall_height, int imageincre)
{
	for (int i = (HEIGHT + wall_height) / 2; i < HEIGHT; i++) {
		if (imageincre < WIDTH && i < HEIGHT) 
		{
			my_mlx_pixel_put(&mlib->data, imageincre, i, FLOOR_COLOR);
		}
	}
}

void draw_manager(t_general *general, t_tab tab, int imageincre, float dist)
{

    int size_wall = general->scene->map.size_wall;
	int wall_height;
    t_vec   ray = tab.v2;
    t_vec   ray_bef = tab.v1;

    
    if (dist <= 1.0f)
    {
        if (pix_in_N(ray, size_wall) == 1 && pix_in_E(ray, size_wall) == 1)
            ne_near(general, tab, imageincre, dist);
        else if (pix_in_N(ray, size_wall) == 1 && pix_in_W(ray, size_wall) == 1)
            nw_near(general, tab, imageincre, dist);
        else if (pix_in_S(ray, size_wall) == 1 && pix_in_E(ray, size_wall) == 1)
            se_near(general, tab, imageincre, dist);
        else if (pix_in_S(ray, size_wall) == 1 && pix_in_W(ray, size_wall) == 1)
            sw_near(general, tab, imageincre, dist);
        if (pix_in_S(ray, size_wall) == 1)
            draw_3D_line_south_near(general, ray, imageincre, dist);
        else if ((int) ray.y % size_wall == size_wall - 1)
            draw_3D_line_north_near(general,ray, imageincre, dist);                 
        else if ((int) ray.x % size_wall == 0)
            draw_3D_line_east_near(general,ray, imageincre, dist);
        else if ((int) ray.x % size_wall == size_wall - 1)
            draw_3D_line_west_near(general,ray, imageincre, dist);
    }
    else
    {
        wall_height = HEIGHT / dist;
        display_sky(general->mlib, wall_height, imageincre, SKY_COLOR);
        display_floor(general->mlib, wall_height, imageincre);

        if (pix_in_N(ray, size_wall) == 1 && pix_in_E(ray, size_wall) == 1)
        {
            if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y + 1)
                draw_3D_line_north(general,ray, wall_height, imageincre);
            else if (ray_bef.x == ray.x && ray_bef.y == ray.y + 1)
                draw_3D_line_north(general,ray, wall_height, imageincre);
            else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y + 1)
                draw_3D_line_east(general,ray, wall_height, imageincre);
            else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y)
                draw_3D_line_east(general,ray, wall_height, imageincre);
            else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y - 1)
                draw_3D_line_east(general,ray, wall_height, imageincre);
        }
        else if (pix_in_N(ray, size_wall) == 1 && pix_in_W(ray, size_wall) == 1)
        {
            if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y - 1)
                draw_3D_line_west(general,ray, wall_height, imageincre);
            else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y)
                draw_3D_line_west(general,ray, wall_height, imageincre);
            else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y + 1)
                draw_3D_line_north(general,ray, wall_height, imageincre);
            else if (ray_bef.x == ray.x && ray_bef.y == ray.y + 1)
                draw_3D_line_north(general,ray, wall_height, imageincre);
            else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y + 1)
                draw_3D_line_north(general,ray, wall_height, imageincre);
        }
        else if (pix_in_S(ray, size_wall) == 1 && pix_in_E(ray, size_wall) == 1)
        {
            if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y + 1)
                draw_3D_line_east(general,ray, wall_height, imageincre);
            else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y)
                draw_3D_line_east(general,ray, wall_height, imageincre);
            else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y - 1)
                draw_3D_line_south(general,ray, wall_height, imageincre);
            else if (ray_bef.x == ray.x && ray_bef.y == ray.y - 1)
                draw_3D_line_south(general,ray, wall_height, imageincre);
            else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y - 1)
                draw_3D_line_south(general,ray, wall_height, imageincre);
        }
        else if (pix_in_S(ray, size_wall) == 1 && pix_in_W(ray, size_wall) == 1)
        {
            if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y - 1)
                draw_3D_line_south(general,ray, wall_height, imageincre);
            else if (ray_bef.x == ray.x && ray_bef.y == ray.y - 1)
                draw_3D_line_south(general,ray, wall_height, imageincre);
            else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y - 1)
                draw_3D_line_south(general,ray, wall_height, imageincre);
            else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y)
                draw_3D_line_west(general,ray, wall_height, imageincre);
            else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y + 1)
                draw_3D_line_west(general,ray, wall_height, imageincre);
        }
        else if (pix_in_S(ray, size_wall) == 1)
            draw_3D_line_south(general, ray, wall_height, imageincre);
        else if (pix_in_E(ray, size_wall) == 1)
            draw_3D_line_east(general, ray, wall_height, imageincre);
        else if (pix_in_N(ray, size_wall) == 1)
            draw_3D_line_north(general,ray, wall_height, imageincre);                 
        else if (pix_in_W(ray, size_wall) == 1)
            draw_3D_line_west(general, ray, wall_height, imageincre);
    }
}