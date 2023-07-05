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
    float head_len = 5;

    // Draw the two sides of the arrowhead
    draw_line(general, x1, y1, x1 - head_len * (arrow_dir_x + arrow_perp_x), y1 - head_len * (arrow_dir_y + arrow_perp_y), color);
    draw_line(general, x1, y1, x1 - head_len * (arrow_dir_x - arrow_perp_x), y1 - head_len * (arrow_dir_y - arrow_perp_y), color);
}

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

t_vec   absolute_to_relative(int x, int y, t_vec origin)
{
    t_vec   result;

    result.x = x - origin.x;
    result.y = y - origin.y;
    result.z = 0.0f;

    return (result);
}

t_vec   relative_to_absolute(float x, float y, t_vec origin)
{
    t_vec   result;

    result.x = x + origin.x;
    result.y = y + origin.y;
    result.z = 0.0f;

    return (result);

}

/*static  int is_in_definition_domain(t_vec pixel_relative, t_vec direction)
{
    return (pixel_relative.x * direction.x + pixel_relative.y * direction.y > 0);
}*/

int position_is_valid_pix(t_general *general, int i, int j)
{

    int     size_wall;
    char    **matrix;

    matrix = general->scene->map.matrix;
    size_wall = general->scene->map.size_wall;

    printf("c = %c ", matrix[j / size_wall][i / size_wall]);

    return (!(matrix[j / size_wall][i / size_wall] == '1'));
}

void draw_rays(t_mlib *mlib, int x0, int y0, int x1, int y1, int size_wall, int window_width, int window_height) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (42) {
        // Ensure the pixel coordinates are within window bounds
        if (x0 >= 0 && x0 < window_width && y0 >= 0 && y0 < window_height) {
            int color = (x0 % size_wall == 0 || y0 % size_wall == 0) ? 0xFFFF00 : 0xFF0000;
            my_mlx_pixel_put(&mlib->data, x0, y0, color);
        }
        else
            break;

        if (x0 == x1 && y0 == y1)   
            break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}


void launch_mid_ray(t_general *general) {
    t_vec position = general->scene->player.pos;
    t_vec direction = general->scene->player.dir;

    int size_wall = general->scene->map.size_wall;
    int window_width = WIDTH;
    int window_height = HEIGHT;

    t_mlib *mlib = general->mlib;

    float player_angle = atan2f(direction.y, direction.x);
    float fov_rad = FOV * M_PI / 180;
    float fov_start = player_angle - fov_rad / 2;
    float fov_end = player_angle + fov_rad / 2;
    float angle_step = fov_rad / 500;

    for (float angle = fov_start; angle <= fov_end; angle += angle_step)
    {
        float cos_angle = cosf(angle);
        float sin_angle = sinf(angle);
        t_vec end_point = {position.x + cos_angle * (window_width), position.y + sin_angle * (window_width ), 0.0f};

        //if (end_point.x >= window_width) end_point.x = window_width - 1;
        //if (end_point.y >= window_height) end_point.y = window_height - 1;

        draw_rays(mlib, position.x, position.y, end_point.x, end_point.y, size_wall, window_width, window_height);

    }
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

void test(t_general *general)
{
    char **matrix = general->scene->map.matrix;
    int size_wall = general->scene->map.size_wall;
    int i = 0;
    int j = 0;


    int map_h = general->scene->map.height_map;
    int map_w = general->scene->map.width_map;
    //(void) general;

    while (j / size_wall < map_h)
    {
        i = 0;
        while (i / size_wall < map_w)
        {
            //position_is_valid_pix(general, i,j);

            printf("j = %d i = %d \n", j / size_wall, i / size_wall );
            printf("%c\n", matrix[j/size_wall][i/size_wall]);
            

           

            //sleep(1);

            i++;
        }
        printf("\n");
        //sleep(1);
        j++;
    }
    sleep(1);
}

int render_mini_map(t_general *general)
{
    t_mlib  *mlib = general->mlib;


    mlib->data.img_ptr = mlx_new_image(mlib->utils.mlx, WIDTH, HEIGHT);
    mlib->data.addr = mlx_get_data_addr(mlib->data.img_ptr, &mlib->data.bits_per_pixel, &mlib->data.line_length, &mlib->data.endian);

    //test(general);
    //sleep(10);
    /* Creation de l image */
    render_wall2D(general);

    /* Affichage de la grille */
    draw_grid(general);

    /* Mouvement du joueur */
    move(general);

    draw_player(general);

    launch_mid_ray(general);
    
    
    
    //mlx_sync(MLX_SYNC_IMAGE_WRITABLE, mlib->data.img_ptr);
    mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, mlib->data.img_ptr, 0, 0);
    mlx_destroy_image(mlib->utils.mlx, mlib->data.img_ptr);
    //mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, mlib->data.img_ptr);
    return (0);
}