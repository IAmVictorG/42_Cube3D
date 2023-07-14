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


int hit_a_wall(t_general *general, int x, int y)
{
    char **matrix = general->scene->map.matrix;
    int size_wall = general->scene->map.size_wall;
    int map_h = general->scene->map.height_map;
    int map_w = general->scene->map.width_map;


    //printf("y = %d x = %d\n", y / size_wall, x / size_wall);

    if (y / size_wall >= map_h || x / size_wall >= map_w)
    {
        return (0);
    }


    return (matrix[y / size_wall][x / size_wall] == '1');

}

int hit_corner(t_general *general, int x, int y)
{
    char **matrix = general->scene->map.matrix;
    int size_wall = general->scene->map.size_wall;


    int y_mat = y / size_wall;
    int x_mat = x / size_wall;

    if (matrix[y_mat][x_mat] == '1' && matrix[y_mat-1][x_mat-1] == '1')
    {
        return (1);
    }

    return (0);
}

void draw_rays(t_general *general, t_vec position, int x1, int y1) 
{
    t_mlib *mlib;

    mlib = general->mlib;

    t_coord relative_pos;
    t_coord position_int;

    position_int.x = (int) position.x;
    position_int.y = (int) position.y;
    

    relative_pos.x = abs(x1 - position_int.x);
    relative_pos.y = abs(y1 - position_int.y);

    int sx = (position_int.x < x1) ? 1 : -1;
    int sy = (position_int.y < y1) ? 1 : -1;
    int err = relative_pos.x - relative_pos.y;


    while (42) 
    {
        // Ensure the pixel coordinates are within window bounds
        if (position_int.x >= 0 && position_int.x < WIDTH && position_int.y >= 0 && position_int.y < HEIGHT) 
        {
            if (hit_a_wall(general,position_int.x, position_int.y) == 0)
            {
                my_mlx_pixel_put(&mlib->data, position_int.x, position_int.y, 0xFF0000);
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }

        if (position_int.x == x1 && position_int.y == y1)   
            break;
        int e2 = 2 * err;
        if (e2 > -relative_pos.y)
        {
            err -= relative_pos.y;
            position_int.x += sx;
        }
        else if (e2 < relative_pos.x) 
        {
            err += relative_pos.x;
            position_int.y += sy;
        }
    }

}

void launch_mid_ray(t_general *general)
{
    t_vec   position;
    t_vec   direction;

    float   player_angle;
    float   fov_rad;
    float   fov_start;
    float   fov_end;
    float   angle;
    float   angle_step;

    float   cos_angle;
    float   sin_angle;  


    position = general->scene->player.pos;
    direction = general->scene->player.dir;

    //size_wall = general->scene->map.size_wall;


    player_angle = atan2f(direction.y, direction.x);
    fov_rad = FOV * M_PI / 180;
    fov_start = player_angle - fov_rad / 2;
    fov_end = player_angle + fov_rad / 2;
    angle_step = fov_rad / 100;

    for (angle = fov_start; angle <= fov_end; angle += angle_step)
    {
        cos_angle = cosf(angle);
        sin_angle = sinf(angle);
        t_vec end_point = {position.x + cos_angle * (WIDTH), position.y + sin_angle * (WIDTH), 0.0f};
        draw_rays(general, position, end_point.x, end_point.y);
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

    while (j / size_wall < map_h)
    {
        i = 0;
        while (i / size_wall < map_w)
        {
            printf("j = %d i = %d \n", j / size_wall, i / size_wall );
            printf("%c\n", matrix[j/size_wall][i/size_wall]);
            i++;
        }
        printf("\n");
        j++;
    }
    sleep(1);
}

int render_mini_map(t_general *general)
{
    t_mlib  *mlib = general->mlib;


    mlib->data.img_ptr = mlx_new_image(mlib->utils.mlx, WIDTH, HEIGHT);
    mlib->data.addr = mlx_get_data_addr(mlib->data.img_ptr, &mlib->data.bits_per_pixel, &mlib->data.line_length, &mlib->data.endian);

    render_wall2D(general);
    draw_grid(general);
    move(general);
    draw_player(general);
    launch_mid_ray(general);
    
    //mlx_sync(MLX_SYNC_IMAGE_WRITABLE, mlib->data.img_ptr);
    mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, mlib->data.img_ptr, 0, 0);
    mlx_destroy_image(mlib->utils.mlx, mlib->data.img_ptr);
    //mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, mlib->data.img_ptr);
    return (0);
}