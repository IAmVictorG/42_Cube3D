/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:05:39 by vgiordan          #+#    #+#             */
/*   Updated: 2023/07/26 12:05:01 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	draw_pix_or_stop(t_general *general, t_coord c0, int c)
{
	if (c0.x >= 0 && c0.x < WIDTH && c0.y >= 0 && c0.y < HEIGHT)
	{
		if (hit_a_wall(general, c0.x, c0.y) == 0)
			my_mlx_pixel_put(&general->mlib->data, c0.x, c0.y, c);
		else
			return (0);
	}
	else
		return (0);
	return (1);
}

static void	init_var(int *dx, int *dy, t_coord c0, t_coord c1)
{
	*dx = c1.x - c0.x;
	*dy = c1.y - c0.x;
}

static void	draw1(t_general *general, t_coord c0, t_coord c1, int c)
{
	int		dx;
	int		dy;
	float	err;

	err = 0.5;
	init_var(&dx, &dy, c0, c1);
	while (42)
	{
		if (draw_pix_or_stop(general, c0, c) == 0)
			return ;
		if (err > 1.001f)
		{
			if (dy > 0)
				c0.y++;
			else
				c0.y--;
			err -= 1.0f;
			if (draw_pix_or_stop(general, c0, c) == 0)
				return ;
		}
		err += fabs((float) dy / (float)dx);
		if (dx > 0)
			c0.x++;
		else
			c0.x--;
	}
}

static void	draw2(t_general *general, t_coord c0, t_coord c1, int c)
{
	int		dx;
	int		dy;
	float	err;

	err = 0.5f;
	init_var(&dx, &dy, c0, c1);
	while (42)
	{
		if (draw_pix_or_stop(general, c0, c) == 0)
			return ;
		if (err > 1.001f)
		{
			if (dx > 0)
				c0.x++;
			else
				c0.x--;
			err -= 1.0f;
			if (draw_pix_or_stop(general, c0, c) == 0)
				return ;
		}
		err += fabs((float) dx / (float) dy);
		if (dy > 0)
			c0.y++;
		else
			c0.y--;
	}
}

void	draw_ray2(t_general *general, t_coord c0, t_coord c1, int color)
{
	int		dx;
	int		dy;

	dx = c1.x - c0.x;
	dy = c1.y - c0.x;
	if (abs(dx) >= abs(dy))
	{
		draw1(general, c0, c1, color);
	}
	else
	{
		draw2(general, c0, c1, color);
	}
}
