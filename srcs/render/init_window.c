#include "../../header.h"

int key_press(int keycode, t_mlib *mlib)
{
    (void) keycode;
    (void) mlib;
    if (keycode == 53)
    {
        exit(EXIT_FAILURE);
    }
    return (0);
}

// Fonction pour gérer les événements souris
int mouse_press(int button, int x, int y, t_mlib *mlib)
{
    (void) button;
    (void) x;
    (void) y;
    (void) mlib;
    return (0);
}

int close_window(t_mlib *mlib)
{
    mlx_destroy_window(mlib->utils.mlx, mlib->utils.win);
    exit(0);
}

void init_window(t_mlib *mlib, t_scene *scene)
{
   // void *img_ptr;
    //int img_height;
   // int img_width;

    mlib->utils.mlx = mlx_init();
    mlib->utils.win = mlx_new_window(mlib->utils.mlx, WIDTH, HEIGHT, "Cube3D");

   // img_ptr = mlx_png_file_to_image(mlib->utils.mlx, "sprites/Wall_North.png", &img_width, &img_height);
    
    render(scene, mlib);
    //mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, img_ptr, 0, 0);

    mlx_hook(mlib->utils.win, 2, 1L<<0, key_press, mlib);  // Hook pour les touches pressées
    mlx_hook(mlib->utils.win, 4, 1L<<2, mouse_press, mlib);  // Hook pour les clics de souris
    mlx_hook(mlib->utils.win, 17, 1L<<17, close_window, mlib);  // Hook pour la fermeture de la fenêtre

    mlx_loop(mlib->utils.mlx);
}