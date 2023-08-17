/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pixel_screen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 10:39:52 by vgiordan          #+#    #+#             */
/*   Updated: 2023/08/17 11:03:10 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render3D.h"

static t_tab	p_ew(t_general *general, t_coord c0, t_coord c1)
{
	int		dx;
	int		dy;
	float	err;
	t_tab	r;

	err = 0.5;
	init_var(&dx, &dy, c0, c1);
	while (42)
	{
		if (err > 1.001f)
		{
			if (dy > 0)
				c0.y++;
			else
				c0.y--;
			err -= 1.0f;
			set_var(&r.v1, &r.v2, c0);
			if (should_stop(general, c0) == 0)
				break ;
		}
		err += fabs((float) dy / (float)dx);
		if (dx > 0)
			c0.x++;
		else
			c0.x--;
		set_var(&r.v1, &r.v2, c0);
		if (should_stop(general, c0) == 0)
			break ;
	}
	return (r);
}

static t_tab	p_sn(t_general *general, t_coord c0, t_coord c1)
{
	int		dx;
	int		dy;
	float	err;
	t_tab	r;

	err = 0.5f;
	init_var(&dx, &dy, c0, c1);
	while (42)
	{
		if (err > 1.001f)
		{
			if (dx > 0)
				c0.x++;
			else
				c0.x--;
			err -= 1.0f;
			set_var(&r.v1, &r.v2, c0);
			if (should_stop(general, c0) == 0)
				break ;
		}
		err += fabs((float) dx / (float) dy);
		if (dy > 0)
			c0.y++;
		else
			c0.y--;
		set_var(&r.v1, &r.v2, c0);
		if (should_stop(general, c0) == 0)
			break ;
	}
	return (r);
}

t_tab	find_point_on_screen(t_general *general, t_coord c0, float angle)
{
	int		dx;
	int		dy;
	t_coord	c1;

	c1.x = round(c0.x + cos(angle) * 200000);
	c1.y = round(c0.y + sin(angle) * 200000);
	dx = c1.x - c0.x;
	dy = c1.y - c0.x;
	if (abs(dx) >= abs(dy))
	{
		return (p_ew(general, c0, c1));
	}
	else
	{
		return (p_sn(general, c0, c1));
	}
}
