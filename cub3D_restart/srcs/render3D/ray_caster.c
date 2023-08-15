#include "render3D.h"

float get_dist(t_coord pos, t_coord ray, float delta_angle)
{
	float	dist;

	dist = sqrtf((ray.x - pos.x)*(ray.x - pos.x) + (ray.y - pos.y)*(ray.y - pos.y));
	dist /= SIZE_WALL;
	dist *= cos(delta_angle);
	return (dist);
}

void	display_sky(t_mlib *mlib, int wall_height, int imageincre, unsigned int sky_color)
{
	int i;

	i = 0;
	while (i < (HEIGHT - wall_height) / 2)
	{
		if (imageincre < WIDTH && i < HEIGHT) 
		{
			my_mlx_pixel_put(&mlib->data, imageincre, i, sky_color);
		}
		i++;
	}
}

void    display_floor(t_mlib *mlib, int wall_height, int imageincre, unsigned int floor_color)
{
	int i;


	i = (HEIGHT + wall_height) / 2;
	while (i < HEIGHT)
	{
		if (imageincre < WIDTH && i < HEIGHT) 
		{
			my_mlx_pixel_put(&mlib->data, imageincre, i, floor_color);
		}
		i++;
	}
	
}

int	pix_in_S (t_coord ray)
{
	return ray.y % SIZE_WALL == 0;
}

int	pix_in_N (t_coord ray)
{
	return ray.y % SIZE_WALL == SIZE_WALL - 1;
}

int	pix_in_E (t_coord ray)
{
	return ray.x % SIZE_WALL == 0;
}

int	pix_in_W (t_coord ray)
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


int	text_in_N (t_coord ray, t_coord ray_bef)
{
	if (pix_in_N(ray) == 1 && pix_in_E(ray) == 1)
		return (pix_in_n_e(ray, ray_bef));
	if (pix_in_N(ray) == 1 && pix_in_W(ray) == 1)
		return (pix_in_n_w(ray, ray_bef));
	return (pix_in_N(ray));
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

int text_in_S (t_coord ray, t_coord ray_bef)
{

	if (pix_in_S(ray) == 1 && pix_in_E(ray) == 1)
		return (pix_in_s_e(ray, ray_bef));

	if (pix_in_S(ray) == 1 && pix_in_W(ray) == 1)
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

void trace_ray(t_general *general) 
{
	t_coord position;
	t_vec   direction;
	t_coord ray;
	t_coord ray_bef;
	float dist;
	int imageincre;
	float player_angle;
	float	fov_start;
	float	fov_end;
	double	angle;


	position = general->scene->player.pos;
	direction = general->scene->player.dir;
	dist = 0;
	imageincre = 0;
	player_angle = atan2f(direction.y, direction.x);


	fov_start = get_fov_start(general);
	fov_end = get_fov_end(general);


	for (int i = 0; i < WIDTH; i++)
	{
		angle = fov_start + (fov_end - fov_start) * i / WIDTH;
		double cos_angle = cos(angle);
		double sin_angle = sin(angle);
		t_vec end_point = {position.x + cos_angle * 200000, position.y + sin_angle * 200000, 0.0f}; // ?
		
		t_tab result = find_point_on_screen(general, position, (t_coord){round(end_point.x), round(end_point.y), 0});


		ray = result.v2;
		ray_bef = result.v1;
		int wall_height;



		dist = get_dist(position, result.v2, angle - player_angle);

 
		wall_height = round((float)(WIDTH) / (float)dist);

		display_sky(general->mlib, wall_height, imageincre, general->scene->sky_color);
		display_floor(general->mlib, wall_height, imageincre, general->scene->floor_color);


		if (text_in_S(ray, ray_bef))
		{
			draw_3d_line_south(general,  result.v2, wall_height, imageincre);
		}
		else if (text_in_N (ray, ray_bef))
		{
			draw_3d_line_north(general,  result.v2, wall_height, imageincre);
		}
		else if (pix_in_E(ray))
		{
			draw_3d_line_east(general, result.v2, wall_height, imageincre);
		}
		else if (pix_in_W(ray))
		{
			draw_3d_line_west(general, result.v2, wall_height, imageincre);
		}
		imageincre++;
	}
}

int render_game(t_general *general)
{
	t_mlib  *mlib = general->mlib;


	mlib->data.img_ptr = mlx_new_image(mlib->utils.mlx, WIDTH, HEIGHT);
	mlib->data.addr = mlx_get_data_addr(mlib->data.img_ptr, &mlib->data.bits_per_pixel, &mlib->data.line_length, &mlib->data.endian);


	move(general);
	trace_ray(general);

	mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, mlib->data.img_ptr, 0, 0);
	mlx_destroy_image(mlib->utils.mlx, mlib->data.img_ptr);
	return (0);
}

