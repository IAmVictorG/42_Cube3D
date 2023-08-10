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
    general->scene->player.speed = 0.1f * SIZE_WALL;
    general->scene->mini_map = 1;
    if (load_texture_png(general) == 0)
    {
		printf("Error : Imposible to load textures\n");
        return (0);
    }
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


void    free_main(char **copy_of_file, char **walls, char *ceil_s, char *floor_s)
{
    ft_free_tabs(copy_of_file);
    ft_free_tabs(walls);
    free(ceil_s);
    free(floor_s);
}

void    get_ce_fl_colors(char **copy_of_file, char **walls, char **ce_fl_colors)
{

    ce_fl_colors[1] = get_floor_ceil(copy_of_file, 'F');
    if (ce_fl_colors[1] == NULL)
    {
        ft_free_tabs(copy_of_file);
        ft_free_tabs(walls);
        exit (0);
    }

    ce_fl_colors[0] = get_floor_ceil(copy_of_file, 'C');
    if (ce_fl_colors[0] == NULL)
    {
        ft_free_tabs(copy_of_file);
        ft_free_tabs(walls);
        free(ce_fl_colors[1]);
        printf("Error : Invalid ceil color.\n");
        exit (0);
    }

}

// void    get_ceil_color_vec (char **copy_of_file, char **walls, char **ce_fl_colors, t_coord *ceil_coord_vec)
// {
//     t_coord ceil_vec;
//     ceil_vec = set_vector(ce_fl_colors[0]);
//     if (check_coord_color(ceil_vec) == 0)
//     {
//         ft_free_tabs(copy_of_file);
//         ft_free_tabs(walls);
//         free(ce_fl_colors[0]);
//         free(ce_fl_colors[1]);
//         printf ("Error : Invalid floor color vector.\n");
//         return (0);
//     }

//     return (ceil_vec);
// }


int main (int argc, char *argv[])
{
    char    **copy_of_file;
    char    **walls;
    char    *ce_fl_colors[2];
    t_coord ce_fl_colors_vec[2];
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
    get_ce_fl_colors(copy_of_file, walls, ce_fl_colors);
    ce_fl_colors_vec[1]= set_vector(ce_fl_colors[1]);
    if (check_coord_color(ce_fl_colors_vec[1]) == 0)
    {
        ft_free_tabs(copy_of_file);
        ft_free_tabs(walls);
        free(ce_fl_colors[1]);
        free(ce_fl_colors[0]);
        printf ("Error : Invalid floor color vector.\n");
        return (0);
    }
    ce_fl_colors_vec[0]= set_vector(ce_fl_colors[0]);
    if (check_coord_color(ce_fl_colors_vec[0]) == 0)
    {
        ft_free_tabs(copy_of_file);
        ft_free_tabs(walls);
        free(ce_fl_colors[1]);
        free(ce_fl_colors[0]);
        printf ("Error : Invalid ceil color vector.\n");
        return (0);
    }
    if (map_parser(copy_of_file, end) == 0)
    {
        ft_free_tabs(copy_of_file);
        ft_free_tabs(walls);
        free(ce_fl_colors[1]);
        free(ce_fl_colors[0]);
        //printf("Error : map_parser.\n");
        return (0);
    }
    general = create_general(walls);
    if (general == NULL)
        return (0);
    if (feed_the_scene(general, copy_of_file, ce_fl_colors_vec[1], ce_fl_colors_vec[0]) == 0)
        return (0);
    print_scene(general->scene);
    print_sprites(general->sprites);
	init_window(general);
    free_main(copy_of_file, walls, ce_fl_colors[1], ce_fl_colors[0]);
    free_general(general);
	return (0);
}