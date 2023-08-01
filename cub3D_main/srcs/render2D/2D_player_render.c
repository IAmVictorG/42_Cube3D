#include "../../header.h"

void draw_cross(t_general *general, int x, int y, int color) 
{
    t_mlib  *mlib;
    mlib = general->mlib;

    // Taille de la croix
    int size = 3;

    for(int i = -size; i <= size; i++) {
        my_mlx_pixel_put(&mlib->data, x + i, y, color);
        my_mlx_pixel_put(&mlib->data, x, y + i, color);
    }
}

void draw_line(t_general *general, int x0, int y0, int x1, int y1, int color) 
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

void draw_arrow(t_general *general, int x0, int y0, float dx, float dy, int color) 
{

    //t_mlib  *mlib;
    //mlib = general->mlib;

    int x1 = x0 + dx;
    int y1 = y0 + dy;

    //draw_line(general, x0, y0, x1, y1, color); // Draw the main line of the arrow

    // Compute the direction of the arrow for the arrowhead
    float arrow_dir_x = dx / sqrtf(dx * dx + dy * dy);
    float arrow_dir_y = dy / sqrtf(dx * dx + dy * dy);

    // Compute the perpendicular direction for the arrowhead
    float arrow_perp_x = -arrow_dir_y;
    float arrow_perp_y = arrow_dir_x;

    // Length of the arrowhead
    float head_len = 7;

    // Draw the two sides of the arrowhead
    draw_line(general, x1, y1, x1 - head_len * (arrow_dir_x + arrow_perp_x), y1 - head_len * (arrow_dir_y + arrow_perp_y), color);
    draw_line(general, x1, y1, x1 - head_len * (arrow_dir_x - arrow_perp_x), y1 - head_len * (arrow_dir_y - arrow_perp_y), color);
}

void draw_player(t_general *general)
{
    int color;
    t_coord coord_vector;

    color = 0x00FF00;

    int int_x0 = roundf(general->scene->player.pos.x);
    int int_y0 = roundf(general->scene->player.pos.y);

    draw_cross(general, int_x0, int_y0, color);

    float dir_scale = 0.2 * general->scene->map.size_wall;
    coord_vector.x = general->scene->player.dir.x * dir_scale;
    coord_vector.y = general->scene->player.dir.y * dir_scale;

    draw_arrow(general, int_x0, int_y0, coord_vector.x, coord_vector.y, 0x00FF00);
}