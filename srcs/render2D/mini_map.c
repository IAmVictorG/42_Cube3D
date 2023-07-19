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
    

    relative_pos.x = abs(x1 - position.x);
    relative_pos.y = abs(y1 - position.y);

    int sx = (position.x < x1) ? 1 : -1;
    int sy = (position.y < y1) ? 1 : -1;
    int err = relative_pos.x - relative_pos.y;


    while (42) 
    {
        // Ensure the pixel coordinates are within window bounds
        if (position.x >= 0 && position.x < WIDTH && position.y >= 0 && position.y < HEIGHT) 
        {
            if (hit_a_wall(general,position.x, position.y) == 0)
            {
                my_mlx_pixel_put(&mlib->data, position.x, position.y, 0xFF0000);
            }
            else
            {
                printf("first\n");
                break;
            }
        }
        else
        {
            printf("second\n");
            break;
        }

        // if (position.x == x1 && position.y == y1)
        // {
        //     printf("third\n");
        //     break;
        // }
        int e2 = 2 * err;
        if (e2 > -relative_pos.y)
        {
            err -= relative_pos.y;
            position.x += sx;
        }
        else if (e2 < relative_pos.x) 
        {
            err += relative_pos.x;
            position.y += sy;
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



    player_angle = atan2f(direction.y, direction.x);


    cos_angle = cosf(player_angle);
    sin_angle = sinf(player_angle);

    end_point.x = position.x + cos_angle * (WIDTH);
    end_point.y = position.y + sin_angle * (WIDTH);
    end_point.z = 0.0f;

    fov_rad = FOV * M_PI / 180;
    fov_start = player_angle - fov_rad / 2;
    fov_end = player_angle + fov_rad / 2;
    angle_step = fov_rad / 100;




    for (angle = fov_start; angle <= fov_end; angle += angle_step)
    {
        cos_angle = cosf(angle);
        sin_angle = sinf(angle);
        end_point.x = position.x + cos_angle * (WIDTH);
        end_point.y = position.y + sin_angle * (WIDTH);
        end_point.z = 0.0f;
        draw_rays(general, position, end_point.x, end_point.y);
    }
}

float   rad_to_deg(float angle)
{
    return ((angle * 180)/M_PI);
}

float   deg_to_rad(float angle)
{
    return ((angle * M_PI) / 180);
}

void    draw_ray2(t_general *general)
{
    /*Il faut ecrire a nouveau draw_ray en parcourant
    la range de x jusqu'au bord de la fenetre
    OU
    la range de y jusqu au bord de la fenetre
    penser a utiliser la trigonometrie
    
    */
    t_mlib *mlib;
    mlib = general->mlib;

    t_coord position = general->scene->player.pos;
    int     x_pix = general->scene->player.pos.x;
    int     y_pix = general->scene->player.pos.y;

    float   y_pix_f;
    float   x_pix_f;

    t_vec   direction = general->scene->player.dir;
    float   angle_player;
    float   x_div_y = 0;
    float   y_div_x = 0;


    if (direction.x > 0 && direction.y > 0)
    {
        angle_player = atan2f(direction.y, direction.x);
        //printf("SW ");
        //printf("angle_player = %f (%f)\n", angle_player, rad_to_deg(angle_player));
        y_div_x = direction.y / direction.x;
        x_div_y = direction.x / direction.y;

        //printf("y_div_x = %f x_div_y = %f\n", y_div_x, x_div_y);

        while (x_pix < WIDTH && y_pix < HEIGHT)
        {
            y_pix_f = (x_pix - position.x) * y_div_x + position.y;
            x_pix_f = (y_pix - position.y) * x_div_y + position.x;

            if (y_pix_f < HEIGHT)
            {
                my_mlx_pixel_put(&mlib->data, x_pix, y_pix_f, 0xFF0000);
            }

            if (x_pix_f < WIDTH)
            {
                my_mlx_pixel_put(&mlib->data, x_pix_f, y_pix, 0xFF0000);
            }



            x_pix++;
            y_pix++;
        }
        //exit(42);


    }

    if (direction.x < 0 && direction.y < 0)
    {
        angle_player = atan2f(direction.y, direction.x);
        printf("NE ");
        printf("angle_player = %f (%f)\n", angle_player, rad_to_deg(angle_player));


    }

    if (direction.x > 0 && direction.y < 0)
    {
        angle_player = atan2f(direction.y, direction.x);
        printf("NW ");
        printf("angle_player = %f (%f)\n", angle_player, rad_to_deg(angle_player));

    }

    if (direction.x < 0 && direction.y > 0)
    {
        angle_player = atan2f(direction.y, direction.x);
        printf("SE ");
        printf("angle_player = %f (%f)\n", angle_player, rad_to_deg(angle_player));

    }


//    t_coord range;

//     int x;
//     int y;

//     int range;

//     if (WIDTH - position.x < HEIGHT - position.y)
//     {
//         range = WIDTH - position.x;
//         while (position.x < range)
//         {
            


//             position.x++;
//         }



//     }
//     else
//     {
//         range = HEIGHT - position.y;
//     }



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
    //draw_ray2(general);
    draw_player(general);
    
    //mlx_sync(MLX_SYNC_IMAGE_WRITABLE, mlib->data.img_ptr);
    mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, mlib->data.img_ptr, 0, 0);
    mlx_destroy_image(mlib->utils.mlx, mlib->data.img_ptr);
    //mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, mlib->data.img_ptr);
    return (0);
}