#include "render3D.h"

void draw_3D_line_south_near(t_general *general, t_vec ray, int imageincre, float dist)
{

    int i;
    int x_text;
    unsigned int color;

    (void) dist;

    i = 0;
    while (i < HEIGHT)
    {
        x_text = (int) roundf(ray.x);
        color = get_color_wall_south_near(general ,x_text, i, dist);
        color = 0x0000FF;
        my_mlx_pixel_put(&general->mlib->data, imageincre, i, color);
        i++;
    }
}

void draw_3D_line_north_near(t_general *general, t_vec ray, int imageincre, float dist)
{

    int i;
    int x_text;
    unsigned int color;

    i = 0;
    while (i < HEIGHT)
    {
        x_text = (int) roundf(ray.x);
        color = get_color_wall_north_near(general ,x_text, i, dist);
        my_mlx_pixel_put(&general->mlib->data, imageincre, i, color);
        i++;
    }
}

void draw_3D_line_west_near(t_general *general, t_vec ray, int imageincre, float dist)
{

    int i;
    int x_text;
    unsigned int color;

    i = 0;
    while (i < HEIGHT)
    {
        x_text = (int) roundf(ray.y);
        color = get_color_wall_west_near(general ,x_text, i, dist);
        my_mlx_pixel_put(&general->mlib->data, imageincre, i, color);
        i++;
    }
}

void draw_3D_line_east_near(t_general *general, t_vec ray, int imageincre, float dist)
{

    int i;
    int x_ray;
    unsigned int color;

    i = 0;
    while (i < HEIGHT)
    {
        x_ray = (int) roundf(ray.y);
        color = get_color_wall_east_near(general ,x_ray, i, dist);
        my_mlx_pixel_put(&general->mlib->data, imageincre, i, color);
        i++;
    }
}