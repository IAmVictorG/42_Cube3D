#include "../header.h"

t_mlib  *init_mlib()
{
    t_mlib  *mlib;

    mlib = (t_mlib *) malloc(sizeof(t_mlib));
    if (mlib == NULL)
        return (NULL);
    
    mlib->utils.mlx = mlx_init();


    return (mlib);
}

t_keys *init_key()
{
    t_keys *keys;


    keys = (t_keys *) malloc(sizeof(t_keys));
    if (keys == NULL)
    {
        return (NULL);
    }
    keys->w = 0;
    keys->a = 0;
    keys->s = 0;
    keys->d = 0;
    keys->arrow_l = 0;
    keys->arrow_r = 0;

    return (keys);

}

t_sprite *init_sprite(char *path)
{
    t_sprite    *wall;

    wall = (t_sprite *) malloc(sizeof(t_sprite));
    if (wall == NULL)
    {
        return (NULL);
    }
    wall->path = path;
    return (wall);
}

t_sprites   *init_sprites(char *wall_north, char *wall_south, char *wall_west, char *wall_east)
{
    t_sprites *sprites;

    sprites = (t_sprites *) malloc(sizeof(t_sprites));
    if (sprites == NULL)
        return (NULL);

    sprites->wall_east = init_sprite(wall_east);
    sprites->wall_west = init_sprite(wall_west);
    sprites->wall_south = init_sprite(wall_south);
    sprites->wall_north = init_sprite(wall_north);

    return sprites;
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

void print_tab(char **tab)
{
    int i;
    
	printf("-------------------------------- START\n\n");
    i = 0;
    while (tab[i] != NULL)
    {
        printf("[%s] (%d)\n", tab[i],i);
        i++;
    }
	printf("\n--------------------------------- END\n");
}

void    printMap(t_map  map)
{
    print_tab(map.matrix);
    printf("   height_map = %d\n", map.height_map);
    printf("    width_map = %d\n", map.width_map);
    printf("heigth_matrix = %d\n", map.height_matrix);
    printf(" width_matrix = %d\n", map.width_matrix);
    printf("    size_wall = %d\n", map.size_wall);
}

void    printVec(t_vec vector)
{
    printf("x = %f, ", vector.x);
    printf("y = %f, ", vector.y);
    printf("z = %f", vector.z);
    printf("\n");
}

void    printCoord(t_coord coord)
{
    printf("Coord x = %d ", coord.x);
    printf("Coord y = %d", coord.y);
    //printf("Coord z = %d", coord.z);
    printf("\n");
}

void    print_player(t_player player)
{
    printf("----PLAYER----\n");
    printCoord(player.coord_ini);
    printf("pos : ");
    printCoord(player.pos);
    printf("dir : ");
    printVec(player.dir);
    printf("speed = %f\n", player.speed);
    printf("\n");
}

t_coord	get_player_coord(char **matrix)
{
	int		lin;
	int		col;
	t_coord	coord_ini;

	coord_ini.x = -1;
	coord_ini.y = -1;
	lin = 0;
	while (matrix[lin] != NULL)
	{
		col = 0;
		while (matrix[lin][col] != '\0')
		{
			if (matrix[lin][col] == 'N' || matrix[lin][col] == 'S' || matrix[lin][col] == 'E' || matrix[lin][col] == 'W')
			{
				coord_ini.y = lin * SIZE_WALL + 32;
				coord_ini.x = col * SIZE_WALL + 32;

				return(coord_ini);	
			}
			col++;
		}
		lin++;
	}
	return (coord_ini);
}

char	get_letter_oreintation(char **matrix)
{
	int		i;
	int		j;

	i = 0;
	while (matrix[i] != NULL)
	{
		j = 0;
		while (matrix[i][j] != '\0')
		{
			if (matrix[i][j] == 'N' || matrix[i][j] == 'S' || matrix[i][j] == 'E' || matrix[i][j] == 'W')
				return (matrix[i][j]);
			j++;
		}
		i++;
	}
	return (0);
}


t_vec	get_player_orientation(char **matrix)
{
	char	orientation;
	t_vec	orientation_ini;

	orientation_ini.x = -1;
	orientation_ini.y = -1;
	orientation_ini.z = 0;

	orientation = get_letter_oreintation(matrix);
	
	if (orientation == 'N')
	{
		orientation_ini.x = 0;
		orientation_ini.y = -1;
	}
	else if (orientation == 'S')
	{
		orientation_ini.x = 0;
		orientation_ini.y = 1;
	}
	else if (orientation == 'W')
	{
		orientation_ini.x = -1;
		orientation_ini.y = 0;
	}
	else if (orientation == 'E')
	{
		orientation_ini.x = 1;
		orientation_ini.y = 0;
	}
	return (orientation_ini);
}

int convert_coord_for_2D_X(int x, int width_map)
{
	return ((int) roundf((float) (x * WIDTH) / (float) width_map));
}

int convert_coord_for_2D_Y(int y, int heigth_map)
{
	return (int) roundf((float) (y * HEIGHT) / (float) heigth_map);
}

t_coord	convert_coord_for_2D(t_coord pos, int width_map, int heigth_map)
{
    t_coord pos2D;

	pos2D.x = (int) roundf((float) (pos.x * WIDTH) / (float) width_map);
	pos2D.y = (int) roundf((float) (pos.y * HEIGHT) / (float) heigth_map);

    return pos2D;
}


int main ()
{

    t_general   *general;

    t_scene     *scene;
    t_mlib      *mlib;
    t_sprites   *sprites;
    t_keys      *keys;

	char		*matrix[21];

	matrix[0]  = "1111111111111111111111111111111111111111";
	matrix[1]  = "1000000000000000000000000000000000000001";
	matrix[2]  = "1000000000000000000000000000000000000001";
	matrix[3]  = "1000000000000011100000000000000000000001";
	matrix[4]  = "1000000000000010100000000000000000000001";
	matrix[5]  = "1000000000000000000000000000000000000001";
	matrix[6]  = "1000000000000000000000000000000000000001";
	matrix[7]  = "1000000000000000000000000000000000000001";
	matrix[8]  = "1000000000000000000000000000000000000001";
	matrix[9]  = "1000000000000000000000000000000000000001";
	matrix[10] = "1000000000000000000000000000000000000001";
	matrix[11] = "1000000000000000000000000000000000000001";
	matrix[12] = "1000000000000100000W00010000000000000001";
	matrix[13] = "1000000000000000000000000000000000000001";
	matrix[14] = "1000000000000000000000000000000000000001";
	matrix[15] = "1000000000000000000000000000000000000001";
	matrix[16] = "1000000000000000000000000000000000000001";
	matrix[17] = "1000000000000000000000000000000000000001";
	matrix[18] = "1000000000000000000000000000000000000001";
	matrix[19] = "1111111111111111111111111111111111111111";
	matrix[20] = NULL;
    


    general = (t_general *) malloc (sizeof(t_general));
    if (general == NULL)
        return (0);

    scene = malloc(sizeof(t_scene));
    if (scene == NULL)
        return (0);

    mlib = init_mlib();
    if (mlib == NULL)
        return (0);

    keys = init_key();
    if (keys == NULL)
        return (0);

	sprites = init_sprites("textures/Wall_North.png", "textures/Wall_South.png","textures/Wall_West.png","textures/Wall_East.png");
    if (sprites == NULL)
    {
        printf("Error sprite\n");
        return (0);
    }

	scene->map.matrix = matrix;
	scene->map.height_matrix = 20;
	scene->map.width_matrix = 40;
	scene->map.height_map = 20 * SIZE_WALL;
	scene->map.width_map = 40 * SIZE_WALL;
	scene->map.size_wall = SIZE_WALL;

	scene->player.coord_ini = get_player_coord(matrix);
	scene->player.pos = get_player_coord(matrix);

    scene->player.pos2D = convert_coord_for_2D(scene->player.pos, scene->map.width_map, scene->map.height_map);


	scene->player.dir = get_player_orientation(matrix);
	scene->player.speed = 1.0f;
	scene->sky_color = 0x2211FF;
	scene->floor_color = 0x556B2F;
	scene->mini_map = 1;

    general->keys = keys;
    general->mlib = mlib;
    general->scene = scene;
    general->sprites = sprites;	

    if (load_texture_png(general) == 0)
    {
		printf("sdgsdfgdsfg\n");
        return (0);
    }

	printf("WIDTH = %d HEIGTH = %d\n", WIDTH, HEIGHT);
	print_player(scene->player);
	printMap(scene->map);


	init_window(general, mlib);

	return (0);
}