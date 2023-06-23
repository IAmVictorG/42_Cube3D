#include <stdio.h>
#include "mlx/mlx.h"
#include <stdlib.h>

#define WIN_HEIGHT 1000
#define WIN_WIDTH 500

typedef struct s_data 
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

typedef struct s_vars 
{
	void *mlx;
	void *win;
} t_vars;

typedef struct s_picture
{
	int value;
	int x;
	int	y;

} t_picture;


typedef struct s_data_vars
{
	t_data		*data;
	t_vars		*vars;
	t_picture	*picture;

} t_data_vars;

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void display_data (t_data img)
{
	printf("     void *img = %p\n", img.img);
	printf("    char *addr = %p\n", img.addr);
	printf("bits_per_pixel = %d\n", img.bits_per_pixel);
	printf("   line_length = %d\n", img.line_length);
	printf("        endian = %d\n", img.line_length);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int manage_OnKeydown(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else
	{
		printf("Kycode = %d\n", keycode);
	}

	return (0);
}

int manage_MouseEvents(int keycode/*, t_vars *vars*/)
{
	printf("Mouse event = %d\n", keycode);
	return 0;
}

int render_next_frame (t_data_vars *data_vars)
{


	//my_mlx_pixel_put(data_vars->data, data_vars->picture->value, data_vars->picture->value, 0x00FF0000);
	//mlx_put_image_to_window(data_vars->vars->mlx, data_vars->vars->win, data_vars->data->img,0,0);

	//my_mlx_pixel_put(data_vars->data, data_vars->picture->value, data_vars->picture->value, 0x00FF0000);

	


	my_mlx_pixel_put(data_vars->data, data_vars->picture->x, data_vars->picture->y, 0x00FF0000);
	my_mlx_pixel_put(data_vars->data, 499, 996, 0xFF000000);
	my_mlx_pixel_put(data_vars->data, 499, 997, 0x0000FF00);
	my_mlx_pixel_put(data_vars->data, 499, 998, 0x000000FF);
	my_mlx_pixel_put(data_vars->data, 499, 999, 0x00FF0000);
	//my_mlx_pixel_put(data_vars->data, 499, 1000, 0x000000FF);
		
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, data_vars->data->img);
	mlx_put_image_to_window(data_vars->vars->mlx, data_vars->vars->win, data_vars->data->img,0,0);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, data_vars->vars->win);

	return 0;
}

int main()
{
	t_data		data;
	t_vars		vars;
	t_picture	picture;

	t_data_vars data_vars;

	data_vars.data = &data;
	data_vars.vars = &vars;
	data_vars.picture = &picture;

	picture.x = 250;
	picture.y = 500;


	vars.mlx = mlx_init();

	vars.win = mlx_new_window(vars.mlx,  WIN_WIDTH, WIN_HEIGHT,"Window");

	data.img = mlx_new_image(vars.mlx, WIN_WIDTH, WIN_HEIGHT);

	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	mlx_loop_hook(vars.mlx, render_next_frame, &data_vars);

	mlx_hook(vars.win, 2, 1L<<0, manage_OnKeydown, &vars);
	mlx_mouse_hook(vars.win, manage_MouseEvents, &vars);

	//display_data(data);

	mlx_loop(vars.mlx);

	return 0;
}