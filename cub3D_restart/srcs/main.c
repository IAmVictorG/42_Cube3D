#include "../header.h"


t_general    *create_general (char **walls)
{
    t_general   *general;

    general = (t_general *) malloc (sizeof(t_general));
    if (general == NULL)
    {
        printf("Error : malloc allocation.\n");
        return (0);
    }
    else
    {
        printf("%s : %p (%lu bytes)\n", "general", general, sizeof(t_general));
    }
    general->scene = malloc(sizeof(t_scene));
    if (general->scene == NULL)
        return (0);
    else
    {
        printf("%s : %p (%lu bytes)\n", "scene", general->scene, sizeof(t_scene));
    }
    general->mlib = init_mlib();
    if (general->mlib == NULL)
        return (0);
    general->keys = init_key();
    if (general->keys == NULL)
        return (0);
    else
    {
        printf("%s : %p (%lu bytes)\n", "keys", general->keys, sizeof(t_keys));
    }
	general->sprites = init_sprites(walls[0], walls[1], walls[3], walls[2]);
    if (general->sprites == NULL)
    {
        printf("Error sprite\n");
        return (0);
    } 
    return general;
}

int feed_the_scene (t_general *general, char **copy_of_file, t_coord floor, t_coord ceil)
{
    int end;

    end = parser(copy_of_file);

    if (init_map(&general->scene->map, copy_of_file, end) == 0)
    {
        printf("Error init_map\n");
        return (0);
    }    

    general->scene->floor_color = create_trgb(0, floor.x, floor.y, floor.z);
    general->scene->sky_color = create_trgb(0, ceil.x, ceil.y, ceil.z);


    general->scene->player.coord_ini = get_player_coord(general->scene->map.matrix);
	general->scene->player.pos = get_player_coord(general->scene->map.matrix);
    general->scene->player.pos2D = convert_coord_for_2D(general->scene->player.pos);
	general->scene->player.dir = get_player_orientation(general->scene->map.matrix);

    general->scene->player.speed = 0.1f;
    general->scene->mini_map = 1;

    return (1);

}

void    free_general(t_general *general)
{
    ft_free_tabs(general->scene->map.matrix);
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

void chk_file (int argc, char *argv[])
{
    int size_file;

    if (argc != 2)
    {
        printf("Error : Invalid number of arguments.\n");
        exit (0);
    }
    if (arg_manager(argv[1]) == 0)
        exit (0);
    size_file = get_size_file(argv[1]);
    if (size_file <= 0)
    {
        printf("Error : File is empty or not a text file.\n");
        exit (0);
    }
}


int main (int argc, char *argv[])
{
    char    **copy_of_file;
    char    **walls;

    char    *floor_s;
    char    *ceil_s;

    t_coord floor;
    t_coord ceil;

    int     end;

    t_general   *general;


    chk_file(argc, argv);

    copy_of_file = copy_file(argv[1]);
    if (copy_of_file == NULL)
        return (0);

    end = parser(copy_of_file);
    walls = walls_manager(copy_of_file);
    if (walls == NULL)
        return (0);

    floor_s = get_floor_ceil(copy_of_file, 'F');
    if (floor_s == NULL)
    {
        ft_free_tabs(copy_of_file);
        ft_free_tabs(walls);
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

    general = create_general(walls);

    if (general == NULL)
        return (0);




    if (feed_the_scene(general, copy_of_file, floor, ceil) == 0)
    {
        //printf("Error : impossible to initialize map.\n");
        return (0);
    }



    if (load_texture_png(general) == 0)
    {
		printf("Error : Imposible to load textures\n");
        return (0);
    }




    print_scene(general->scene);
    print_sprites(general->sprites);



	init_window(general);

    ft_free_tabs(copy_of_file);
    ft_free_tabs(walls);
    free(floor_s);
    free(ceil_s);
    
    free_general(general);

	return (0);
}