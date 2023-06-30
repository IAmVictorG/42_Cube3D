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

void move(t_general *general)
{
    float pos_x;
    float pos_y;

    if (general->keys->s == 1)
    {
        pos_x = general->scene->player.pos.x - general->scene->player.speed * general->scene->player.dir.x;
        pos_y = general->scene->player.pos.y - general->scene->player.speed * general->scene->player.dir.y;
        
        if (position_is_valid(general, pos_x, pos_y) == 1)
        {
            general->scene->player.pos.x = pos_x;
            general->scene->player.pos.y = pos_y;
        }
        //print_player(general->scene->player);
    }
    if (general->keys->w == 1)
    {
        pos_x = general->scene->player.pos.x + general->scene->player.speed * general->scene->player.dir.x;
        pos_y = general->scene->player.pos.y + general->scene->player.speed * general->scene->player.dir.y;

        if (position_is_valid(general,pos_x, pos_y) == 1)
        {
            general->scene->player.pos.x = pos_x;
            general->scene->player.pos.y = pos_y;
        }
        //print_player(general->scene->player);
    }
    if (general->keys->a == 1)
    {
        pos_x = general->scene->player.pos.x - general->scene->player.speed * general->scene->player.dir.y * -1;
        pos_y = general->scene->player.pos.y - general->scene->player.speed * general->scene->player.dir.x;


        if (position_is_valid(general,pos_x, pos_y) == 1)
        {
            general->scene->player.pos.x = pos_x;
            general->scene->player.pos.y = pos_y;
        }

        //print_player(general->scene->player);
    }
    if (general->keys->d == 1)
    {
        pos_y = general->scene->player.pos.y + general->scene->player.speed * general->scene->player.dir.x;
        pos_x = general->scene->player.pos.x + general->scene->player.speed * general->scene->player.dir.y * -1;

        if (position_is_valid(general, pos_x, pos_y) == 1)
        {
            general->scene->player.pos.x = pos_x;
            general->scene->player.pos.y = pos_y;
        }

        //print_player(general->scene->player);

    }

    //Changement de direction player
    if (general->keys->q == 1)
    {
        float angle = atan2f(general->scene->player.dir.y, general->scene->player.dir.x);
        angle -= ROTATION_SPEED;
        general->scene->player.dir.x = cosf(angle);
        general->scene->player.dir.y = sinf(angle);
        //print_player(general->scene->player);

    }
    if (general->keys->r == 1)
    {
        float angle = atan2f(general->scene->player.dir.y, general->scene->player.dir.x);
        angle += ROTATION_SPEED;
        general->scene->player.dir.x = cosf(angle);
        general->scene->player.dir.y = sinf(angle);
       // print_player(general->scene->player);

    }
    if (general->keys->arrow_l == 1)
    {
        float angle = atan2f(general->scene->player.dir.y, general->scene->player.dir.x);
        angle -= ROTATION_SPEED;
        general->scene->player.dir.x = cosf(angle);
        general->scene->player.dir.y = sinf(angle);
        //print_player(general->scene->player);

    }
    if (general->keys->arrow_r == 1)
    {
        float angle = atan2f(general->scene->player.dir.y, general->scene->player.dir.x);
        angle += ROTATION_SPEED;
        general->scene->player.dir.x = cosf(angle);
        general->scene->player.dir.y = sinf(angle);
        //print_player(general->scene->player);
    }
}


int render_game(t_general *general)
{
    t_mlib  *mlib = general->mlib;

    mlib->data.img_ptr = mlx_new_image(mlib->utils.mlx, WIDTH, HEIGHT);
    mlib->data.addr = mlx_get_data_addr(mlib->data.img_ptr, &mlib->data.bits_per_pixel, &mlib->data.line_length, &mlib->data.endian);

    mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, mlib->data.img_ptr, 0, 0);
    mlx_destroy_image(mlib->utils.mlx, mlib->data.img_ptr);
    return (0);
}

