#include "../header.h"

int	render(t_general *general)
{
	if (general->scene->mini_map == 1)
	{
		render_mini_map(general);
	}
	else
	{
		render_game(general);
	}
	return (1);
}

void	init_window(t_general *general)
{
	general->mlib->utils.win = mlx_new_window(general->mlib->utils.mlx,
			WIDTH,
			HEIGHT,
			"Cube3D");
	mlx_hook(general->mlib->utils.win, 2, 0, key_pression, general);
	mlx_hook(general->mlib->utils.win, 3, 0, key_release, general);
	mlx_loop_hook(general->mlib->utils.mlx, render, general);
	mlx_loop(general->mlib->utils.mlx);
}
