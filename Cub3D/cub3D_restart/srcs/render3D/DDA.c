#include "render3D.h"

t_tab DDA_boosted(t_general *general, t_coord c0, t_vec c1)
{
	int		dx;
	int		dy;
	t_tab	result;
	dx = c1.x - c0.x;
	dy = c1.y - c0.y;
	double	slope;
	t_vec	pos;
	t_coord 	last_pos;
	double 	adv_x;
	double 	adv_y;

	result.v2.x = 0;
	result.v2.y = 0;

	slope = (double) dy / dx;
	pos.x = c0.x;
	pos.y = c0.y;

	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
	if (steps == 0)
		printf("PROBELE EEMEFE\n");
	int i = 0;
	while(42)
	{
		
		i++;

		if (pos.x < 0 || pos.y < 0)
			break ;

		if (dx > 0)
        {
            // if (pos.x > c1.x)
            //     break ;
			adv_x = (double)SIZE_WALL - fmod(pos.x, SIZE_WALL);
        }
		else
        {
            // if (pos.x < c1.x)
            //     break ;
			adv_x = -fmod(pos.x, SIZE_WALL);

        }
		if (dy > 0)
        {
            // if (pos.y > c1.y)
            //     break ;
			adv_y = (double) SIZE_WALL - fmod(pos.y, SIZE_WALL);

        }
		else
        {
            // if (pos.y < c1.y)
            //     break ;              
			adv_y = -fmod(pos.y, SIZE_WALL);

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

		last_pos.x = (pos.x);
		last_pos.y = (pos.y);

		// printf("slope %f, adv * slope (%f) <= adv_y %f\n", slope, fabsf(adv_x * slope), fabsf(adv_y));
		if (dx < 0)
			adv_x--;
		if (dy < 0)
			adv_y--;
		if (fabs(adv_x * slope) <= fabs(adv_y))
		{

			pos.x = (pos.x + adv_x);
			pos.y += adv_x * slope;
		}
		else
		{

			pos.x += adv_y / slope;
			pos.y = (pos.y + adv_y);
		}
		result.v2.x = pos.x;
		result.v2.y = pos.y;
		result.v3.x = pos.x;
		result.v3.y = pos.y;

		// printf("Adv_x, Adv_y %f, %f\n", adv_x, adv_y);
		// printf("pos (%f, %f)\n", pos.x, pos.y);

		if (should_stop(general, (t_coord) {pos.x, pos.y, 0}))
		{
			break ;
		}

	}
	// printf("\n\n\n");
	return (result);
}