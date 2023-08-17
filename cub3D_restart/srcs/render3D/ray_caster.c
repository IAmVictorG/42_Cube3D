#include "render3D.h"

float	get_dist(t_coord pos, t_coord ray, float delta_angle)
{
	float	dist;

	dist = sqrtf((ray.x - pos.x) * (ray.x - pos.x)
			+ (ray.y - pos.y) * (ray.y - pos.y));
	dist /= SIZE_WALL;
	dist *= cos(delta_angle);
	return (dist);
}

void	display_sky(t_mlib *mlib, int w_h, int imi, unsigned int ceil)
{
	int	i;

	i = 0;
	while (i < (HEIGHT - w_h) / 2)
	{
		if (imi < WIDTH && i < HEIGHT) 
		{
			my_mlx_pixel_put(&mlib->data, imi, i, ceil);
		}
		i++;
	}
}

void    display_floor(t_mlib *mlib, int w_h, int imi, unsigned int floor)
{
	int i;


	i = (HEIGHT + w_h) / 2;
	while (i < HEIGHT)
	{
		if (imi < WIDTH && i < HEIGHT) 
		{
			my_mlx_pixel_put(&mlib->data, imi, i, floor);
		}
		i++;
	}
	
}

int	pix_in_s (t_coord ray)
{
	return ray.y % SIZE_WALL == 0;
}

int	pix_in_n (t_coord ray)
{
	return ray.y % SIZE_WALL == SIZE_WALL - 1;
}

int	pix_in_e (t_coord ray)
{
	return ray.x % SIZE_WALL == 0;
}

int	pix_in_w (t_coord ray)
{
	return ray.x % SIZE_WALL == SIZE_WALL - 1;
}


int	pix_in_n_e(t_coord ray, t_coord ray_bef)
{

	if (ray_bef.x == (int) (ray.x + 1) && ray_bef.y == (int) (ray.y + 1))
	{
		return (1);
	}
	else if (ray_bef.x == (int) ray.x && ray_bef.y == (int) (ray.y + 1))
	{
		return (1);
	}
	else if (ray_bef.x == (int)(ray.x - 1) && ray_bef.y == (int)(ray.y + 1))
	{
		return (0);
	}
	else if (ray_bef.x == (int)(ray.x - 1) && ray_bef.y == (int)(ray.y))
	{
		return (0);
	}
	else if (ray_bef.x == (int)(ray.x - 1) && ray_bef.y == (int)(ray.y - 1))
	{
		return (0);
	}
	return (1);
}

int	pix_in_n_w(t_coord ray, t_coord ray_bef)
{
	if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y - 1)
	{
		return (0);
	}
	else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y)
	{
		return (0);
	}
	else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y + 1)
	{
		return (1);
	}
	else if (ray_bef.x == ray.x && ray_bef.y == ray.y + 1)
	{
		return (1);
	}
	else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y + 1)
	{
		return (1);
	}
	return (0);
}


int	text_in_n (t_coord ray, t_coord ray_bef)
{
	if (pix_in_n(ray) == 1 && pix_in_e(ray) == 1)
		return (pix_in_n_e(ray, ray_bef));
	if (pix_in_n(ray) == 1 && pix_in_w(ray) == 1)
		return (pix_in_n_w(ray, ray_bef));
	return (pix_in_n(ray));
}


int	pix_in_s_e(t_coord ray, t_coord ray_bef)
{
	if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y + 1)
	{
		return (0);
	}
	else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y)
	{
		return (0);
	}
	else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y - 1)
	{
		return (0);
	}
	else if (ray_bef.x == ray.x && ray_bef.y == ray.y - 1)
	{
		return (1);
	}
	else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y - 1)
	{
		return (1);
	}
	return (0);
}

int	pix_in_s_w(t_coord ray, t_coord ray_bef)
{
	if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y - 1)
	{
		return (1);
	}
	else if (ray_bef.x == ray.x && ray_bef.y == ray.y - 1)
	{
		return (1);
	}
	else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y - 1)
	{
		return (1);
	}
	else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y)
	{
		return (0);
	}
	else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y + 1)
	{
		return (0);
	}
	return (1);
}

int text_in_s (t_coord ray, t_coord ray_bef)
{

	if (pix_in_s(ray) == 1 && pix_in_e(ray) == 1)
		return (pix_in_s_e(ray, ray_bef));

	if (pix_in_s(ray) == 1 && pix_in_w(ray) == 1)
	{
		return (pix_in_s_w(ray, ray_bef));
	}


	return ray.y % SIZE_WALL == 0;
}

float    atan2f_to_ortho(t_vec  direction)
{
	float angle_relative;

	angle_relative = atan2f(direction.y, direction.x);

	if (angle_relative < 0)
	{
		return (angle_relative * (-1));
	}

	return (2 * M_PI - angle_relative);

}

float	get_fov_start(t_general *general)
{
	float	player_angle;
	t_vec	direction;

	direction = general->scene->player.dir;
	player_angle = atan2f(direction.y, direction.x);
	return player_angle - ((M_PI / 3) / 2);
}

float	get_fov_end(t_general *general)
{
	float	player_angle;
	t_vec	direction;

	direction = general->scene->player.dir;
	player_angle = atan2f(direction.y, direction.x);
	return player_angle + ((M_PI / 3) / 2);
}

void	color_img(t_general *general, int imi, int w_h, t_tab result)
{

	if (w_h < WIDTH)
	{
		display_sky(general->mlib, w_h, imi, general->scene->sky_color);
		display_floor(general->mlib, w_h, imi, general->scene->floor_color);
	}
	if (text_in_s(result.v2, result.v1))
	{
		draw_3d_line_south(general,  result.v2, w_h, imi);
	}
	else if (text_in_n (result.v2, result.v1))
	{
		draw_3d_line_north(general,  result.v2, w_h, imi);
	}
	else if (pix_in_e(result.v2))
	{
		draw_3d_line_east(general, result.v2, w_h, imi);
	}
	else if (pix_in_w(result.v2))
	{
		draw_3d_line_west(general, result.v2, w_h, imi);
	}

}


void trace_ray(t_general *general) 
{
	int imageincre;
	float	pl_st_end[3];
	double	angle;
	t_tab	result;
	int wall_height;


	imageincre = 0;
	pl_st_end[0] = atan2f(general->scene->player.dir.y,
			general->scene->player.dir.x);
	pl_st_end[1] = get_fov_start(general);
	pl_st_end[2] = get_fov_end(general);
	while (imageincre < WIDTH)
	{
		angle = pl_st_end[1] +
			(pl_st_end[2] - pl_st_end[1]) * imageincre / WIDTH;
		result = find_point_on_screen(general,
				general->scene->player.pos, angle);
		wall_height = round((float)(WIDTH) /
				get_dist(general->scene->player.pos,
					result.v2, angle - pl_st_end[0]));
		color_img(general , imageincre, wall_height, result);
		imageincre++;
	}
}

int render_game(t_general *general)
{
	t_mlib  *mlib = general->mlib;


	mlib->data.img_ptr = mlx_new_image(mlib->utils.mlx, WIDTH, HEIGHT);
	mlib->data.addr = mlx_get_data_addr(mlib->data.img_ptr,
			&mlib->data.bits_per_pixel,
			&mlib->data.line_length,
			&mlib->data.endian);


	move(general);
	trace_ray(general);

	mlx_put_image_to_window(mlib->utils.mlx,
			mlib->utils.win, mlib->data.img_ptr, 0, 0);
	mlx_destroy_image(mlib->utils.mlx, mlib->data.img_ptr);
	return (0);
}

