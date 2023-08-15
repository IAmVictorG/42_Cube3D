#include "../../header.h"

void	draw_grid(t_general *general)
{
	t_mlib	*mlib;
	int		i;
	int		j;

	mlib = general->mlib;
	i = 0;
	while (i < general->scene->map.width_matrix * SCALE_MINI_MAP)
	{
		j = 0;
		while (j < general->scene->map.height_matrix * SCALE_MINI_MAP)
		{
			if (i % SCALE_MINI_MAP == 0)
			{
				my_mlx_pixel_put(&mlib->data, i, j, 0x00AA00);
			}
			if (j % SCALE_MINI_MAP == 0)
			{
				my_mlx_pixel_put(&mlib->data, i, j, 0x00AA00);
			}
			j++;
		}
		i++;
	}
}

void	draw_wall(t_general *general, t_coord coord_wall)
{
	int		x;
	int		y;
	t_mlib	*mlib;

	mlib = general->mlib;
	y = 0;
	while (y < SCALE_MINI_MAP)
	{
		x = 0;
		while (x < SCALE_MINI_MAP)
		{
			my_mlx_pixel_put(&mlib->data, coord_wall.x * SCALE_MINI_MAP + x,
				coord_wall.y * SCALE_MINI_MAP + y,
				0x1100FF);
			x++;
		}
		y++;
	}
}

void	render_wall2d(t_general *general)
{
	t_coord	coord_wall;
	int		i;
	int		j;

	j = 0;
	while (j < general->scene->map.height_matrix)
	{
		i = 0;
		while (i < general->scene->map.width_matrix)
		{
			if (general->scene->map.matrix[j][i] == '1')
			{
				coord_wall.x = i;
				coord_wall.y = j;
				draw_wall(general, coord_wall);
			}
			i++;
		}
		j++;
	}
}

void	draw_player(t_general *general)
{
	t_mlib	*mlib;
	int		size;
	int		x;
	int		y;
	int		i;

	mlib = general->mlib;
	x = general->scene->player.pos2D.x;
	y = general->scene->player.pos2D.y;
	size = 3;
	i = -size;
	while (i <= size)
	{
		my_mlx_pixel_put(&mlib->data, x + i, y, 0x00FF00);
		my_mlx_pixel_put(&mlib->data, x, y + i, 0x00FF00);
		i++;
	}
}

void	draw_arrow(t_general *general, t_coord start_arrow, t_vec dir)
{
	int		color;
	t_coord	end_arrow;

	color = 0xFF0000;
	start_arrow = convertcoord2d(start_arrow);
	end_arrow.x = start_arrow.x + 8 * dir.x;
	end_arrow.y = start_arrow.y + 8 * dir.y;
	my_mlx_pixel_put(&general->mlib->data, end_arrow.x, end_arrow.y, color);
}

int	render_mini_map(t_general *general)
{
	t_mlib	*mlib;

	mlib = general->mlib;
	mlib->data.img_ptr = mlx_new_image(mlib->utils.mlx, WIDTH, HEIGHT);
	mlib->data.addr = mlx_get_data_addr(mlib->data.img_ptr,
			&mlib->data.bits_per_pixel,
			&mlib->data.line_length,
			&mlib->data.endian);
	render_wall2d(general);
	//draw_grid(general);
	move(general);
	draw_player(general);
	draw_arrow(general, general->scene->player.pos, general->scene->player.dir);
	mlx_put_image_to_window(mlib->utils.mlx,
		mlib->utils.win,
		mlib->data.img_ptr, 0, 0);
	mlx_destroy_image(mlib->utils.mlx, mlib->data.img_ptr);
	return (0);
}
