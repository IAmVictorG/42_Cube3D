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

int key_press_exit(int keycode, t_general *general)
{
    key_pression(keycode, general);
    //printf("keycode = %d\n", keycode);
    if (keycode == 53)
    {
        exit(EXIT_FAILURE);
    }
    return (0);
}

/*
t_coord get_new_postion_x (int prev_pos_x, float player_speed, )
{
    int new_pos_x;

    new_pos_x = prev_pos_x -




}
*/



void move(t_general *general)
{
    int pos_x;
    int pos_y;
    int size_wall;
    int render_time;

    render_time = (clock() - general->time) / 1000;
    size_wall = general->scene->map.size_wall;

    if (general->keys->s == 1)
    {
        pos_x = round(general->scene->player.pos.x - general->scene->player.speed * general->scene->player.dir.x * size_wall);
        pos_y = round(general->scene->player.pos.y - general->scene->player.speed * general->scene->player.dir.y * size_wall);
        if (position_is_valid(general, pos_x, pos_y) == 1)
        {
            general->scene->player.pos.x = pos_x;
            general->scene->player.pos.y = pos_y;
        }
        else
        {
            if (position_is_valid(general, general->scene->player.pos.x, general->scene->player.pos.y - general->scene->player.dir.y * size_wall))
            {
                general->scene->player.pos.y = pos_y;
            }
            else if (position_is_valid(general, general->scene->player.pos.x - general->scene->player.dir.x * size_wall, general->scene->player.pos.y))
            {
                general->scene->player.pos.x = pos_x;
            }
        }
        // print_player(general->scene->player);
    }

    if (general->keys->w == 1) /*z sur AZERTY*/
    {
        pos_x = round(general->scene->player.pos.x + general->scene->player.speed * general->scene->player.dir.x * size_wall);
        pos_y = round(general->scene->player.pos.y + general->scene->player.speed * general->scene->player.dir.y * size_wall);
        if (position_is_valid(general, pos_x, pos_y) == 1)
        {
            general->scene->player.pos.x = pos_x;
            general->scene->player.pos.y = pos_y;
        }
        else
        {
            if (position_is_valid(general, general->scene->player.pos.x, general->scene->player.pos.y + general->scene->player.dir.y * size_wall))
            {
                general->scene->player.pos.y = pos_y;
            }
            else if (position_is_valid(general, general->scene->player.pos.x + general->scene->player.dir.x * size_wall, general->scene->player.pos.y))
            {
                general->scene->player.pos.x = pos_x;
            }
        }
    }


    if (general->keys->a == 1) /*q sur AZERTY*/
    {
        pos_x = round(general->scene->player.pos.x + general->scene->player.speed * general->scene->player.dir.y * size_wall);
        pos_y = round(general->scene->player.pos.y - general->scene->player.speed * general->scene->player.dir.x * size_wall);


        if (position_is_valid(general,pos_x, pos_y) == 1)
        {
            general->scene->player.pos.x = pos_x;
            general->scene->player.pos.y = pos_y;
        }
        else
        {
            if (position_is_valid(general, general->scene->player.pos.x, general->scene->player.pos.y - general->scene->player.speed * general->scene->player.dir.x * size_wall))
            {
                general->scene->player.pos.y = pos_y;
            }
            else if (position_is_valid(general, general->scene->player.pos.x + general->scene->player.speed * general->scene->player.dir.y * size_wall, general->scene->player.pos.y))
            {
                general->scene->player.pos.x = pos_x;
            }
        }

        // print_player(general->scene->player);
    }
    if (general->keys->d == 1)
    {
        
        pos_x = round(general->scene->player.pos.x - general->scene->player.speed * general->scene->player.dir.y * size_wall);
        pos_y = round(general->scene->player.pos.y + general->scene->player.speed * general->scene->player.dir.x * size_wall);

        if (position_is_valid(general, pos_x, pos_y) == 1)
        {
            general->scene->player.pos.x = pos_x;
            general->scene->player.pos.y = pos_y;
        }
        else
        {
            if (position_is_valid(general, general->scene->player.pos.x, general->scene->player.pos.y + general->scene->player.speed * general->scene->player.dir.x * size_wall))
            {
                general->scene->player.pos.y = pos_y;
            }
            else if (position_is_valid(general, general->scene->player.pos.x - general->scene->player.speed * general->scene->player.dir.y * size_wall, general->scene->player.pos.y))
            {
                general->scene->player.pos.x = pos_x;
            }
        }

        // print_player(general->scene->player);
    }

    //Changement de direction player
    if (general->keys->q == 1)
    {
        float angle = atan2f(general->scene->player.dir.y, general->scene->player.dir.x);
        angle -= ROTATION_SPEED;
        general->scene->player.dir.x = cosf(angle);
        general->scene->player.dir.y = sinf(angle);
        // print_player(general->scene->player);

    }
    if (general->keys->r == 1)
    {
        float angle = atan2f(general->scene->player.dir.y, general->scene->player.dir.x);
        angle += ROTATION_SPEED;
        general->scene->player.dir.x = cosf(angle);
        general->scene->player.dir.y = sinf(angle);
       // // print_player(general->scene->player);

    }
    if (general->keys->arrow_l == 1)
    {
        float angle = atan2f(general->scene->player.dir.y, general->scene->player.dir.x);
        angle -= ROTATION_SPEED;
        general->scene->player.dir.x = cosf(angle);
        general->scene->player.dir.y = sinf(angle);
        // print_player(general->scene->player);

    }
    if (general->keys->arrow_r == 1)
    {
        float angle = atan2f(general->scene->player.dir.y, general->scene->player.dir.x);
        angle += ROTATION_SPEED;
        general->scene->player.dir.x = cosf(angle);
        general->scene->player.dir.y = sinf(angle);
        // print_player(general->scene->player);
    }
    //printf("Player Position %d, %d\n", general->scene->player.pos.x, general->scene->player.pos.y);
}

int position_is_valid(t_general *general, int pos_x, int pos_y)
{
    int player_size;
    int i;
    
    player_size = 1;
    int corners[4][2] = 
    {
        {((pos_x - player_size) / general->scene->map.size_wall), ((pos_y - player_size) / general->scene->map.size_wall)},
        {((pos_x + player_size) / general->scene->map.size_wall), ((pos_y - player_size) / general->scene->map.size_wall)},
        {((pos_x - player_size) / general->scene->map.size_wall), ((pos_y + player_size) / general->scene->map.size_wall)},
        {((pos_x + player_size) / general->scene->map.size_wall), ((pos_y + player_size) / general->scene->map.size_wall)}
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
    /*if (general->scene->map.matrix[pos_x / general->scene->map.size_wall][pos_y / general->scene->map.size_wall] == '1')
    {
        return (0);
    }*/
    return (1);
}

t_keys *init_key()
{
    t_keys *keys;


    keys = (t_keys *) malloc(sizeof(t_keys));
    if (keys == NULL)
    {
        return (NULL);
        //printf("Malloc ERROR KEYS\n");
        //exit(EXIT_FAILURE);
    }
    keys->w = 0;
    keys->a = 0;
    keys->s = 0;
    keys->d = 0;
    keys->arrow_l = 0;
    keys->arrow_r = 0;

    return (keys);

}