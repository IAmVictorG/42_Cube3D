#include "../../header.h"

void    draw_grid(t_general *general)
{
    int     size_wall;
    t_mlib  *mlib;
    int     map_h = general->scene->map.height_map;
    int     map_w = general->scene->map.width_map;
    int     i;
    int     j;

    mlib = general->mlib;
    size_wall = general->scene->map.size_wall;
    j = 0;
    while (j < (map_h * size_wall + 1))
    {   
        i = 0;
        while (i < (map_w * size_wall + 1))
        {
            if (j % size_wall == 0)
            {
                my_mlx_pixel_put(&mlib->data, i, j, 0x00AA00);
            }
            if (i % size_wall == 0)
            {
                my_mlx_pixel_put(&mlib->data, i, j, 0x00AA00);
            }
            i++;
        }
        j++;
    }
}

void    draw_wall(int pixel_x, int pixel_y, int size_wall, t_mlib *mlib)
{   
    int x;
    int y;

    y = 0;
    while (y < size_wall)
    {
        x = 0;
        while (x < size_wall)
        {
            my_mlx_pixel_put(&mlib->data, pixel_x + x, pixel_y + y, 0x1100FF);
            x++;
        }
        y++;
    }
}

void render_wall2D(t_general *general)
{
    int i;
    int j;

    j = 0;
    while (j < general->scene->map.height_map)
    {
        i = 0;
        while (i < general->scene->map.width_map)
        {
            if (general->scene->map.matrix[j][i] == '1')
            {
                draw_wall(i * general->scene->map.size_wall, j * general->scene->map.size_wall, general->scene->map.size_wall, general->mlib);
            }
            i++;
        }
        j++;
    }

}