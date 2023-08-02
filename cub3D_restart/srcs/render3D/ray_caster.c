#include "render3D.h"
t_tab find_point_on_screen(t_general *general, t_coord c0, t_coord c1);

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


        // if (x0 == x1 && y0 == y1)   
        //     break;
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

t_vec calculate_rays_bef(t_general *general, int x0, int y0, int x1, int y1, int size_wall, int window_width, int window_height) 
{
    //t_mlib *mlib;

    t_vec r_temp;

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

        r_temp.x = x0;
        r_temp.y = y0;

        // if (x0 == x1 && y0 == y1)   
        //     break;
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

    return (r_temp);
}

float get_dist(t_coord pos, t_vec ray, float delta_angle, int size_wall)
{
    float dist;
    (void) delta_angle;

    dist = sqrtf((ray.x - pos.x)*(ray.x - pos.x) + (ray.y - pos.y)*(ray.y - pos.y));
    dist /= size_wall;
    dist *= cos(delta_angle);


    return dist;
}

void    display_sky(t_mlib *mlib, int wall_height, int imageincre, unsigned int sky_color)
{
    for (int i = 0; i < (HEIGHT - wall_height) / 2; i++)
    {
        if (imageincre < WIDTH && i < HEIGHT) 
        {
            my_mlx_pixel_put(&mlib->data, imageincre, i, sky_color);
        }
    }
}

void    display_floor(t_mlib *mlib, int wall_height, int imageincre)
{
    for (int i = (HEIGHT + wall_height) / 2; i < HEIGHT; i++) {
        if (imageincre < WIDTH && i < HEIGHT) 
        {
            my_mlx_pixel_put(&mlib->data, imageincre, i, FLOOR_COLOR);
        }
    }
}

int pix_in_S (t_vec ray, int size_wall)
{
    return (int) ray.y % size_wall == 0;
}

int pix_in_N (t_vec ray, int size_wall)
{
    return (int) ray.y % size_wall == size_wall - 1;
}

int pix_in_E (t_vec ray, int size_wall)
{
    return (int) ray.x % size_wall == 0;
}

int pix_in_W (t_vec ray, int size_wall)
{
    return (int) ray.x % size_wall == size_wall - 1;
}

float    atan2f_to_ortho(t_vec  direction)
{
    float angle_relative;

    angle_relative = atan2f(direction.y, direction.x);

    if (angle_relative < 0)
    {
        return (angle_relative * (-1));
    }

    return (2 * M_PI - angle_relative);

}


