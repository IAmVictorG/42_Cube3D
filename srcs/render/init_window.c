#include "../../header.h"

int position_is_valid(t_general *general, float pos_x, float pos_y)
{
    int player_size;
    int i;
    
    player_size = 1;
    int corners[4][2] = {
        {(int)((pos_x - player_size) / general->scene->map.size_wall), (int)((pos_y - player_size) / general->scene->map.size_wall)},
        {(int)((pos_x + player_size) / general->scene->map.size_wall), (int)((pos_y - player_size) / general->scene->map.size_wall)},
        {(int)((pos_x - player_size) / general->scene->map.size_wall), (int)((pos_y + player_size) / general->scene->map.size_wall)},
        {(int)((pos_x + player_size) / general->scene->map.size_wall), (int)((pos_y + player_size) / general->scene->map.size_wall)}
    };

    i = 0;
    while (i < 4)
    {
        //printf("Corner %d: x = %d, y = %d\n", i, corners[i][0], corners[i][1]);
        if (general->scene->map.matrix[corners[i][1]][corners[i][0]] == '1')
        {
            //printf("Position invalide %d\n", i);
            return 0;
        }
        i++;
    }
    return 1;
}

void init_key(t_general *general)
{
    general->keys = malloc(sizeof(t_keys));
    if (general->keys == NULL)
    {
        printf("Malloc ERROR KEYS\n");
        exit(EXIT_FAILURE);
    }
    general->keys->w = 0;
    general->keys->a = 0;
    general->keys->s = 0;
    general->keys->d = 0;
    general->keys->arrow_l = 0;
    general->keys->arrow_r = 0;

}

void init_window(t_mlib *mlib, t_scene *scene, t_sprites *sprites)
{
    t_general *general;
 
    general = (t_general *) malloc (sizeof(t_general));
    if (general == NULL)
    {
        printf("ERROR MALLOC FOR general\n");
    }

    

    scene->mini_map = 1;
    init_key(general);




    general->mlib = mlib;
    general->scene = scene;
    general->sprites = sprites;



    mlib->utils.mlx = mlx_init();
    
    load_texture(general);
    printf("h_wall est = %d w_wall est = %d h_wall ouest = %d w_wall ouest = %d\n",
            general->sprites->wall_east->sprite_h,
            general->sprites->wall_east->sprite_w,
            general->sprites->wall_west->sprite_h,
            general->sprites->wall_west->sprite_w
            );


    printf("h_wall est = %d w_wall est = %d h_wall ouest = %d w_wall ouest = %d\n",
            general->sprites->wall_south->sprite_h,
            general->sprites->wall_south->sprite_w,
            general->sprites->wall_north->sprite_h,
            general->sprites->wall_north->sprite_w
            );

    mlib->utils.win = mlx_new_window(mlib->utils.mlx, WIDTH, HEIGHT, "Cube3D");





    mlx_hook(mlib->utils.win, 2, 0, key_press_exit, general);  // Hook pour les touches pressées
    mlx_hook(mlib->utils.win, 3, 0, key_release, general);
    mlx_hook(mlib->utils.win, 4, 0, mouse_press, mlib);  // Hook pour les clics de souris
    mlx_hook(mlib->utils.win, 17, 0, close_window, mlib);  // Hook pour la fermeture de la fenêtre

    mlx_loop_hook(mlib->utils.mlx, render, general);
    


    //mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, sprites->wall_north.data_spr.img_ptr, 0, 0);

    mlx_loop(mlib->utils.mlx);
}