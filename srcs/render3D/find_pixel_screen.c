/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pixel_screen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:19:20 by vgiordan          #+#    #+#             */
/*   Updated: 2023/07/26 14:34:37 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	should_stop(t_general *general, t_coord c0)
{
	if (c0.x >= 0 && c0.x < WIDTH && c0.y >= 0 && c0.y < HEIGHT)
	{
		if (hit_a_wall(general, c0.x, c0.y) != 0)
			return (0);
	}
	else
		return (0);
	return (1);
}

static void	replace_var(t_tab *r, t_coord c0)
{
	r->v1.x = r->v2.x;
	r->v1.y = r->v2.y;
	r->v1.z = 0;
	r->v2.x = c0.x;
	r->v2.y = c0.y;
	r->v2.z = 0;
}

static t_tab	p1(t_general *general, t_coord c0, t_coord cd, float err)
{
	t_tab	r;

	while (42)
	{
		if (err > 1.001f)
		{
			if (cd.y > 0)
				c0.y++;
			else
				c0.y--;
			err -= 1.0f;
			replace_var(&r, c0);
			if (should_stop(general, c0) == 0)
				break ;
		}
		err += fabs((float) cd.y / (float) cd.x);
		if (cd.x > 0)
			c0.x++;
		else
			c0.x--;
		replace_var(&r, c0);
		if (should_stop(general, c0) == 0)
			break ;
	}
	return (r);
}

static t_tab	p2(t_general *general, t_coord c0, t_coord cd, float err)
{
	t_tab	r;

	while (42)
	{
		if (err > 1.001f)
		{
			if (cd.x > 0)
				c0.x++;
			else
				c0.x--;
			err -= 1.0f;
			replace_var(&r, c0);
			if (should_stop(general, c0) == 0)
				break ;
		}
		err += fabs((float) cd.x / (float) cd.y);
		if (cd.y > 0)
			c0.y++;
		else
			c0.y--;
		replace_var(&r, c0);
		if (should_stop(general, c0) == 0)
			break ;
	}
	return (r);
}

t_tab	find_point_on_screen(t_general *general, t_coord c0, t_coord c1)
{
	int		dx;
	int		dy;
	float	err;

	dx = c1.x - c0.x;
	dy = c1.y - c0.x;
	err = 0.5f;
	if (abs(dx) >= abs(dy))
	{
		return (p1(general, c0, (t_coord){dx, dy, 0}, err));
	}
	else
	{
		return (p2(general, c0, (t_coord){dx, dy, 0}, err));
	}
}
