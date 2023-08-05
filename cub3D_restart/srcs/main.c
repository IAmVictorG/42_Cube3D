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

    //printf("path = %s\n", path);
    t_sprite    *wall;

    wall = (t_sprite *) malloc(sizeof(t_sprite));
    if (wall == NULL)
    {
        return (NULL);
    }
    wall->path = path;

    //print_sprite(wall);
    //printf("%s\n", wall->path);
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

void    free_general(t_general *general)
{
    free(general->sprites->wall_east);
    free(general->sprites->wall_north);
    free(general->sprites->wall_south);
    free(general->sprites->wall_west);
    free(general->sprites);
    free(general->keys);
    free(general->mlib);
    free(general->scene);
    free(general);

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

    int     end;

    t_general   *general;

    t_scene     *scene;
    t_mlib      *mlib;
    t_sprites   *sprites;
    t_keys      *keys;

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
        printf("Error : File is empty or not a text file.\n");
        return (0);
    }
    copy_of_file = copy_file(argv[1], size_file);
    if (copy_of_file == NULL)
    {
        printf("Error : Error with configuration file.\n");
        return (0);
    }

    end = parser(copy_of_file);

    walls = walls_manager(copy_of_file);
    if (walls == NULL)
    {
        ft_free_tabs(copy_of_file);
        printf("Error : Walls management issue.");
        return (0);
    }

    if (walls_manager_exists(walls) == 0)
    {
        ft_free_tabs(copy_of_file);
        ft_free_tabs(walls);
        printf("Error : Issue with wall file.\n");
        return (0);
    }

    floor_s = get_floor_ceil(copy_of_file, 'F');
    if (floor_s == NULL)
    {
        ft_free_tabs(copy_of_file);
        ft_free_tabs(walls);
        printf("Error : Floor color not found.\n");
        return (0);
    }

    ceil_s = get_floor_ceil(copy_of_file, 'C');
    if (ceil_s == NULL)
    {
        ft_free_tabs(copy_of_file);
        ft_free_tabs(walls);
        free(floor_s);
        printf("Error : Ceil color not found.\n");
        return (0);
    }

    floor = set_vector(floor_s);
    if (check_coord_color(floor) == 0)
    {
        ft_free_tabs(copy_of_file);
        ft_free_tabs(walls);
        free(floor_s);
        free(ceil_s);
        printf ("Error : Invalid floor color.\n");
        return (0);
    }

    ceil = set_vector(ceil_s);
    if (check_coord_color(ceil) == 0)
    {
        ft_free_tabs(copy_of_file);
        ft_free_tabs(walls);
        free(floor_s);
        free(ceil_s);
        printf ("Error : Invalid ceil color.\n");
        return (0);
    }

    if (map_parser(copy_of_file, end) == 0)
    {
        ft_free_tabs(copy_of_file);
        ft_free_tabs(walls);
        free(floor_s);
        free(ceil_s);
        //printf("Error : map_parser.\n");
        return (0);
    }

    /*LEAKS PROOF UNTIL HERE*/

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

	sprites = init_sprites(walls[0], walls[1], walls[3], walls[2]);

    if (sprites == NULL)
    {
        printf("Error sprite\n");
        return (0);
    }  

    if (init_map(&scene->map, copy_of_file, end) == 0)
    {
        printf("Error init_map\n");
        return (0);

    }

    scene->floor_color = create_trgb(0, floor.x, floor.y, floor.z);
    scene->sky_color = create_trgb(0, ceil.x, ceil.y, ceil.z);

    scene->player.coord_ini = get_player_coord(scene->map.matrix);
	scene->player.pos = get_player_coord(scene->map.matrix);
    scene->player.pos2D = convert_coord_for_2D(scene->player.pos);
	scene->player.dir = get_player_orientation(scene->map.matrix);

    scene->player.speed = 0.1f;
    scene->mini_map = 1;



    general->keys = keys;
    general->mlib = mlib;
    general->scene = scene;
    general->sprites = sprites;

    if (load_texture_png(general) == 0)
    {
		printf("Error : Imposible to load textures\n");
        return (0);
    }


    //printf("ICI %c\n", general->scene->map.matrix[0][0]);

    print_scene(general->scene);
    print_sprites(general->sprites);



	init_window(general, mlib);

    ft_free_tabs(copy_of_file);
    ft_free_tabs(walls);
    free(floor_s);
    free(ceil_s);
    ft_free_tabs(general->scene->map.matrix);
    free_general(general);

	return (0);
}