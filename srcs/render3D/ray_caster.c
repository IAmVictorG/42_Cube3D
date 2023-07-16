#include "../../header.h"


t_vec calculate_rays(t_general *general, int x0, int y0, int x1, int y1, int size_wall, int window_width, int window_height) 
{
    //t_mlib *mlib;
    t_vec r;

    //mlib = general->mlib;


    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    //printf("dx = %d, dy = %d\n", dx, dy);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    (void) size_wall;

    while (42) 
    {
        // Ensure the pixel coordinates are within window bounds
        if (x0 >= 0 && x0 < window_width && y0 >= 0 && y0 < window_height) 
        {
            if (hit_a_wall(general,x0, y0) == 1)
                break;
        }
        else
            break;


        if (x0 == x1 && y0 == y1)   
            break;
        int e2 = 2 * err;
        if (e2 > -dy) 
        {
            err -= dy;
            x0 += sx;
        }
        else if (e2 < dx) 
        {
            err += dx;
            y0 += sy;
        }
    }
    r.x = x0;
    r.y = y0;
    r.z = 0;
    return (r);
}

t_coord   calculate_rays2(t_general *general)
{
    t_coord ray_point;
    (void)  general;

    ray_point.x = 0;
    ray_point.y = 0;
    ray_point.z = 0;


    return ray_point;
}


void trace_ray(t_general *general) 
{
    t_coord position = general->scene->player.pos;
    t_vec direction = general->scene->player.dir;
    t_vec ray;

    int imageincre = 0;
    int size_wall = general->scene->map.size_wall;
    int window_width = WIDTH;
    int window_height = HEIGHT;

    float player_angle = atan2f(direction.y, direction.x);
    float fov_rad = FOV * M_PI / 180;
    float fov_start = player_angle - fov_rad / 2;
    float fov_end = player_angle + fov_rad / 2;

    float angle_step = fov_rad / WIDTH;

    //printf("angle_step = %f \n", angle_step);

    for (float angle = fov_start; angle <= fov_end; angle += angle_step)
    {
        float cos_angle = cosf(angle);
        float sin_angle = sinf(angle);
        t_vec end_point = {position.x + cos_angle * (window_width), position.y + sin_angle * (window_width), 0.0f}; //windows_width ??? issue with the length of the ray
        //printVec(end_point);


        ray = calculate_rays(general, position.x, position.y, end_point.x, end_point.y, size_wall, window_width, window_height);
        int wall_height;
        float dist;
        float delta_angle = angle - player_angle;

        dist = sqrtf((ray.x - general->scene->player.pos.x)*(ray.x - general->scene->player.pos.x) + (ray.y - general->scene->player.pos.y)*(ray.y - general->scene->player.pos.y));
        dist /= size_wall;
        dist *= cos(delta_angle);

        //int r;
        if (dist <= 1.0f)
        {
            //r = 10;
            wall_height = HEIGHT;
        }
        else
        {
            //r = 0;
             wall_height = HEIGHT / dist;
        }

        for (int i = 0; i < (window_height - wall_height) / 2; i++)
        {
            if (imageincre < WIDTH && i < HEIGHT) 
            {
                my_mlx_pixel_put(&general->mlib->data, imageincre, i, SKY_COLOR);
            }
        }

        for (int i = (window_height + wall_height) / 2; i < window_height; i++) {
            if (imageincre < WIDTH && i < HEIGHT) 
            {
                my_mlx_pixel_put(&general->mlib->data, imageincre, i, FLOOR_COLOR);
            }
        }

        if ((int) ray.y % size_wall == 0)
        {
            draw_3D_line_south(general, ray, wall_height, imageincre);
        }
        else if ((int) ray.y % size_wall == size_wall - 1)
        {
            draw_3D_line_north(general,ray, wall_height, imageincre);                 
        }

        if ((int) ray.x % size_wall == 0)
        {
            draw_3D_line_east(general, ray, wall_height, imageincre);

        }
        else if ((int) ray.x % size_wall == size_wall - 1)
        {
            draw_3D_line_west(general, ray, wall_height, imageincre);
        }   

        imageincre++;
    }
}

int render_game(t_general *general)
{
    t_mlib  *mlib = general->mlib;

    mlib->data.img_ptr = mlx_new_image(mlib->utils.mlx, WIDTH, HEIGHT);
    mlib->data.addr = mlx_get_data_addr(mlib->data.img_ptr, &mlib->data.bits_per_pixel, &mlib->data.line_length, &mlib->data.endian);


    //load_texture(general);
    //my_mlx_pixel_put(&sprites->wall_north.data_spr, 10, 10, convert_char_to_int(sprites->wall_north.data_spr.addr));
    //my_mlx_pixel_put(&mlib->data, 15, 15, 0xFF0000);



    //my_mlx_pixel_put(&mlib->data, 10, 10, color);
    //mlx_put_image_to_window(&mlib->utils.mlx, mlib->utils.win, sprites->wall_north.data_spr.img_ptr, 0, 0);

    //trace_wall(general, general->sprites->wall_east);

    trace_ray(general);
    move(general);
    mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, mlib->data.img_ptr, 0, 0);
    mlx_destroy_image(mlib->utils.mlx, mlib->data.img_ptr);
    return (0);
}

