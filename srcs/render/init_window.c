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

    
    return (1);
}

int key_pression_dir(int keycode, t_general *general)
{
    if (keycode == KEY_Q)
        general->keys->q = 1;
    else if (keycode == KEY_R)
        general->keys->r = 1;
    else if (keycode == KEY_ARR_R)
        general->keys->arrow_r = 1;
    else if (keycode == KEY_ARR_L)
        general->keys->arrow_l = 1;

    return (1);
}

int position_is_valid(t_general *general, float pos_x, float pos_y)
{
    /* Test pour les bords de la map */
    // if (pos_x < general->scene->map.size_wall || pos_y < general->scene->map.size_wall)
    // {
    //     return (0);
    // }

    int x = (int) (pos_x / general->scene->map.size_wall);
    int y = (int) (pos_y / general->scene->map.size_wall);
    printf("pos_x = %d\n", (int) (pos_x / general->scene->map.size_wall));
    printf("pos_y = %d\n", (int) (pos_y / general->scene->map.size_wall));
    printf("c = %c \n", general->scene->map.matrix[y][x]);

    if (general->scene->map.matrix[y][x] == '1')
    {
        return (0);
    }





    return(1);
}


int key_press(int keycode, t_general *general)
{
    float pos_x;
    float pos_y;

    key_pression(keycode, general);
    key_pression_dir(keycode, general);

    printf("keycode = %d\n", keycode);
    printf("w %d\n", general->keys->w);
    printf("a %d\n", general->keys->a);
    printf("s %d\n", general->keys->s);
    printf("d %d\n", general->keys->d);

    if (keycode == 53)
    {
        exit(EXIT_FAILURE);
    }
    if (general->keys->s == 1)
    {
        pos_x = general->scene->player.pos.x - general->scene->player.speed * general->scene->player.dir.x;
        pos_y = general->scene->player.pos.y - general->scene->player.speed * general->scene->player.dir.y;
        
        if (position_is_valid(general, pos_x, pos_y) == 1)
        {
            general->scene->player.pos.x = pos_x;
            general->scene->player.pos.y = pos_y;
        }

        print_player(general->scene->player);
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
        print_player(general->scene->player);
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

        print_player(general->scene->player);
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

        print_player(general->scene->player);

    }

    //Changement de direction player
    if (general->keys->q == 1)
    {
        float angle = atan2f(general->scene->player.dir.y, general->scene->player.dir.x);
        angle -= ROTATION_SPEED;
        general->scene->player.dir.x = cosf(angle);
        general->scene->player.dir.y = sinf(angle);
        print_player(general->scene->player);

    }
    if (general->keys->r == 1)
    {
        float angle = atan2f(general->scene->player.dir.y, general->scene->player.dir.x);
        angle += ROTATION_SPEED;
        general->scene->player.dir.x = cosf(angle);
        general->scene->player.dir.y = sinf(angle);
        print_player(general->scene->player);

    }
    if (general->keys->arrow_l == 1)
    {
        float angle = atan2f(general->scene->player.dir.y, general->scene->player.dir.x);
        angle -= ROTATION_SPEED;
        general->scene->player.dir.x = cosf(angle);
        general->scene->player.dir.y = sinf(angle);
        print_player(general->scene->player);

    }
    if (general->keys->arrow_r == 1)
    {
        float angle = atan2f(general->scene->player.dir.y, general->scene->player.dir.x);
        angle += ROTATION_SPEED;
        general->scene->player.dir.x = cosf(angle);
        general->scene->player.dir.y = sinf(angle);
        print_player(general->scene->player);
    }

    return (0);
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
}

void init_window(t_mlib *mlib, t_scene *scene)
{
    t_general *general;
 
    general = (t_general *) malloc (sizeof(t_general));
    if (general == NULL)
    {
        printf("ERROR MALLOC FOR general\n");

    }
    
    init_key(general);

    general->mlib = mlib;
    general->scene = scene;


    mlib->utils.mlx = mlx_init();
    mlib->utils.win = mlx_new_window(mlib->utils.mlx, WIDTH, HEIGHT, "Cube3D");

    mlx_hook(mlib->utils.win, 2, 0, key_press, general);  // Hook pour les touches pressées
    mlx_hook(mlib->utils.win, 3, 0, key_release, general);
    mlx_hook(mlib->utils.win, 4, 0, mouse_press, mlib);  // Hook pour les clics de souris
    mlx_hook(mlib->utils.win, 17, 0, close_window, mlib);  // Hook pour la fermeture de la fenêtre
    mlx_loop_hook(mlib->utils.mlx, render, general);
    mlx_loop(mlib->utils.mlx);
}