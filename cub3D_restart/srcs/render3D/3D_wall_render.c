#include "render3D.h"

void draw_3D_line_west(t_general *general, t_coord ray, int wall_height, int imageincre)
{
    int             i;
    unsigned int    color;
        
    i = 0;
    if ((HEIGHT - wall_height) / 2 > 0)
    {
        while (i < wall_height)
        {
            color = get_color_wall_west(general, ray.y, i, wall_height);
            my_mlx_pixel_put(&general->mlib->data, imageincre, (HEIGHT - wall_height) / 2 + i, color);
            i++;
        }
    }
    else
    {
        while (i < HEIGHT)
        {
            color = get_color_wall_west(general, ray.y, (wall_height - HEIGHT) / 2 + i, wall_height);
            my_mlx_pixel_put(&general->mlib->data, imageincre, i, color);
            i++;
        }
    }
}

void draw_3D_line_east(t_general *general, t_coord ray, int wall_height, int imageincre)
{
    int             i;
    unsigned int    color;
        
    i = 0;
    if ((HEIGHT - wall_height) > 0)
    {
        while (i < wall_height)
        {
            color = get_color_wall_east(general, ray.y, i, wall_height);
            my_mlx_pixel_put(&general->mlib->data, imageincre, (HEIGHT - wall_height) / 2 + i, color);
            i++;
        }
    }
    else
    {
        while (i < HEIGHT)
        {
            color = get_color_wall_east(general, ray.y, (wall_height - HEIGHT) / 2 + i, wall_height);
            my_mlx_pixel_put(&general->mlib->data, imageincre, i, color);
            i++;
        }
    }
}

void draw_3D_line_south(t_general *general, t_coord ray, int wall_height, int imageincre)
{
    int             i;
    unsigned int    color;
        
    i = 0;
    if ((HEIGHT - wall_height) / 2 > 0)
    {
        while (i < wall_height)
        {
            color = get_color_wall_south(general, ray.x, i, wall_height);
            my_mlx_pixel_put(&general->mlib->data, imageincre, (HEIGHT - wall_height) / 2 + i, color);
            i++;
        }
    }
    else
    {
        while (i < HEIGHT)
        {
            color = get_color_wall_south(general, ray.x, (wall_height - HEIGHT) / 2 + i, wall_height);
            my_mlx_pixel_put(&general->mlib->data, imageincre, i, color);
            i++;
        }
    }
}


void draw_3D_line_north(t_general *general, t_coord ray, int wall_height, int imageincre)
{
    int             i;
    unsigned int    color;
        
    i = 0;
    if ((HEIGHT - wall_height) / 2 > 0)
    {
        while (i < wall_height)
        {
            color = get_color_wall_north(general, ray.x, i, wall_height);
            my_mlx_pixel_put(&general->mlib->data, imageincre, (HEIGHT - wall_height) / 2 + i, color);
            i++;
        }
    }
    else
    {
        while (i < HEIGHT)
        {
            color = get_color_wall_north(general, ray.x, (wall_height - HEIGHT) / 2 + i, wall_height);
            my_mlx_pixel_put(&general->mlib->data, imageincre, i, color);
            i++;
        }
    }
}


void draw_3D_line_color(t_general *general, t_vec ray, int wall_height, int imageincre, unsigned int color)
{
    int i;
    int x_int;


    for (i = 0; i < wall_height; i++)
    {
        x_int = (int) roundf(ray.x);

        my_mlx_pixel_put(&general->mlib->data, imageincre, (HEIGHT - wall_height) / 2 + i, color);
    }
}