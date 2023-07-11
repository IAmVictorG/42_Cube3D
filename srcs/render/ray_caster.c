#include "../../header.h"
/*
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
}*/

void draw_3D_line_west(t_general *general, t_vec ray, int wall_height, int imageincre)
{
    int             i;
    int             x_int;
    unsigned int    color;


    for (i = 0; i < wall_height; i++)
    {
        x_int = (int) roundf(ray.y);
        color = get_color_wall_west(general, x_int, i, wall_height);
        my_mlx_pixel_put(&general->mlib->data, imageincre, (HEIGHT - wall_height) / 2 + i, color);
    }
}

void draw_3D_line_east(t_general *general, t_vec ray, int wall_height, int imageincre)
{
    int             i;
    int             x_int;
    unsigned int    color;

    for (i = 0; i < wall_height; i++)
    {
        x_int = (int) roundf(ray.y);
        color = get_color_wall_east(general, x_int, i, wall_height);
        my_mlx_pixel_put(&general->mlib->data, imageincre, (HEIGHT - wall_height) / 2 + i, color);
    } 
}

void draw_3D_line_south(t_general *general, t_vec ray, int wall_height, int imageincre)
{

    int             i;
    int             x_int;
    unsigned int    color;


    for (i = 0; i < wall_height; i++)
    {
        x_int = (int) roundf(ray.x);
        color = get_color_wall_south(general, x_int, i, wall_height);
        my_mlx_pixel_put(&general->mlib->data, imageincre, (HEIGHT - wall_height) / 2 + i, color);
    } 
}


void draw_3D_line_north(t_general *general, t_vec ray, int wall_height, int imageincre)
{
    int i;
    int x_int;
    unsigned int color;

    for (i = 0; i < wall_height; i++)
    {
        x_int = (int) roundf(ray.x);
        color = get_color_wall_north(general, x_int, i, wall_height);
        my_mlx_pixel_put(&general->mlib->data, imageincre, (HEIGHT - wall_height) / 2 + i, color);
    }
}

void trace_ray(t_general *general) 
{

    t_vec position = general->scene->player.pos;
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

    for (float angle = fov_start; angle <= fov_end; angle += angle_step)
    {
        float cos_angle = cosf(angle);
        float sin_angle = sinf(angle);
        t_vec end_point = {position.x + cos_angle * (window_width), position.y + sin_angle * (window_width ), 0.0f};

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

int convert_char_to_int(char *color)
{

    return (*color << 24 | *(color + 1) << 16 | *(color + 2) << 8 | *(color + 3));


}


void load_texture(t_general *general)
{    
    t_sprites *sprites = general->sprites;

    sprites->wall_north->data_spr.img_ptr = mlx_xpm_file_to_image(general->mlib->utils.mlx, "sprites/Wall_North.xpm", &sprites->wall_north->sprite_w , &sprites->wall_north->sprite_h);
    sprites->wall_north->data_spr.addr = mlx_get_data_addr(sprites->wall_north->data_spr.img_ptr, &sprites->wall_north->data_spr.bits_per_pixel, &sprites->wall_north->data_spr.line_length, &sprites->wall_north->data_spr.endian); /* devrait etre un pointeur */
    
    sprites->wall_south->data_spr.img_ptr = mlx_xpm_file_to_image(general->mlib->utils.mlx, "sprites/Wall_South.xpm", &sprites->wall_south->sprite_w , &sprites->wall_south->sprite_h);
    sprites->wall_south->data_spr.addr = mlx_get_data_addr(sprites->wall_south->data_spr.img_ptr, &sprites->wall_south->data_spr.bits_per_pixel, &sprites->wall_south->data_spr.line_length, &sprites->wall_south->data_spr.endian); /* devrait etre un pointeur */

    sprites->wall_east->data_spr.img_ptr = mlx_xpm_file_to_image(general->mlib->utils.mlx, "sprites/Wall_East.xpm", &sprites->wall_east->sprite_w , &sprites->wall_east->sprite_h);
    sprites->wall_east->data_spr.addr = mlx_get_data_addr(sprites->wall_east->data_spr.img_ptr, &sprites->wall_east->data_spr.bits_per_pixel, &sprites->wall_east->data_spr.line_length, &sprites->wall_east->data_spr.endian); /* devrait etre un pointeur */

    sprites->wall_west->data_spr.img_ptr = mlx_xpm_file_to_image(general->mlib->utils.mlx, "sprites/Wall_West.xpm", &sprites->wall_west->sprite_w , &sprites->wall_west->sprite_h);
    sprites->wall_west->data_spr.addr = mlx_get_data_addr(sprites->wall_west->data_spr.img_ptr, &sprites->wall_west->data_spr.bits_per_pixel, &sprites->wall_west->data_spr.line_length, &sprites->wall_west->data_spr.endian); /* devrait etre un pointeur */
}


void    trace_wall(t_general *general, t_sprite *sprite)
{
    int h = sprite->sprite_h;
    int w = sprite->sprite_w;

    int i;
    int j;
    char *color;

    //printf("h = %d & w = %d\n", h,w);

    j = 0;
    while (j < h)
    {
        i = 0;
        while (i < w)
        {
            color = sprite->data_spr.addr + j * sprite->data_spr.line_length + i * sprite->data_spr.bits_per_pixel / 8;
            my_mlx_pixel_put(&general->mlib->data, i,j, *(unsigned int *)color);
            i++;
        }
        j++;
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

