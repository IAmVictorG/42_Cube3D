#include "../../header.h"

t_vec create_ray(t_scene *scene, int pixel_x, int pixel_y)
{
    (void) scene;
    float aspect_ratio;
    t_vec dir_r;
    float dx; //increment x
    float dy; //increment y

    float d; //distance total


    d = 2.0f * tanf((float) FOV * 0.5f);
    dx = d / (float) WIDTH;
    
    aspect_ratio = (float) HEIGHT / (float) WIDTH;
    dy = dx * aspect_ratio;


    dir_r = (t_vec) {dx * pixel_x, dy * pixel_y, 1.0f};
    dir_r = vec_normalize(dir_r);
    printVec(dir_r);
    return (dir_r);
}




t_vec draw_rays_3D(t_general *general, int x0, int y0, int x1, int y1) 
{
    t_mlib *mlib;
    t_vec result;

    mlib = general->mlib;

    int size_wall = general->scene->map.size_wall;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (42) {
        // Ensure the pixel coordinates are within window bounds
        if (x0 >= 0 && x0 < WIDTH && y0 >= 0 && y0 < HEIGHT) 
        {
            if (x0 % size_wall == 0 && y0 % size_wall == 0)
            {
                if (hit_corner(general,x0, y0) == 1)
                    break;

            }
            else
            {
                if (hit_a_wall(general,x0, y0) == 0)
                    my_mlx_pixel_put(&mlib->data, x0, y0, 0xFF0000);
                else
                {
                    break;
                }
            }
            //int color = (x0 % size_wall == 0 || y0 % size_wall == 0) ? 0xFFFF00 : 0xFF0000;

        }
        else
            break;

        // if (x0 >= 0 && x0 < window_width && y0 >= 0 && y0 < window_height) {
            



        //     int color = (x0 % size_wall == 0 || y0 % size_wall == 0) ? 0xFFFF00 : 0xFF0000;
        //     if (hit_a_wall(general,x0, y0) == 0)
        //         my_mlx_pixel_put(&mlib->data, x0, y0, color);
        //     else
        //         break;
        // }
        // else
        //     break;

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
    result.x = x0;
    result.y = y0;
    result.z = 0;
    return (result);
}

void launch_mid_ray_3D(t_general *general)
{
    //printf("RAY\n");
    t_vec position = general->scene->player.pos;
    t_vec direction = general->scene->player.dir;
    t_vec result;

    //int size_wall = general->scene->map.size_wall;
    int window_width = WIDTH;
    //int window_height = HEIGHT;

    //t_mlib *mlib = general->mlib;

    float player_angle = atan2f(direction.y, direction.x);
    float fov_rad = FOV * M_PI / 180;
    float fov_start = player_angle - fov_rad / 2;
    float fov_end = player_angle + fov_rad / 2;
    float angle_step = fov_rad / 4;

    for (float angle = fov_start; angle <= fov_end; angle += angle_step)
    {
        float cos_angle = cosf(angle);
        float sin_angle = sinf(angle);
        t_vec end_point = {position.x + cos_angle * (window_width), position.y + sin_angle * (window_width ), 0.0f};


        result = draw_rays_3D(general, position.x, position.y, end_point.x, end_point.y);
        printVec(result);

    }
    printf("\n");
}




int render_game(t_general *general)
{
    t_mlib  *mlib = general->mlib;

    mlib->data.img_ptr = mlx_new_image(mlib->utils.mlx, WIDTH, HEIGHT);
    mlib->data.addr = mlx_get_data_addr(mlib->data.img_ptr, &mlib->data.bits_per_pixel, &mlib->data.line_length, &mlib->data.endian);

    //printf("%f %f\n", general->scene->player.pos.x,general->scene->player.pos.y);

    move(general);


    launch_mid_ray_3D(general);



    mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, mlib->data.img_ptr, 0, 0);
    mlx_destroy_image(mlib->utils.mlx, mlib->data.img_ptr);
    return (0);
}

