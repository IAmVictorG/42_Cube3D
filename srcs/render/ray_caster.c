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

void trace_ray(t_general *general) {
    //printf("RAY\n");
    t_vec position = general->scene->player.pos;
    t_vec direction = general->scene->player.dir;
    t_vec ray;

    int size_wall = general->scene->map.size_wall;
    int window_width = WIDTH;
    int window_height = HEIGHT;

    //t_mlib *mlib = general->mlib;

    float player_angle = atan2f(direction.y, direction.x);
    float fov_rad = FOV * M_PI / 180;
    float fov_start = player_angle - fov_rad / 2;
    float fov_end = player_angle + fov_rad / 2;

    float angle_step = fov_rad / 400;

    for (float angle = fov_start; angle <= fov_end; angle += angle_step)
    {
        float cos_angle = cosf(angle);
        float sin_angle = sinf(angle);
        t_vec end_point = {position.x + cos_angle * (window_width), position.y + sin_angle * (window_width ), 0.0f};



        //if (end_point.x >= window_width) end_point.x = window_width - 1;
        //if (end_point.y >= window_height) end_point.y = window_height - 1;

        ray = draw_rays(general, position.x, position.y, end_point.x, end_point.y, size_wall, window_width, window_height);
        printf("Ray : %d, %d\n", (int) ray.x, (int) ray.y);
        for (int i = 0; i < 200; i++)
        {
            my_mlx_pixel_put(&general->mlib->data, (int) ray.y, i + HEIGHT / 3, 0x00FF00);
            
        }
        
    }
}

int render_game(t_general *general)
{
    t_mlib  *mlib = general->mlib;

    mlib->data.img_ptr = mlx_new_image(mlib->utils.mlx, WIDTH, HEIGHT);
    mlib->data.addr = mlx_get_data_addr(mlib->data.img_ptr, &mlib->data.bits_per_pixel, &mlib->data.line_length, &mlib->data.endian);

    /*printf("0,0\n");
    create_ray(general->scene, 0, 0);
    printf("%d,0\n", WIDTH);
    create_ray(general->scene, WIDTH, 0);
    printf("0,%d\n", HEIGHT);
    create_ray(general->scene, 0, HEIGHT);
    printf("%d,%d\n", WIDTH, HEIGHT);
    create_ray(general->scene, WIDTH, HEIGHT);*/
    trace_ray(general);
    move(general);
    mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, mlib->data.img_ptr, 0, 0);
    mlx_destroy_image(mlib->utils.mlx, mlib->data.img_ptr);
    return (0);
}

