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
    printf("    size_wall = %d\n", SIZE_WALL);
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
    printf("y = %d ", coord.y);
    printf("z = %d\n", coord.z);
    //printf("\n");
}

void    print_player(t_player player)
{
    printf("----PLAYER----\n");
    printCoord(player.coord_ini);
    printf("pos : ");
    printCoord(player.pos);
    printf("pos2D : \n");
    printCoord(player.pos2D);
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
				coord_ini.y = lin * SIZE_WALL + SIZE_WALL / 2;
				coord_ini.x = col * SIZE_WALL + SIZE_WALL / 2;

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


int arg_manager (char *file_path)
{
    char    *file_name;
    char    *extension;

    file_name = NULL;
    extension = NULL;

    if (filename_is_valid(file_path) == 0)
    {
        printf("Error : Invalid file.\n");
        return (0);
    }
    if (file_exists(file_path) == 0)
    {
        printf("Error : Impossible to open file : %s.", file_path);
        return (0);
    }
    return (1);
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


char **walls_manager (char **copy_of_file)
{
    char    **walls;

    walls = (char **) ft_calloc(5, sizeof(char *)); // malloc(5 * sizeof(char *));
    // walls[0] = NULL;
    // walls[1] = NULL;
    // walls[2] = NULL;
    // walls[3] = NULL;
    // walls[4] = NULL;

    walls[0] = get_wall(copy_of_file, 'N', 'O');
    if (walls[0] == NULL)
    {
        printf("Error : No Wall North.\n");
        free(walls);
        return (NULL);
    }
    walls[1] = get_wall(copy_of_file, 'S', 'O');
    if (walls[1] == NULL)
    {
        printf("Error : No Wall South.\n");
        ft_free_tabs(walls);
        return (NULL);
    }    
    walls[2] = get_wall(copy_of_file, 'E', 'A');
    if (walls[2] == NULL)
    {
        printf("Error : No Wall East.\n");
        ft_free_tabs(walls);
        return (NULL);
    }    
    walls[3] = get_wall(copy_of_file, 'W', 'E');
    if (walls[3] == NULL)
    {
        printf("Error : No Wall West.\n");
        ft_free_tabs(walls);
        return (NULL);
    }
    //print_tab(walls);
    return (walls);
}

int walls_manager_exists (char **walls)
{
    int i;

    i = 0;
    while (walls[i] != NULL)
    {
        if (file_exists(walls[i]) == 0)
        {
            printf("Error : Impossible to open %s\n", walls[i]);
            return (0);
        }
        i++;
    }
    return (1);
}

int main (int argc, char *argv[])
{
    int     size_file;
    char    **copy_of_file;
    char    **walls;

    char    *floor_s;
    char    *ceil_s;

    t_coord floor;
    t_coord ceil;

    // int     floor_i;
    // int     ceil_i;

    if (argc != 2)
    {
        printf("Error : Invalid number of arguments.\n");
        return (0);
    }
    if (arg_manager(argv[1]) == 0)
        return (0);

    size_file = get_size_file(argv[1]);
    if (size_file <= 0)
    {
        printf("Error : File is empty.\n");
        return (0);
    }
    copy_of_file = copy_file(argv[1], size_file);

    walls = walls_manager(copy_of_file);

    if (walls_manager_exists(walls) == 0)
    {
        return (0);
    }


    floor_s = get_floor_ceil(copy_of_file, 'F');
    ceil_s = get_floor_ceil(copy_of_file, 'C');

    // printf("F = (%s)\n", floor_s);
    // printf("C = (%s)\n", ceil_s);


    floor = set_vector(floor_s);
    ceil = set_vector(ceil_s);

    printCoord(floor);
    printCoord(ceil);


    //ft_free_tabs(walls_manager);
    ft_free_tabs(copy_of_file);




    // printf("NO = %s\n", get_wall(copy_of_file, 'N', 'O'));
    // printf("SO = %s\n", get_wall(copy_of_file, 'S', 'O'));
    // printf("NE = %s\n", get_wall(copy_of_file, 'W', 'E'));
    // printf("EA = %s\n", get_wall(copy_of_file, 'E', 'A'));


    return (42);

    t_general   *general;

    t_scene     *scene;
    t_mlib      *mlib;
    t_sprites   *sprites;
    t_keys      *keys;

    int         heigth_matrix = 20;
    int         width_matrix = 40;
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
    


    // int         heigth_matrix = 32;
    // int         width_matrix = 150;
    // char *matrix[33];
    // matrix[0] = "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
    // matrix[1] = "110000000000000100001000001000111100010010010001101000110001000110010100010000110110101111011000000000111000000011000110011100010000100000010000000011";
    // matrix[2] = "100010001000011010000101000100111000011100100000000000000110100100000000010000000100010000101001010100011000010000101001100000100010011100010000001001";
    // matrix[3] = "110000110000101010100000000001001001000100010000000011100101000000000100000000010000000100100000010000010000011000010000001100111000000100101000001101";
    // matrix[4] = "101000000111100000000000000000000101000110010011000101110101000000000000000000001100010000100000100100100011000000001010000000010000000110000100010001";
    // matrix[5] = "110000001000100100000100000010101101101010001000000000001001011000001010101010000010000000001000000111001100100000110001001001000011000000000101001001";
    // matrix[6] = "100000100000101100101000100101010011000100010000010000000001100101001010000010000000000011000100011100000101100000100110010100100010001001001000010101";
    // matrix[7] = "110000000000011001100100000001010100000000101010000000010000100000000000011001010000100100010001000000000000010110000100111011010000100000110011100011";
    // matrix[8] = "110111010100000110000001010001000000100100000001000001010110001100000000000010100000001000100001111000011010000010111000111100010100100011010011101001";
    // matrix[9] = "100000110010101001000101000000001101000000110000100100010010010000010101101110100001100001001001110110011000001010010001000011100000100011100000010011";
    // matrix[10] = "110001000000000000100100000001101000010100100000110000000100000101010101000000001000000111000000010100001100001001101010101101011110010000110010110001";
    // matrix[11] = "100000111011000100000011011100010110110000100000011101001010000000100100111010100000011001000001001E00010001101011110001001100010100000000000001001111";
    // matrix[12] = "100001101001010100000000000100011100000000000010100000110100101000010000010000010001000010100100010010100000110110000000000011000000001000100001010001";
    // matrix[13] = "100000000000000000001000000001001000000011010100001110001100000000110001100000000011001010000011000010000000000001010000110110000101000110111110101101";
    // matrix[14] = "100010000000001001110001010000001000101000010000000000100100000100101001101100111010100000111010001010100010100111101000100000010000010010010011100011";
    // matrix[15] = "100000000000010111000100011001010001000000101000101000000101000000101001000011011000010011000001010001000111001101100000010100010000001001101000010111";
    // matrix[16] = "101010000001000010100011001010010001111000010110010100110001000111101001001001101000100100100010100101101010000000101001000001001000010101011000111001";
    // matrix[17] = "110000010000000000000010000011001000111100100010010000000010000010100001000100010010001000000100010110000000001001000001100100000101100110000011001101";
    // matrix[18] = "101010001001001101100001100101010010000001010000010000101000100001000000100010010100001010001010100000000100000110000001001000000101001000001001000001";
    // matrix[19] = "101001001000000000000000000001100000001000000100010010000110010100100010001001101010111000011100010100000000010100010100000101000011010001010101011101";
    // matrix[20] = "100001001000001000101000010001000001000000000100000100001000000000000000000101100001010001000100000000101100000001001010001010011001011001000010100001";
    // matrix[21] = "100011001001100100010010000010000000000000011000000001011000000010000011010000000100111010100100001000011100110000010001011101111100000100100000100101";
    // matrix[22] = "101001000000010000110000000001000001011010001110101010001000010011010110100010000000000001100000001000100010001101000001100000100001101010011000000001";
    // matrix[23] = "110001000001010001000000010100000010001000011000111000000100000110100010000000011001000000000010000000110011001001000100010100001011000101100100000001";
    // matrix[24] = "110001000001010001010000000000001100101000010000010000010000000000110000010000001110001100000001100000001001001001101011000100000010011000000111011001";
    // matrix[25] = "101101000000000000100001000110000100000000011000111000001101001100100001000000010001011010101001001000101000010000001001010010000001000100000000000001";
    // matrix[26] = "100100001010000000000000000000110100100000110100001100100011000110011101111000001010110001000000100000010000011100110001010000000000011100010000000001";
    // matrix[27] = "100011000010010100001010000101000010000010000000000000110000000011010001010011101101100011000000011101000001001100010001010001001000000000000000000111";
    // matrix[28] = "110011000010001000010010011000100101001000100000010000010011000000001000000010100100001000111110110110110001100101110010001001001001000000100100000001";
    // matrix[29] = "100001010001000000001010001000100010000010001000100010000001100100010000001001010000000000101100001001010000000000100111001000000000001011000100000001";
    // matrix[30] = "100000001000010100000100011001100001100110011110010001001000000101000100001000000100111100000000000100001100000011100110100100100101000000100001000101";
    // matrix[31] = "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
    // matrix[32] = NULL;






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
	scene->map.height_matrix = heigth_matrix;
	scene->map.width_matrix = width_matrix;
	scene->map.height_map = heigth_matrix * SIZE_WALL;
	scene->map.width_map = width_matrix * SIZE_WALL;

	scene->player.coord_ini = get_player_coord(matrix);
	scene->player.pos = get_player_coord(matrix);

    scene->player.pos2D = convert_coord_for_2D(scene->player.pos);

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