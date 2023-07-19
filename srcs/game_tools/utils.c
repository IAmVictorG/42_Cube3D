#include "../../header.h"

int hit_a_wall(t_general *general, int x, int y)
{
    char **matrix = general->scene->map.matrix;
    int size_wall = general->scene->map.size_wall;
    int map_h = general->scene->map.height_map;
    int map_w = general->scene->map.width_map;


    //printf("y = %d x = %d\n", y / size_wall, x / size_wall);

    if (y / size_wall >= map_h || x / size_wall >= map_w)
    {
        return (0);
    }


    return (matrix[y / size_wall][x / size_wall] == '1');

}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
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

void load_texture(t_general *general)
{    
    t_sprites *sprites = general->sprites;

    sprites->wall_north->data_spr.img_ptr = mlx_xpm_file_to_image(general->mlib->utils.mlx, "sprites/Wall_North.xpm", &sprites->wall_north->sprite_w , &sprites->wall_north->sprite_h);
    sprites->wall_north->data_spr.addr = mlx_get_data_addr(sprites->wall_north->data_spr.img_ptr, &sprites->wall_north->data_spr.bits_per_pixel, &sprites->wall_north->data_spr.line_length, &sprites->wall_north->data_spr.endian); /* devrait etre un pointeur */
    
    sprites->wall_south->data_spr.img_ptr = mlx_xpm_file_to_image(general->mlib->utils.mlx, "sprites/Wall_South.xpm", &sprites->wall_south->sprite_w , &sprites->wall_south->sprite_h);
    sprites->wall_south->data_spr.addr = mlx_get_data_addr(sprites->wall_south->data_spr.img_ptr, &sprites->wall_south->data_spr.bits_per_pixel, &sprites->wall_south->data_spr.line_length, &sprites->wall_south->data_spr.endian); /* devrait etre un pointeur */

    sprites->wall_east->data_spr.img_ptr = mlx_xpm_file_to_image(general->mlib->utils.mlx, "sprites/Wall_East.xpm", &sprites->wall_east->sprite_w , &sprites->wall_east->sprite_h);
    sprites->wall_east->data_spr.addr = mlx_get_data_addr(sprites->wall_east->data_spr.img_ptr, &sprites->wall_east->data_spr.bits_per_pixel, &sprites->wall_east->data_spr.line_length, &sprites->wall_east->data_spr.endian); /* devrait etre un pointeur */

    sprites->wall_west->data_spr.img_ptr = mlx_xpm_file_to_image(general->mlib->utils.mlx, "sprites/Wall_West.xpm", &sprites->wall_west->sprite_w , &sprites->wall_west->sprite_h);
    sprites->wall_west->data_spr.addr = mlx_get_data_addr(sprites->wall_west->data_spr.img_ptr, &sprites->wall_west->data_spr.bits_per_pixel, &sprites->wall_west->data_spr.line_length, &sprites->wall_west->data_spr.endian); /* devrait etre un pointeur */
}

t_coord get_end_point(t_general *general, t_coord position, float angle)
{
    //t_matrix matrix = general->scene->matrix;

    (void) general;

    int size_wall = general->scene->map.size_wall;

    t_coord next_pix;

    next_pix.x = position.x;
    next_pix.y = position.y;


    while (next_pix.x > size_wall && next_pix.y > size_wall)
    {
        next_pix.x = (int) ((float) next_pix.x + cosf(angle) * size_wall);
        next_pix.y = (int) ((float) next_pix.y + sinf(angle) * size_wall);
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