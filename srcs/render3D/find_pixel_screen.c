
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

static void	init_var(int *dx, int *dy, t_coord c0, t_coord c1)
{
	*dx = c1.x - c0.x;
	*dy = c1.y - c0.x;
}

static t_tab    p1(t_general *general, t_coord c0, t_coord c1)
{
	int		dx;
	int		dy;
	float	err;
    t_tab r;

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
			r.v1.x = r.v2.x;
			r.v1.y = r.v2.y;
			r.v1.z = 0;
			r.v2.x = c0.x;
			r.v2.y = c0.y;
			r.v2.z = 0;
			if (should_stop(general, c0) == 0)
				break ;
		}
		err += fabs((float) dy / (float)dx);
		if (dx > 0)
			c0.x++;
		else
			c0.x--;
        r.v1.x = r.v2.x;
        r.v1.y = r.v2.y;
        r.v1.z = 0;
        r.v2.x = c0.x;
        r.v2.y = c0.y;
        r.v2.z = 0;
		if (should_stop(general, c0) == 0)
			break ;
	}
    return (r);
}

static t_tab	p2(t_general *general, t_coord c0, t_coord c1)
{
	int		dx;
	int		dy;
	float	err;
    t_tab r;

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
			r.v1.x = r.v2.x;
			r.v1.y = r.v2.y;
			r.v1.z = 0;
			r.v2.x = c0.x;
			r.v2.y = c0.y;
			r.v2.z = 0;
			if (should_stop(general, c0) == 0)
				break ;
		}
		err += fabs((float) dx / (float) dy);
		if (dy > 0)
			c0.y++;
		else
			c0.y--;
        r.v1.x = r.v2.x;
        r.v1.y = r.v2.y;
        r.v1.z = 0;
        r.v2.x = c0.x;
        r.v2.y = c0.y;
        r.v2.z = 0;
		if (should_stop(general, c0) == 0)
			break ;

	}
    return (r);
}

t_tab find_point_on_screen(t_general *general, t_coord c0, t_coord c1)
{
	int		dx;
	int		dy;

	dx = c1.x - c0.x;
	dy = c1.y - c0.x;
	if (abs(dx) >= abs(dy))
	{
		return (p1(general, c0, c1));
	}
	else
	{
		return (p2(general, c0, c1));
	}
}
