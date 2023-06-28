#include "../../header.h"

 t_vec create_ray(t_scene *scene, int pixel_x, int pixel_y)
{
    (void) scene;
    float aspect_ratio;
    t_vec dir;
    float dx; //increment x
    float dy; //increment y

    float d; //distance total


    d = 2.0f * tanf((float) FOV * 0.5f);
    dx = d / (float) WIDTH;
    
    aspect_ratio = (float) HEIGHT / (float) WIDTH;
    dy = dx * aspect_ratio;


    dir = (t_vec) {dx * pixel_x, dy * pixel_y, 1.0f};
    //dir = (t_vec) {d * (pixel_x / (float)WIDTH - 0.5f), d * (pixel_y / (float)HEIGHT - 0.5f) * aspect_ratio, 1.0f};
    dir = vec_normalize(dir);
    return (dir);
}

 int check_intesection(t_scene *scene, t_vec player_pos, t_vec dir)
{
    (void) scene;
    int hit;
    int i;
    int ngx; //next goal x
    int ngy; //next goal y

    (void) hit;
    (void) i;
    (void) ngx; //next goal x
    (void) ngy;



    if (dir.x > 0)
        ngx = (int) player_pos.x + 1;
    else
        ngx = (int) player_pos.x;
    if (dir.y > 0)
        ngy = (int) player_pos.y + 1;
    else
        ngy = (int) player_pos.y;
    hit = 0;
    i = 0;
    /*while (!hit && i < MAX_DISTANCE)
    {

    }*/
    return (0);
}

void draw_player(float x0, float y0, float x1, float y1, int color, int size_wall, t_mlib *mlib)
{
    int int_x0 = roundf(x0);
    int int_y0 = roundf(y0);
    int int_x1 = roundf(x1);
    int int_y1 = roundf(y1);

    my_mlx_pixel_put(&mlib->data, int_x0, int_y0, color);
    my_mlx_pixel_put(&mlib->data, int_x0 + 1, int_y0, color);
    my_mlx_pixel_put(&mlib->data, int_x0, int_y0 + 1, color);
    my_mlx_pixel_put(&mlib->data, int_x0, int_y0 - 1, color);
    my_mlx_pixel_put(&mlib->data, int_x0 - 1, int_y0, color);

    int i = 0;
    while (i < size_wall / 2)
    {
        if (int_y1 != 0)
            my_mlx_pixel_put(&mlib->data, int_x0, int_y0 + i * int_y1, color);        
        else
            my_mlx_pixel_put(&mlib->data, int_x0 + i * int_x1, int_y0, color);        
        i++;
    }
    
    my_mlx_pixel_put(&mlib->data, int_x0 + int_x1, int_y0 + int_y1, 0xFF0000);
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
            my_mlx_pixel_put(&mlib->data, pixel_x + x, pixel_y + y, 0xFF00FF);

            x++;
        }
        y++;
    }
    // printf("%d\n", mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, mlib->data.img_ptr, 0, 0));

}


int render(t_general *general)
{
    t_scene *scene = general->scene;
    t_mlib  *mlib = general->mlib;
    int size_wall;

    mlib->data.img_ptr = mlx_new_image(mlib->utils.mlx, WIDTH, HEIGHT);
    mlib->data.addr = mlx_get_data_addr(mlib->data.img_ptr, &mlib->data.bits_per_pixel, &mlib->data.line_length, &mlib->data.endian);
    if (scene->map.height_map > scene->map.width_map)
    {
        size_wall = HEIGHT / scene->map.height_map;
    }
    else
    {
        size_wall = WIDTH / scene->map.width_map;
    }

    //printf("size_wall = %d\n", size_wall);



    int i;
    int j;
    (void) i;

    j = 0;
    while (j < scene->map.height_map)
    {
        i = 0;
        while (i < scene->map.width_map)
        {
            if (scene->map.matrix[j][i] == '1')
            {
                draw_wall(i * size_wall, j * size_wall, size_wall, mlib);
            }
            else if (scene->map.matrix[j][i] == 'N')
            {   
                draw_player(scene->player.pos.x * size_wall + (size_wall * 0.5), scene->player.pos.y * size_wall + (size_wall * 0.5), general->scene->player.dir.x, general->scene->player.dir.y, 0x00FF00 , size_wall, mlib);
            }
            i++;
        }
        j++;
    }



    //mlx_sync(MLX_SYNC_IMAGE_WRITABLE, mlib->data.img_ptr);
    mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, mlib->data.img_ptr, 0, 0);
    mlx_destroy_image(mlib->utils.mlx, mlib->data.img_ptr);
    //mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, mlib->data.img_ptr);
    return (1);
}