void trace_ray(t_general *general) 
{
    t_coord position = general->scene->player.pos;
    t_vec direction = general->scene->player.dir;
    t_vec ray;
    t_vec ray_bef;

    int imageincre = 0;
    int size_wall = general->scene->map.size_wall;

    
    float player_angle;

    player_angle = atan2f(direction.y, direction.x);


    float fov_rad = FOV * M_PI / 180;
    float fov_start = (player_angle - fov_rad / 2);
    float fov_end = (player_angle + fov_rad / 2);




    float angle_step = fov_rad / WIDTH;

    //printf("fov_start = %f fov_end = %f player_angle = %f\n", fov_start, fov_end, player_angle);


    for (double angle = fov_start; angle <= fov_end; angle += angle_step)
    {
        double cos_angle = cos(angle);
        double sin_angle = sin(angle);
        t_vec end_point = {position.x + cos_angle * 2000000, position.y + sin_angle * 2000000, 0.0f}; // ?

        t_tab result = find_point_on_screen(general, (t_coord){position.x, position.y, 0}, (t_coord){end_point.x, end_point.y, 0});


        ray = result.v2;
        ray_bef = result.v1;
        int wall_height;
        float dist;

        dist = get_dist(position, result.v3, angle - player_angle, size_wall);
        wall_height = WIDTH / dist;
        if (dist <= 1.0f)
        {
  
            draw_3D_line_south_near(general, result.v3, imageincre, dist);
            /*if (pix_in_S(ray, size_wall) == 1)
            {
            }

            if ((int) ray.y % size_wall == size_wall - 1)
            {
                draw_3D_line_north_near(general, result.v3, imageincre, dist);                 
            }

            if ((int) ray.x % size_wall == 0)
            {
                draw_3D_line_east_near(general, result.v3, imageincre, dist);
            }
            
            if ((int) ray.x % size_wall == size_wall - 1)
            {
                draw_3D_line_west_near(general, result.v3, imageincre, dist);
            }  


            if (pix_in_N(ray, size_wall) == 1 && pix_in_E(ray, size_wall) == 1)
            {

                if (ray_bef.x == (int) (ray.x + 1) && ray_bef.y == (int) (ray.y + 1))
                {
                    draw_3D_line_north_near(general, result.v3, imageincre, dist);
                }
                else if (ray_bef.x == (int) ray.x && ray_bef.y == (int) (ray.y + 1))
                {
                    draw_3D_line_north_near(general, result.v3, imageincre, dist);
                }
                else if (ray_bef.x == (int)(ray.x - 1) && ray_bef.y == (int)(ray.y + 1))
                {
                    draw_3D_line_east_near(general, result.v3, imageincre, dist);
                }
                else if (ray_bef.x == (int)(ray.x - 1) && ray_bef.y == (int)(ray.y))
                {
                    draw_3D_line_east_near(general, result.v3, imageincre, dist);
                }
                else if (ray_bef.x == (int)(ray.x - 1) && ray_bef.y == (int)(ray.y - 1))
                {
                    draw_3D_line_east_near(general, result.v3, imageincre, dist);
                }


            }

 
            if (pix_in_N(ray, size_wall) == 1 && pix_in_W(ray, size_wall) == 1)
            {

                if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y - 1)
                {
                    draw_3D_line_west_near(general, result.v3, imageincre, dist);
                }
                else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y)
                {
                    draw_3D_line_west_near(general, result.v3, imageincre, dist);
                }
                else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y + 1)
                {
                    draw_3D_line_north_near(general, result.v3, imageincre, dist);
                }
                else if (ray_bef.x == ray.x && ray_bef.y == ray.y + 1)
                {
                    draw_3D_line_north_near(general, result.v3, imageincre, dist);
                }
                else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y + 1)
                {
                    draw_3D_line_north_near(general, result.v3, imageincre, dist);
                }

            }

            if (pix_in_S(ray, size_wall) == 1 && pix_in_E(ray, size_wall) == 1)
            {

                if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y + 1)
                {
                    draw_3D_line_east_near(general, result.v3, imageincre, dist);
                }
                else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y)
                {
                    draw_3D_line_east_near(general, result.v3, imageincre, dist);
                }
                else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y - 1)
                {
                    draw_3D_line_south_near(general, result.v3, imageincre, dist);
                }
                else if (ray_bef.x == ray.x && ray_bef.y == ray.y - 1)
                {
                    draw_3D_line_south_near(general, result.v3, imageincre, dist);
                }
                else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y - 1)
                {
                    draw_3D_line_south_near(general, result.v3, imageincre, dist);
                }

            }

            if (pix_in_S(ray, size_wall) == 1 && pix_in_W(ray, size_wall) == 1)
            {

                if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y - 1)
                {
                    draw_3D_line_south_near(general, result.v3, imageincre, dist);
                }
                else if (ray_bef.x == ray.x && ray_bef.y == ray.y - 1)
                {
                    draw_3D_line_south_near(general, result.v3, imageincre, dist);
                }
                else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y - 1)
                {
                    draw_3D_line_south_near(general, result.v3, imageincre, dist);
                }
                else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y)
                {
                    draw_3D_line_west_near(general, result.v3, imageincre, dist);
                }
                else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y + 1)
                {
                    draw_3D_line_west_near(general, result.v3, imageincre, dist);
                }

            }*/

        }
        else
        {

            wall_height = WIDTH / dist;

            display_sky(general->mlib, wall_height, imageincre, SKY_COLOR);
            display_floor(general->mlib, wall_height, imageincre);
            draw_3D_line_south(general, result.v3, wall_height, imageincre);
            //draw_3D_line_south(general, result.v3, imageincre, wall_height);
            //float angle_to_corner = atan2f(ray.y - position.y, ray.x - position.x);


            /*if (pix_in_S(ray, size_wall) == 1)
            {
                //printf("S viewing_angle = %f\n", viewing_angle);

                draw_3D_line_south(general, result.v3, wall_height, imageincre);
            }
            
            if (pix_in_E(ray, size_wall) == 1)
            {
                //printf("E viewing_angle = %f\n", viewing_angle);

                draw_3D_line_east(general, result.v3, wall_height, imageincre);
            }
            
            if (pix_in_N(ray, size_wall) == 1)
            {
                //printf("N viewing_angle = %f\n", viewing_angle);


                draw_3D_line_north(general, result.v3, wall_height, imageincre);                 
            }

            if (pix_in_W(ray, size_wall) == 1)
            {


                draw_3D_line_west(general, result.v3, wall_height, imageincre);
            }




            if (pix_in_N(ray, size_wall) == 1 && pix_in_E(ray, size_wall) == 1)
            {

                if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y + 1)
                {
                    draw_3D_line_north(general, result.v3, wall_height, imageincre);
                }
                else if (ray_bef.x == ray.x && ray_bef.y == ray.y + 1)
                {
                    draw_3D_line_north(general, result.v3, wall_height, imageincre);
                }
                else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y + 1)
                {
                    draw_3D_line_east(general, result.v3, wall_height, imageincre);
                }
                else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y)
                {
                    draw_3D_line_east(general, result.v3, wall_height, imageincre);
                }
                else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y - 1)
                {
                    draw_3D_line_east(general, result.v3, wall_height, imageincre);
                }


            }

 
            if (pix_in_N(ray, size_wall) == 1 && pix_in_W(ray, size_wall) == 1)
            {

                if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y - 1)
                {
                    draw_3D_line_west(general, result.v3, wall_height, imageincre);
                }
                else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y)
                {
                    draw_3D_line_west(general, result.v3, wall_height, imageincre);
                }
                else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y + 1)
                {
                    draw_3D_line_north(general, result.v3, wall_height, imageincre);
                }
                else if (ray_bef.x == ray.x && ray_bef.y == ray.y + 1)
                {
                    draw_3D_line_north(general, result.v3, wall_height, imageincre);
                }
                else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y + 1)
                {
                    draw_3D_line_north(general, result.v3, wall_height, imageincre);
                }





            }

            if (pix_in_S(ray, size_wall) == 1 && pix_in_E(ray, size_wall) == 1)
            {

                if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y + 1)
                {
                    draw_3D_line_east(general, result.v3, wall_height, imageincre);
                }
                else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y)
                {
                    draw_3D_line_east(general, result.v3, wall_height, imageincre);
                }
                else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y - 1)
                {
                    draw_3D_line_south(general, result.v3, wall_height, imageincre);
                }
                else if (ray_bef.x == ray.x && ray_bef.y == ray.y - 1)
                {
                    draw_3D_line_south(general, result.v3, wall_height, imageincre);
                }
                else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y - 1)
                {
                    draw_3D_line_south(general, result.v3, wall_height, imageincre);
                }




            }

            if (pix_in_S(ray, size_wall) == 1 && pix_in_W(ray, size_wall) == 1)
            {

                if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y - 1)
                {
                    draw_3D_line_south(general, result.v3, wall_height, imageincre);
                }
                else if (ray_bef.x == ray.x && ray_bef.y == ray.y - 1)
                {
                    draw_3D_line_south(general, result.v3, wall_height, imageincre);
                }
                else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y - 1)
                {
                    draw_3D_line_south(general, result.v3, wall_height, imageincre);
                }
                else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y)
                {
                    draw_3D_line_west(general, result.v3, wall_height, imageincre);
                }
                else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y + 1)
                {
                    draw_3D_line_west(general, result.v3, wall_height, imageincre);
                }
            }*/
        }
        imageincre++;
    }
    //exit(42);dd
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

