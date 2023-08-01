#include "../header.h"

void init_window(t_general *general, t_mlib *mlib)
{

    mlib->utils.win = mlx_new_window(mlib->utils.mlx, WIDTH, HEIGHT, "Cube3D");

    mlx_hook(mlib->utils.win, 2, 0, key_press_exit, general);  // Hook pour les touches pressées
    mlx_hook(mlib->utils.win, 3, 0, key_release, general);
    mlx_hook(mlib->utils.win, 4, 0, mouse_press, mlib);  // Hook pour les clics de souris
    mlx_hook(mlib->utils.win, 17, 0, close_window, mlib);  // Hook pour la fermeture de la fenêtre

    mlx_loop_hook(mlib->utils.mlx, render, general);
    


    //mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, sprites->wall_north.data_spr.img_ptr, 0, 0);

    mlx_loop(mlib->utils.mlx);
}