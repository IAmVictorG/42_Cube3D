#include "../header.h"

int	key_pression(int keycode, t_general *general)
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

int	key_release(int keycode, t_general *general)
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

int	position_is_valid(t_general *general, int pos_x, int pos_y)
{
	int	plyr_size;
	int	i;
	int	corners[4][2];

	plyr_size = SIZE_WALL * 0.05f;
	corners[0][0] = (pos_x - plyr_size) / SIZE_WALL;
	corners[0][1] = (pos_y - plyr_size) / SIZE_WALL;
	corners[1][0] = (pos_x + plyr_size) / SIZE_WALL;
	corners[1][1] = (pos_y - plyr_size) / SIZE_WALL;
	corners[2][0] = (pos_x - plyr_size) / SIZE_WALL;
	corners[2][1] = (pos_y + plyr_size) / SIZE_WALL;
	corners[3][0] = (pos_x + plyr_size) / SIZE_WALL;
	corners[3][1] = (pos_y + plyr_size) / SIZE_WALL;
	i = 0;
	while (i < 4)
	{
		if (general->scene->map.matrix[corners[i][1]][corners[i][0]] == '1')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	s_key(t_general *general, t_coord *c_p, t_coord *n_p, t_vec *dir)
{
	if (general->keys->s == 1)
	{
		(*n_p).x = round((*c_p).x - general->scene->player.speed * (*dir).x);
		(*n_p).y = round((*c_p).y - general->scene->player.speed * (*dir).y);
		if (position_is_valid(general, (*n_p).x, (*n_p).y) == 1)
		{
			general->scene->player.pos2D = convertCoord2D(*n_p);
			general->scene->player.pos = *n_p;
			*c_p = *n_p;
		}
	}
}

void	w_key(t_general *general, t_coord *c_p, t_coord *n_p, t_vec *dir)
{
	if (general->keys->w == 1)
	{
		(*n_p).x = round((*c_p).x + general->scene->player.speed * (*dir).x);
		(*n_p).y = round((*c_p).y + general->scene->player.speed * (*dir).y);
		if (position_is_valid(general, (*n_p).x, (*n_p).y) == 1)
		{
			general->scene->player.pos2D = convertCoord2D(*n_p);
			general->scene->player.pos = *n_p;
			*c_p = *n_p;
		}
	}
}

void	d_key(t_general *general, t_coord *c_p, t_coord *n_p, t_vec *dir)
{
	if (general->keys->d == 1)
	{
		(*n_p).x = round((*c_p).x - general->scene->player.speed * (*dir).y);
		(*n_p).y = round((*c_p).y + general->scene->player.speed * (*dir).x);
		if (position_is_valid(general, (*n_p).x, (*n_p).y) == 1)
		{
			general->scene->player.pos2D = convertCoord2D(*n_p);
			general->scene->player.pos = *n_p;
			*c_p = *n_p;
		}
	}
}

void	a_key(t_general *general, t_coord *c_p, t_coord *n_p, t_vec *dir)
{
	if (general->keys->a == 1)
	{
		(*n_p).x = round((*c_p).x + general->scene->player.speed * (*dir).y);
		(*n_p).y = round((*c_p).y - general->scene->player.speed * (*dir).x);
		if (position_is_valid(general, (*n_p).x, (*n_p).y) == 1)
		{
			general->scene->player.pos2D = convertCoord2D(*n_p);
			general->scene->player.pos = *n_p;
			*c_p = *n_p;
		}
	}
}

void	move(t_general *general)
{
	t_coord	n_p;
	t_coord	c_p;
	t_vec	dir;
	float	a;

	c_p = general->scene->player.pos;
	dir = general->scene->player.dir;
	s_key(general, &c_p, &n_p, &dir);
	w_key(general, &c_p, &n_p, &dir);
	d_key(general, &c_p, &n_p, &dir);
	a_key(general, &c_p, &n_p, &dir);
	if (general->keys->arrow_l == 1)
	{
		a = atan2f(general->scene->player.dir.y, general->scene->player.dir.x);
		a -= ROTATION_SPEED;
		general->scene->player.dir.x = cosf(a);
		general->scene->player.dir.y = sinf(a);
	}
	if (general->keys->arrow_r == 1)
	{
		a = atan2f(general->scene->player.dir.y, general->scene->player.dir.x);
		a += ROTATION_SPEED;
		general->scene->player.dir.x = cosf(a);
		general->scene->player.dir.y = sinf(a);
	}
}
