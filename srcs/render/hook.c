#include "../../header.h"

int key_pression(int keycode, t_general *general)
{
    if (keycode == KEY_W)
        general->keys->w = 1;
    else if (keycode == KEY_A)
        general->keys->a = 1;
    else if (keycode == KEY_S)
        general->keys->s = 1;
    else if (keycode == KEY_D)
        general->keys->d = 1;
    else if (keycode == KEY_Q)
        general->keys->q = 1;
    else if (keycode == KEY_R)
        general->keys->r = 1;
    else if (keycode == KEY_ARR_R)
        general->keys->arrow_r = 1;
    else if (keycode == KEY_ARR_L)
        general->keys->arrow_l = 1;
    else if (keycode == KEY_M)
        general->scene->mini_map ^= 1; 

    
    return (1);
}

int key_release(int keycode, t_general *general)
{
    if (keycode == KEY_W)
        general->keys->w = 0;
    else if (keycode == KEY_A)
        general->keys->a = 0;
    else if (keycode == KEY_S)
        general->keys->s = 0;
    else if (keycode == KEY_D)
        general->keys->d = 0;
    else if (keycode == KEY_Q)
        general->keys->q = 0;
    else if (keycode == KEY_R)
        general->keys->r = 0;
    else if (keycode == KEY_ARR_R)
        general->keys->arrow_r = 0;
    else if (keycode == KEY_ARR_L)
        general->keys->arrow_l = 0;

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

int key_press(int keycode, t_general *general)
{

    key_pression(keycode, general);

    printf("keycode = %d\n", keycode);
 

    if (keycode == 53)
    {
        exit(EXIT_FAILURE);
    }


    return (0);
}