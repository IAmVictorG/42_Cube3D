#include "../header.h"


t_general    *create_general (char **walls)
{
    t_general   *general;

    general = (t_general *) malloc (sizeof(t_general));
    if (general == NULL)
    {
        printf("Error : malloc allocation.\n");
        return NULL;
    }
    else
    {
        printf("%s : %p (%lu bytes)\n", "general", general, sizeof(t_general));
    }
    general->scene = malloc(sizeof(t_scene));
    if (general->scene == NULL)
    {
        free(general);
        return NULL;
    }
    else
    {
        printf("%s : %p (%lu bytes)\n", "scene", general->scene, sizeof(t_scene));
    }
    general->mlib = init_mlib();
    if (general->mlib == NULL)
    {
        free (general->scene);
        free (general);
        return NULL;
    }
    general->keys = init_key();
    if (general->keys == NULL)
    {
        free(general->mlib);
        free (general->scene);
        free (general);
        return NULL;
    }
    else
    {
        printf("%s : %p (%lu bytes)\n", "keys", general->keys, sizeof(t_keys));
    }
	general->sprites = init_sprites(walls[0], walls[1], walls[3], walls[2]);
    if (general->sprites == NULL)
    {
        free(general->keys);
        free(general->mlib);
        free (general->scene);
        free (general);
        printf("Error sprite\n");
        return NULL;
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
    print_scene(general->scene);
    print_sprites(general->sprites);
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

t_coord    set_color_vec(char **copy_of_file, char **walls, char **colors, char *color)
{
    t_coord color_vec;

    color_vec = set_vector(color);
    if (check_coord_color(color_vec) == 0)
    {
        ft_free_tabs(copy_of_file);
        ft_free_tabs(walls);
        free(colors[1]);
        free(colors[0]);
        printf ("Error : Invalid color.\n");
        exit (0);
    }
    return (color_vec);
}

void    parse_the_map(char **copy_of_file, char **walls, char **ce_fl_colors)
{
    if (map_parser(copy_of_file, parser(copy_of_file)) == 0)
    {
        ft_free_tabs(copy_of_file);
        ft_free_tabs(walls);
        free(ce_fl_colors[1]);
        free(ce_fl_colors[0]);
        exit (0);
    }
}


int main (int argc, char *argv[])
{
    char        **copy_of_file;
    char        **walls;
    char        *ce_fl_colors[2];
    t_coord     ce_fl_colors_vec[2];
    t_general   *general;

    chk_file(argc, argv);
    copy_of_file = copy_file(argv[1]);
    parser(copy_of_file);
    walls = walls_manager(copy_of_file);
    if (walls == NULL)
        return (0);
    get_ce_fl_colors(copy_of_file, walls, ce_fl_colors);
    ce_fl_colors_vec[1] = set_color_vec(copy_of_file, walls, ce_fl_colors, ce_fl_colors[1]);
    ce_fl_colors_vec[0] = set_color_vec(copy_of_file, walls, ce_fl_colors, ce_fl_colors[0]);
    parse_the_map(copy_of_file, walls, ce_fl_colors);
    general = create_general(walls);
    if (general == NULL)
        return (0);
    if (feed_the_scene(general, copy_of_file, ce_fl_colors_vec[1], ce_fl_colors_vec[0]) == 0)
        return (0);
	init_window(general);
    free_main(copy_of_file, walls, ce_fl_colors[1], ce_fl_colors[0]);
    free_general(general);
	return (0);
}