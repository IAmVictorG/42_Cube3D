#include "../../header.h"

int hit_a_wall(t_general *general, int x, int y)
{
    char **matrix = general->scene->map.matrix;


    return (matrix[y / SIZE_WALL][x / SIZE_WALL] == '1');

}

int my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

    if (color < 0)
    {
        printf("\n\nPixel : x = %d y = %d\n", x, y);
        printf("Attention la segfault\n\n");
    }

    // printf("data line length = %d\n", data->bits_per_pixel);
    // exit(42);

    //data->line_length = 6400;
    //data->bit_per_pixel = 32;

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        //y = HEIGHT;
	    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));

	    *(unsigned int*)dst = color;
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

t_coord create_trgb_reverse(unsigned int color) 
{
    t_coord color_vec;

    color_vec.x = (color >> 16) & 0xFF;
    color_vec.y = (color >> 8) & 0xFF;
    color_vec.z = color & 0xFF;

    return (color_vec);

}

t_vec vec_normalize(t_vec v)
{
    float vec3_length;    
    t_vec normalized;

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
    return normalized;
}

int load_texture_xpm(t_general *general)
{    
    t_sprites *sprites;
    //void        *temp;

    sprites = general->sprites;


    // temp = mlx_xpm_file_to_image(general->mlib->utils.mlx, "texture/texture1.xpm", &sprites->wall_north->sprite_w , &sprites->wall_north->sprite_h);
    // if (temp == NULL)
    // {
    //     printf("ici\n");
    //     return (0);
    // }
    // else
    // {
    //     sprites->wall_north->data_spr.img_ptr = temp;
    // }

    sprites->wall_north->data_spr.img_ptr = mlx_xpm_file_to_image(general->mlib->utils.mlx, "sprites/Wall_North.xpm", &sprites->wall_north->sprite_w , &sprites->wall_north->sprite_h);
    sprites->wall_north->data_spr.addr = mlx_get_data_addr(sprites->wall_north->data_spr.img_ptr, &sprites->wall_north->data_spr.bits_per_pixel, &sprites->wall_north->data_spr.line_length, &sprites->wall_north->data_spr.endian); /* devrait etre un pointeur */
    
    sprites->wall_south->data_spr.img_ptr = mlx_xpm_file_to_image(general->mlib->utils.mlx, "sprites/Wall_South.xpm", &sprites->wall_south->sprite_w , &sprites->wall_south->sprite_h);
    sprites->wall_south->data_spr.addr = mlx_get_data_addr(sprites->wall_south->data_spr.img_ptr, &sprites->wall_south->data_spr.bits_per_pixel, &sprites->wall_south->data_spr.line_length, &sprites->wall_south->data_spr.endian); /* devrait etre un pointeur */

    sprites->wall_east->data_spr.img_ptr = mlx_xpm_file_to_image(general->mlib->utils.mlx, "sprites/Wall_East.xpm", &sprites->wall_east->sprite_w , &sprites->wall_east->sprite_h);
    sprites->wall_east->data_spr.addr = mlx_get_data_addr(sprites->wall_east->data_spr.img_ptr, &sprites->wall_east->data_spr.bits_per_pixel, &sprites->wall_east->data_spr.line_length, &sprites->wall_east->data_spr.endian); /* devrait etre un pointeur */

    sprites->wall_west->data_spr.img_ptr = mlx_xpm_file_to_image(general->mlib->utils.mlx, "sprites/Wall_West.xpm", &sprites->wall_west->sprite_w , &sprites->wall_west->sprite_h);
    sprites->wall_west->data_spr.addr = mlx_get_data_addr(sprites->wall_west->data_spr.img_ptr, &sprites->wall_west->data_spr.bits_per_pixel, &sprites->wall_west->data_spr.line_length, &sprites->wall_west->data_spr.endian); /* devrait etre un pointeur */


    return (1);
}


