#include "render3D.h"

static int	should_stop(t_general *general, t_coord c0)
{
	if (hit_a_wall(general, c0.x, c0.y) != 0)
		return (0);
	return (1);
}

static void	init_var(int *dx, int *dy, t_coord c0, t_coord c1)
{
	*dx = c1.x - c0.x;
	*dy = c1.y - c0.x;
}

t_coord findv1(t_coord c0, t_coord c1, t_coord v2)
{
	t_coord result;
	int dx = c1.x - c0.x;
	int dy = c1.y - c0.y;

	if (abs(dx) >= abs(dy))
	{
		result.y = v2.y;
		if (dx > 0)
			result.x = v2.x + 1;
		else
			result.x = v2.x - 1;
	}
	else
	{
		result.x = v2.x;
		if (dy > 0)
			result.y = v2.y + 1;
		else
			result.y = v2.y - 1;

	}

	return result;
}

t_tab DDA_boosted(t_general *general, t_coord c0, t_coord c1)
{
	int		dx;
	int		dy;
	float	slope;
	t_tab	result;
	t_vec	pos;
	int adv_x;
	int adv_y;

	dx = c1.x - c0.x;
	dy = c1.y - c0.y;
	if (dx == 0)
		slope = 1;
	else
		slope = (float) dy / dx;
	pos.x = c0.x;
	pos.y = c0.y;

	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    // calculate increment in x & y for each steps
	if (steps == 0)
		printf("PROBELE EEMEFE\n");
	while(42)
	{
		if (should_stop(general, (t_coord) {(int)pos.x, (int)pos.y, 0}) == 0)
			break ;

		if (pos.x < 0 || pos.y < 0)
			break ;

		if (dx > 0)
        {
            if (pos.x > c1.x)
                break ;
			adv_x = SIZE_WALL - (int) pos.x % SIZE_WALL ;
        }
		else
        {
            if (pos.x < c1.x)
                break ;
			adv_x = (int) - pos.x % SIZE_WALL ;
        }
		if (dy > 0)
        {
            if (pos.y > c1.y)
                break ;     
			adv_y = SIZE_WALL - (int) pos.y % SIZE_WALL;
        }
		else
        {
            if (pos.y < c1.y)
                break ;              
			adv_y = - (int) pos.y % SIZE_WALL;
        }
		if (adv_x == 0 && (int) pos.x % SIZE_WALL == 0)
        {
            if (dx > 0)
			    adv_x = SIZE_WALL;
            else
                adv_x = -SIZE_WALL;
        }
		if (adv_y == 0 && (int) pos.y % SIZE_WALL == 0)
        {
            if (dy > 0)
			    adv_y = SIZE_WALL;
            else
                adv_y = -SIZE_WALL;
        }

        //printf("(%f, %f), adv (%d, %d) slope %f\n", pos.x, pos.y, adv_x, adv_y, slope);
		if (fabsf(adv_x * slope) < abs(adv_y))
		{
			pos.x = roundf(pos.x + adv_x);
			pos.y += (float) adv_x * slope;
		}
		else
		{
			pos.x += (float) adv_y / slope;
			pos.y = roundf(pos.y + adv_y);
		}
		//printf("(%f, %f), adv (%d, %d) slope %f\n", pos.x, pos.y, adv_x, adv_y, slope);
	}
	result.v2.x = pos.x;
	result.v2.y = pos.y;
	result.v1 = findv1(c0, c1, result.v2);
	return (result);
}


static t_tab    p1ew(t_general *general, t_coord c0, t_coord c1)
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
	r.v3.x = r.v2.x;
	r.v3.y = r.v2.y + err;
    return (r);
}

static t_tab	p2sn(t_general *general, t_coord c0, t_coord c1)
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
	r.v3.x = r.v2.x + err;
	r.v3.y = r.v2.y;
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
		return (p1ew(general, c0, c1));
	}
	else
	{
		return (p2sn(general, c0, c1));
	}
}