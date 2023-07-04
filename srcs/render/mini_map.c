#include "../../header.h"


void draw_cross(t_general *general, int x, int y, int color) {
    t_mlib  *mlib;
    mlib = general->mlib;

    // Taille de la croix
    int size = 3;

    for(int i = -size; i <= size; i++) {
        my_mlx_pixel_put(&mlib->data, x + i, y, color);
        my_mlx_pixel_put(&mlib->data, x, y + i, color);
    }
}

void draw_line(t_general *general, int x0, int y0, int x1, int y1, int color) {
    t_mlib  *mlib;
    mlib = general->mlib;

    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
    int err = (dx>dy ? dx : -dy)/2, e2;

    while (1) {
        my_mlx_pixel_put(&mlib->data, x0, y0, color);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

void draw_arrow(t_general *general, int x0, int y0, float dx, float dy, int color) {
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
    float head_len = 5;

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

    // Here we are making the arrow shorter by scaling down the direction vector
    float dir_scale = 0.2 * general->scene->map.size_wall;
    coord_vector.x = general->scene->player.dir.x * dir_scale;
    coord_vector.y = general->scene->player.dir.y * dir_scale;

    draw_arrow(general, int_x0, int_y0, coord_vector.x, coord_vector.y, 0xFF0000);
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

int render_mini_map(t_general *general)
{
    t_mlib  *mlib = general->mlib;


    mlib->data.img_ptr = mlx_new_image(mlib->utils.mlx, WIDTH, HEIGHT);
    mlib->data.addr = mlx_get_data_addr(mlib->data.img_ptr, &mlib->data.bits_per_pixel, &mlib->data.line_length, &mlib->data.endian);

    /* Creation de l image */
    render_wall2D(general);

    move(general);
    // printf("w %d\n", general->keys->w);
    // printf("a %d\n", general->keys->a);
    // printf("s %d\n", general->keys->s);
    // printf("d %d\n", general->keys->d);
    // printf("l %d\n", general->keys->arrow_l);
    // printf("r %d\n", general->keys->arrow_r);



    draw_player(general);
    
    
    
    //mlx_sync(MLX_SYNC_IMAGE_WRITABLE, mlib->data.img_ptr);
    mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, mlib->data.img_ptr, 0, 0);
    mlx_destroy_image(mlib->utils.mlx, mlib->data.img_ptr);
    //mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, mlib->data.img_ptr);
    return (0);
}