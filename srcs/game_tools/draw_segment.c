#include "../../header.h"

static void draw1(t_general *general, int x0, int y0, int x1, int y1, int color)
{
    while (42)
    {
        if (err > 1.001f)
        {
            if (dy > 0)
                y0++;
            else
                y0--;
            err -= 1.0f;
        }
        my_mlx_pixel_put(&(general->mlib->data), x0,y0,color);
        err += fabs((float) dy / (float)dx);
        if (x0 == x1)
            break;
        if (dx > 0)
            x0++;
        else
            x0--;
    }
}


void draw_segment(t_general *general, int x0, int y0, int x1, int y1, int color) 
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	float err = 0.5f;

	if (abs(dx) >= abs(dy))
	{
		while (42)
		{
			if (err > 1.001f)
			{
				if (dy > 0)
					y0++;
				else
					y0--;
				err -= 1.0f;
			}
			my_mlx_pixel_put(&(general->mlib->data), x0,y0,color);
			err += fabs((float) dy / (float)dx);
			if (x0 == x1)
				break;
			if (dx > 0)
				x0++;
			else
				x0--;
		}
	}
	else
	{
		while (42)
		{
			if (err > 1.001f)
			{
				if (dx > 0)
					x0++;
				else
					x0--;
				err -= 1.0f;
			}
			my_mlx_pixel_put(&(general->mlib->data), x0,y0,color);
			err += fabs((float) dx / (float) dy);
			if (y0 == y1)
				break;
			if (dy > 0)
				y0++;
			else
				y0--;
		}
	}
}