/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:40:26 by vgiordan          #+#    #+#             */
/*   Updated: 2023/08/17 11:40:27 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	position_is_valid(t_general *general, int pos_x, int pos_y)
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
			general->scene->player.pos2D = convertcoord2d(*n_p);
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
			general->scene->player.pos2D = convertcoord2d(*n_p);
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
			general->scene->player.pos2D = convertcoord2d(*n_p);
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
			general->scene->player.pos2D = convertcoord2d(*n_p);
			general->scene->player.pos = *n_p;
			*c_p = *n_p;
		}
	}
}
