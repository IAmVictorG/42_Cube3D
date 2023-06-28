#include "../../header.h"

int key_press(int keycode, t_general *general)
{
    (void) keycode;
    printf("keycode = %d\n", keycode);
    
    if (keycode == 53)
    {
        exit(EXIT_FAILURE);
    }

    if (keycode == 0)
    {
        general->scene->player.pos.x -=1;


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

    t_general *general;

    general = (t_general *) malloc (sizeof(t_general));
    if (general == NULL)
    {
        printf("tammmmmmmngmdfgnsjdfgs\n");
    }




    general->mlib = mlib;
    general->scene = scene;
    print_scene(general->scene);

    mlib->utils.mlx = mlx_init();
    mlib->utils.win = mlx_new_window(mlib->utils.mlx, WIDTH, HEIGHT, "Cube3D");

    mlib->data.img_ptr = mlx_new_image(mlib->utils.mlx, WIDTH, HEIGHT);
    mlib->data.addr = mlx_get_data_addr(mlib->data.img_ptr, &mlib->data.bits_per_pixel, &mlib->data.line_length, &mlib->data.endian);
   // img_ptr = mlx_png_file_to_image(mlib->utils.mlx, "sprites/Wall_North.png", &img_width, &img_height);
    printf("LET\n");
    mlx_loop_hook(mlib->utils.win, render, general);
    //mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, img_ptr, 0, 0);

    //mlx_hook(mlib->utils.win, 2, 1L<<0, key_press, general);  // Hook pour les touches pressées
    mlx_hook(mlib->utils.win, 4, 1L<<2, mouse_press, mlib);  // Hook pour les clics de souris
    mlx_hook(mlib->utils.win, 17, 1L<<17, close_window, mlib);  // Hook pour la fermeture de la fenêtre

    mlx_loop(mlib->utils.mlx);
}