int load_texture_png(t_general *general)
{    
    t_sprites   *sprites;
    void        *temp;

    sprites = general->sprites;

    temp = mlx_png_file_to_image(general->mlib->utils.mlx, general->sprites->wall_north->path, &sprites->wall_north->sprite_w , &sprites->wall_north->sprite_h);
    if (temp == NULL)
        return (0);
    sprites->wall_north->data_spr.img_ptr = temp;
    sprites->wall_north->data_spr.addr = mlx_get_data_addr(sprites->wall_north->data_spr.img_ptr, &sprites->wall_north->data_spr.bits_per_pixel, &sprites->wall_north->data_spr.line_length, &sprites->wall_north->data_spr.endian); /* devrait etre un pointeur */
    

    temp = mlx_png_file_to_image(general->mlib->utils.mlx, general->sprites->wall_south->path, &sprites->wall_south->sprite_w , &sprites->wall_south->sprite_h);
    if (temp == NULL)
        return (0);
    sprites->wall_south->data_spr.img_ptr = temp;
    sprites->wall_south->data_spr.addr = mlx_get_data_addr(sprites->wall_south->data_spr.img_ptr, &sprites->wall_south->data_spr.bits_per_pixel, &sprites->wall_south->data_spr.line_length, &sprites->wall_south->data_spr.endian); /* devrait etre un pointeur */
    

    temp = mlx_png_file_to_image(general->mlib->utils.mlx, general->sprites->wall_east->path, &sprites->wall_east->sprite_w , &sprites->wall_east->sprite_h);
    if (temp == NULL)
        return (0);
    sprites->wall_east->data_spr.img_ptr = temp;
    sprites->wall_east->data_spr.addr = mlx_get_data_addr(sprites->wall_east->data_spr.img_ptr, &sprites->wall_east->data_spr.bits_per_pixel, &sprites->wall_east->data_spr.line_length, &sprites->wall_east->data_spr.endian); /* devrait etre un pointeur */
    

    temp = mlx_png_file_to_image(general->mlib->utils.mlx, general->sprites->wall_west->path, &sprites->wall_west->sprite_w , &sprites->wall_west->sprite_h);
    if (temp == NULL)
        return (0);
    sprites->wall_west->data_spr.img_ptr = temp;
    sprites->wall_west->data_spr.addr = mlx_get_data_addr(sprites->wall_west->data_spr.img_ptr, &sprites->wall_west->data_spr.bits_per_pixel, &sprites->wall_west->data_spr.line_length, &sprites->wall_west->data_spr.endian); /* devrait etre un pointeur */

    return (1);
}

t_coord get_end_point(t_general *general, t_coord position, float angle)
{
    //t_matrix matrix = general->scene->matrix;

    (void) general;



    t_coord next_pix;

    next_pix.x = position.x;
    next_pix.y = position.y;


    while (next_pix.x > SIZE_WALL && next_pix.y > SIZE_WALL)
    {
        next_pix.x = (int) ((float) next_pix.x + cosf(angle) * SIZE_WALL);
        next_pix.y = (int) ((float) next_pix.y + sinf(angle) * SIZE_WALL);
    }
    next_pix.z = 0;
    //printCoord(next_pix);
    //printf("\n");
    return next_pix;

}

float   rad_to_deg(float angle)
{
    return ((angle * 180)/M_PI);
}

float   deg_to_rad(float angle)
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

int convert_coord_for_2D_X(int x)
{
	return (x * SCALE_MINI_MAP) / SIZE_WALL ;
}

int convert_coord_for_2D_Y(int y)
{
	return (y * SCALE_MINI_MAP) / SIZE_WALL;
}

t_coord	convert_coord_for_2D(t_coord pos)
{
    t_coord pos2D;

	pos2D.x = (pos.x * SCALE_MINI_MAP) / SIZE_WALL;
	pos2D.y = (pos.y * SCALE_MINI_MAP) / SIZE_WALL;

    return pos2D;
}
