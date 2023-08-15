#include "../../header.h"

int	hit_a_wall(t_general *general, int x, int y)
{
	char	**matrix;

	matrix = general->scene->map.matrix;
	return (matrix[y / SIZE_WALL][x / SIZE_WALL] == '1');
}

int	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (color < 0)
	{
		printf("\n\nmyPixel : x = %d y = %d\n", x, y);
	}
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr
			+ (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *) dst = color;
		return (1);
	}
	else
	{
		printf("Pixel inconnu : x = %d y = %d\n", x, y);
		return (-1);
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_coord	create_trgb_reverse(unsigned int color)
{
	t_coord	color_vec;

	color_vec.x = (color >> 16) & 0xFF;
	color_vec.y = (color >> 8) & 0xFF;
	color_vec.z = color & 0xFF;
	return (color_vec);
}

t_vec	vec_normalize(t_vec v)
{
	float	vec3_length;
	t_vec	normalized;

	vec3_length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (vec3_length == 0.0)
	{
		normalized.x = 0.0;
		normalized.y = 0.0;
		normalized.z = 0.0;
	}
	else
	{
		normalized.x = v.x / vec3_length;
		normalized.y = v.y / vec3_length;
		normalized.z = v.z / vec3_length;
	}
	return (normalized);
}

static	int	load_no(t_general *general, t_sprites *sprites)
{
	void	*temp;

	temp = mlx_png_file_to_image(general->mlib->utils.mlx,
			general->sprites->wall_north->path,
			&sprites->wall_north->sprite_w,
			&sprites->wall_north->sprite_h);
	if (temp == NULL)
		return (0);
	sprites->wall_north->data_spr.img_ptr = temp;
	sprites->wall_north->data_spr.addr = mlx_get_data_addr(
			sprites->wall_north->data_spr.img_ptr,
			&sprites->wall_north->data_spr.bits_per_pixel,
			&sprites->wall_north->data_spr.line_length,
			&sprites->wall_north->data_spr.endian);
	return (1);
}

static	int	load_so(t_general *general, t_sprites *sprites)
{
	void	*temp;

	temp = mlx_png_file_to_image(general->mlib->utils.mlx,
			general->sprites->wall_south->path,
			&sprites->wall_south->sprite_w,
			&sprites->wall_south->sprite_h);
	if (temp == NULL)
		return (0);
	sprites->wall_south->data_spr.img_ptr = temp;
	sprites->wall_south->data_spr.addr = mlx_get_data_addr(
			sprites->wall_south->data_spr.img_ptr,
			&sprites->wall_south->data_spr.bits_per_pixel,
			&sprites->wall_south->data_spr.line_length,
			&sprites->wall_south->data_spr.endian);
	return (1);
}

static	int	load_ea(t_general *general, t_sprites *sprites)
{
	void	*temp;

	temp = mlx_png_file_to_image(general->mlib->utils.mlx,
			general->sprites->wall_east->path,
			&sprites->wall_east->sprite_w,
			&sprites->wall_east->sprite_h);
	if (temp == NULL)
		return (0);
	sprites->wall_east->data_spr.img_ptr = temp;
	sprites->wall_east->data_spr.addr = mlx_get_data_addr(
			sprites->wall_east->data_spr.img_ptr,
			&sprites->wall_east->data_spr.bits_per_pixel,
			&sprites->wall_east->data_spr.line_length,
			&sprites->wall_east->data_spr.endian);
	return (1);
}

static	int	load_we(t_general *general, t_sprites *sprites)
{
	void	*temp;

	temp = mlx_png_file_to_image(general->mlib->utils.mlx,
			general->sprites->wall_west->path,
			&sprites->wall_west->sprite_w,
			&sprites->wall_west->sprite_h);
	if (temp == NULL)
		return (0);
	sprites->wall_west->data_spr.img_ptr = temp;
	sprites->wall_west->data_spr.addr = mlx_get_data_addr(
			sprites->wall_west->data_spr.img_ptr,
			&sprites->wall_west->data_spr.bits_per_pixel,
			&sprites->wall_west->data_spr.line_length,
			&sprites->wall_west->data_spr.endian);
	return (1);
}

int	load_texture_png(t_general *general)
{
	t_sprites	*sprites;

	sprites = general->sprites;
	if (load_no(general, sprites) == 0)
		return (0);
	if (load_so(general, sprites) == 0)
		return (0);
	if (load_ea(general, sprites) == 0)
		return (0);
	if (load_we(general, sprites) == 0)
		return (0);
	return (1);
}

float	rad_to_deg(float angle)
{
	return ((angle * 180) / M_PI);
}

float	deg_to_rad(float angle)
{
	return ((angle * M_PI) / 180);
}

int	size_tab(char **tab)
{
	int	count;

	count = 0;
	while (tab[count] != NULL)
		count++;
	return (count);
}

void	ft_free_tabs(char **tab)
{
	int	i;
	int	h;

	h = size_tab(tab);
	i = 0;
	while (i <= h)
	{
		if (tab[i] != NULL)
			free(tab[i]);
		i++;
	}
	free(tab);
}

t_coord	convertcoord2d(t_coord pos)
{
	t_coord	pos2d;

	pos2d.x = (pos.x * SCALE_MINI_MAP) / SIZE_WALL;
	pos2d.y = (pos.y * SCALE_MINI_MAP) / SIZE_WALL;
	return (pos2d);
}
