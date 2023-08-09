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

float get_dist(t_coord pos, t_coord ray, float delta_angle)
{
    float dist;
    (void) delta_angle;

    dist = sqrtf((ray.x - pos.x)*(ray.x - pos.x) + (ray.y - pos.y)*(ray.y - pos.y));
    dist /= SIZE_WALL;
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

void    display_floor(t_mlib *mlib, int wall_height, int imageincre, unsigned int floor_color)
{
    for (int i = (HEIGHT + wall_height) / 2; i < HEIGHT; i++) {
        if (imageincre < WIDTH && i < HEIGHT) 
        {
            my_mlx_pixel_put(&mlib->data, imageincre, i, floor_color);
        }
    }
}

int pix_in_S (t_coord ray)
{
    return ray.y % SIZE_WALL == 0;
}

int pix_in_N (t_coord ray)
{
    return ray.y % SIZE_WALL == SIZE_WALL - 1;
}

int pix_in_E (t_coord ray)
{
    return ray.x % SIZE_WALL == 0;
}

int pix_in_W (t_coord ray)
{
    return ray.x % SIZE_WALL == SIZE_WALL - 1;
}


int text_in_N (t_coord ray, t_coord ray_bef)
{
    //(void) ray_bef;

    if (pix_in_N(ray) == 1 && pix_in_E(ray) == 1)
    {
        if (ray_bef.x == (int) (ray.x + 1) && ray_bef.y == (int) (ray.y + 1))
        {
            return (1);
        }
        else if (ray_bef.x == (int) ray.x && ray_bef.y == (int) (ray.y + 1))
        {
            return (1);
        }
        else if (ray_bef.x == (int)(ray.x - 1) && ray_bef.y == (int)(ray.y + 1))
        {
            return (0);
        }
        else if (ray_bef.x == (int)(ray.x - 1) && ray_bef.y == (int)(ray.y))
        {
            return (0);
        }
        else if (ray_bef.x == (int)(ray.x - 1) && ray_bef.y == (int)(ray.y - 1))
        {
            return (0);
        }
    }

    if (pix_in_N(ray) == 1 && pix_in_W(ray) == 1)
    {
        if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y - 1)
        {
            return (0);
        }
        else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y)
        {
            return (0);
        }
        else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y + 1)
        {
            return (1);
        }
        else if (ray_bef.x == ray.x && ray_bef.y == ray.y + 1)
        {
            return (1);
        }
        else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y + 1)
        {
            return (1);
        }
    }

    return pix_in_N(ray);
}

int text_in_S (t_coord ray, t_coord ray_bef)
{

    if (pix_in_S(ray) == 1 && pix_in_E(ray) == 1)
    {
        if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y + 1)
        {
            return (0);
        }
        else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y)
        {
            return (0);
        }
        else if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y - 1)
        {
            return (0);
        }
        else if (ray_bef.x == ray.x && ray_bef.y == ray.y - 1)
        {
            return (1);
        }
        else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y - 1)
        {
            return (1);
        }
    }

    if (pix_in_S(ray) == 1 && pix_in_W(ray) == 1)
    {

        if (ray_bef.x == ray.x - 1 && ray_bef.y == ray.y - 1)
        {
            return (1);
        }
        else if (ray_bef.x == ray.x && ray_bef.y == ray.y - 1)
        {
            return (1);
        }
        else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y - 1)
        {
            return (1);
        }
        else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y)
        {
            return (0);
        }
        else if (ray_bef.x == ray.x + 1 && ray_bef.y == ray.y + 1)
        {
            return (0);
        }

    }


    return ray.y % SIZE_WALL == 0;
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
    t_vec   direction = general->scene->player.dir;
    t_coord ray;
    t_coord ray_bef;
    float dist = 0;
    int imageincre = 0;


    
    float player_angle;

    player_angle = atan2f(direction.y, direction.x);


    float fov_rad = M_PI / 3;
    float fov_start = (player_angle - fov_rad / 2);
    float fov_end = (player_angle + fov_rad / 2);




   // double angle_step = fov_rad / WIDTH;

    //printf("fov_start = %f fov_end = %f player_angle = %f\n", fov_start, fov_end, player_angle);


    for (int i = 0; i < WIDTH; i++)
    {
        double angle = fov_start + (fov_end - fov_start) * i / WIDTH;
        double cos_angle = cos(angle);
        double sin_angle = sin(angle);
        t_vec end_point = {position.x + cos_angle * 200000, position.y + sin_angle * 200000, 0.0f}; // ?
        
        t_tab result = find_point_on_screen(general, position, (t_coord){round(end_point.x), round(end_point.y), 0});

        /*printf("Player position (%d, %d)\n", general->scene->player.pos.x, general->scene->player.pos.y);
        printf("Wall at (%f, %f)\n", result.v2.x, result.v2.y);*/
        /* h = 768 w = 1280 
        Coord x = 1216 y = 564 z = 0
        Coord x = 1216 y = 569 z = 0
        */

        ray = result.v2;
        ray_bef = result.v1;
        int wall_height;

        float prec_dist;

        prec_dist = dist;
        
        //printCoord(ray);

        dist = get_dist(position, result.v2, angle - player_angle);

        // if ((int) (prec_dist * 100) > (int) (dist * 100))
        // {
        //     printf("+ ");
        // }
        // else if ((int) (prec_dist * 100) == (int) (dist * 100))
        // {
        //     printf("= ");
        // }
        // else
        // {
        //     printf("- ");
        // }

        
        // if (imageincre == 800)        
        //     printf("Distance = %f\n", dist);


    
        //if (dist > 1.5f)
        wall_height = round((float)(WIDTH) / (float)dist);
        // else
        //     wall_height = HEIGHT;



        // if (imageincre == 800)
        //     printf("w_h = %d\n", wall_height);


        display_sky(general->mlib, wall_height, imageincre, SKY_COLOR);
        display_floor(general->mlib, wall_height, imageincre, general->scene->floor_color);
        //t_coord test = (t_coord){(int)(result.v3.x), (int)(result.v3.y), 0};

        //printCoord(ray_bef);
        if (text_in_S(ray, ray_bef))
        {
            draw_3D_line_south(general,  result.v2, wall_height, imageincre);
        }
        else if (text_in_N (ray, ray_bef))
        {
            draw_3D_line_north(general,  result.v2, wall_height, imageincre);
        }
        else if (pix_in_E(ray))
        {
            draw_3D_line_east(general, result.v2, wall_height, imageincre);
        }
        else if (pix_in_W(ray))
        {
            draw_3D_line_west(general, result.v2, wall_height, imageincre);
        }

        

            
        imageincre++;

        // if (imageincre != i)
        // {
        //     printf("imgincr = %d i = %d\n", imageincre, i);
        // }

    }
    //exit(42);

}

int render_game(t_general *general)
{
    t_mlib  *mlib = general->mlib;

    mlib->data.img_ptr = mlx_new_image(mlib->utils.mlx, WIDTH, HEIGHT);
    mlib->data.addr = mlx_get_data_addr(mlib->data.img_ptr, &mlib->data.bits_per_pixel, &mlib->data.line_length, &mlib->data.endian);


    trace_ray(general);
    move(general);

    mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, mlib->data.img_ptr, 0, 0);
    mlx_destroy_image(mlib->utils.mlx, mlib->data.img_ptr);
    return (0);
}

