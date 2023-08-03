#include "../header.h"

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
	else if (keycode == 53)
		exit(0);

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


int position_is_valid(t_general *general, int pos_x, int pos_y)
{
    int player_size;
    int i;
    
    player_size = 1;
    int corners[4][2] = 
    {
        {((pos_x - player_size) / SIZE_WALL), ((pos_y - player_size) / SIZE_WALL)},
        {((pos_x + player_size) / SIZE_WALL), ((pos_y - player_size) / SIZE_WALL)},
        {((pos_x - player_size) / SIZE_WALL), ((pos_y + player_size) / SIZE_WALL)},
        {((pos_x + player_size) / SIZE_WALL), ((pos_y + player_size) / SIZE_WALL)}
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

void move(t_general *general)
{
	t_coord	next_pos;
    t_coord current_pos;
    //t_coord current_pos2D;
    t_vec   dir;

    current_pos = general->scene->player.pos;
    //current_pos2D = general->scene->player.pos2D;
    dir = general->scene->player.dir;


    if (general->keys->s == 1)
    {
        next_pos.x = round(current_pos.x - SPEED * dir.x);
        next_pos.y = round(current_pos.y - SPEED * dir.y);


        if (position_is_valid(general, next_pos.x, next_pos.y) == 1)
        {
            general->scene->player.pos2D = convert_coord_for_2D(next_pos);
            general->scene->player.pos = next_pos;
            current_pos = next_pos;
        }

    }
    if (general->keys->w == 1) /*z sur AZERTY*/
    {
        next_pos.x = round(current_pos.x + SPEED * dir.x);
        next_pos.y = round(current_pos.y + SPEED * dir.y);

        if (position_is_valid(general, next_pos.x, next_pos.y) == 1)
        {
            general->scene->player.pos2D = convert_coord_for_2D(next_pos);
            general->scene->player.pos = next_pos;
            current_pos = next_pos;
        }
    }


    if (general->keys->d == 1) /*z sur AZERTY*/
    {
        next_pos.x = round(current_pos.x - SPEED * dir.y);
        next_pos.y = round(current_pos.y + SPEED * dir.x);

        if (position_is_valid(general, next_pos.x, next_pos.y) == 1)
        {
            general->scene->player.pos2D = convert_coord_for_2D(next_pos);
            general->scene->player.pos = next_pos;
            current_pos = next_pos;
        }
    }

    if (general->keys->a == 1) /*z sur AZERTY*/
    {
        next_pos.x = round(current_pos.x + SPEED * dir.y);
        next_pos.y = round(current_pos.y - SPEED * dir.x);

        if (position_is_valid(general, next_pos.x, next_pos.y) == 1)
        {
            general->scene->player.pos2D = convert_coord_for_2D(next_pos);
            general->scene->player.pos = next_pos;
            current_pos = next_pos;
        }
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
}