#include "../../header.h"

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

void draw_rays(t_general *general, t_coord position, int x1, int y1) 
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
    t_coord   position;
    t_vec   direction;
    t_coord   end_point;

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
        //end_point = get_end_point(general, position, angle);
        end_point.x = position.x + cos_angle * (WIDTH);
        end_point.y = position.y + sin_angle * (WIDTH);
        end_point.z = 0.0f;
        draw_rays(general, position, end_point.x, end_point.y);
    }
}


int render_mini_map(t_general *general)
{
    t_mlib  *mlib = general->mlib;


    mlib->data.img_ptr = mlx_new_image(mlib->utils.mlx, WIDTH, HEIGHT);
    mlib->data.addr = mlx_get_data_addr(mlib->data.img_ptr, &mlib->data.bits_per_pixel, &mlib->data.line_length, &mlib->data.endian);

    render_wall2D(general);
    draw_grid(general);
    move(general);
    launch_mid_ray(general);
    draw_player(general);
    
    //mlx_sync(MLX_SYNC_IMAGE_WRITABLE, mlib->data.img_ptr);
    mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, mlib->data.img_ptr, 0, 0);
    mlx_destroy_image(mlib->utils.mlx, mlib->data.img_ptr);
    //mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, mlib->data.img_ptr);
    return (0);
}