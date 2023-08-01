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
        general->scene->mini_map = 1;
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

// void move2D(t_general *general)
// {

// 	t_coord	next_pos;


//     if (general->keys->w == 1) /*z sur AZERTY*/
//     {
//         pos_x = round(general->scene->player.pos.x + general->scene->player.speed * general->scene->player.dir.x * size_wall);
//         pos_y = round(general->scene->player.pos.y + general->scene->player.speed * general->scene->player.dir.y * size_wall);
//         if (position_is_valid(general, pos_x, pos_y) == 1)
//         {
//             general->scene->player.pos.x = pos_x;
//             general->scene->player.pos.y = pos_y;
//         }
//         else
//         {
//             if (position_is_valid(general, general->scene->player.pos.x, general->scene->player.pos.y + general->scene->player.dir.y * size_wall))
//             {
//                 general->scene->player.pos.y = pos_y;
//             }
//             else if (position_is_valid(general, general->scene->player.pos.x + general->scene->player.dir.x * size_wall, general->scene->player.pos.y))
//             {
//                 general->scene->player.pos.x = pos_x;
//             }
//         }
//     }

// \
// }