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

void draw_player(int x0, int y0, int x1, int y1, int color, int size_wall, t_mlib *mlib)
{
    (void) x1;
    (void) y1;

    my_mlx_pixel_put(&mlib->data, x0, y0, color);
    my_mlx_pixel_put(&mlib->data, x0 + 1, y0, color);
    my_mlx_pixel_put(&mlib->data, x0, y0 + 1, color);
    my_mlx_pixel_put(&mlib->data, x0, y0 - 1, color);
    my_mlx_pixel_put(&mlib->data, x0 - 1, y0, color);
    int i;
    
    i = 0;
    while (i < size_wall / 2)
    {
        if (y1 != 0)
            my_mlx_pixel_put(&mlib->data, x0, y0 + i * y1, color);        
        else
            my_mlx_pixel_put(&mlib->data, x0 + i * x1, y0, color);        
        i++;
    }
    
    my_mlx_pixel_put(&mlib->data, x0 + x1, y0 + y1, 0xFF0000);



    //my_mlx_pixel_put(&mlib->data, i * size_wall + (size_wall * 0.5), j * size_wall + (size_wall * 0.5), 0x00FF00);

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

}


int render(t_general *general)
{
    printf("RENDER\n");
    //(void) general;
    //t_scene *scene = general->scene;
    //t_mlib  *mlib = general->mlib;

    //(void) scene;
    //(void) mlib;

    /*
    int size_wall;

    if (scene->map.height_map > scene->map.width_map)
    {
        size_wall = HEIGHT / scene->map.height_map;
    }
    else
    {
        size_wall = WIDTH / scene->map.width_map;
    }

    printf("size_wall = %d\n", size_wall);

    int i;
    int j;
    (void) i;

    j = 0;
    while (j < scene->map.height_map)
    {
       // printf("%s", scene->map.matrix[j]);
        i = 0;
        while (i < scene->map.width_map)
        {
            if (scene->map.matrix[j][i] == '1')
            {
                //printf("%c", scene->map.matrix[j][i]);
                draw_wall(i * size_wall, j * size_wall, size_wall, mlib);
            }
            else if (scene->map.matrix[j][i] == 'N')
            {   
                printf("NNNNNNNNNNNNNN\n");
                //draw_wall(i * size_wall, j * size_wall, size_wall, mlib);
                draw_player(scene->player.pos.x * size_wall + (size_wall * 0.5), scene->player.pos.y * size_wall + (size_wall * 0.5), 1, 0, 0x00FF00 , size_wall, mlib);
               // my_mlx_pixel_put(&mlib->data, i * size_wall + (size_wall * 0.5), j * size_wall + (size_wall * 0.5), 0x00FF00);
            }
            i++;
        }
        printf("\n");
        j++;
    }

    printf("3");


    // (void) scene;

    // for (int i = 0; i < WIDTH; i++) 
    // {
    //     for (int j = 0; j < HEIGHT; j++) 
    //     {
    //         t_vec dir = create_ray(scene, i, j);
    //         my_mlx_pixel_put(&mlib->data, i, j, 0xFF00FF);
    //         (void) dir;
    //     }
    // }
    printf("%d\n", mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, mlib->data.img_ptr, 0, 0));*/
    
    return (1);
}