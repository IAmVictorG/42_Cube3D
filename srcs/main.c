#include "../header.h"

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


t_mlib  *init_mlib()
{
    t_mlib  *mlib;

    mlib = (t_mlib *) malloc(sizeof(t_mlib));
    if (mlib == NULL)
        return (NULL);
    
    mlib->utils.mlx = mlx_init();


    return (mlib);
}

void    init_scene (t_scene *scene)
{

    scene->player.coord_ini = get_player_coord(scene->map.matrix);
    scene->player.dir = get_player_orientation(scene->map.matrix, scene->player.coord_ini);
    scene->map.size_wall = get_size_wall(scene->map.width_map, scene->map.height_map);
    scene->player.pos = get_player_position(scene->player.coord_ini, scene->map.size_wall);
    scene->player.speed = 0.1f;
    scene->mini_map = 1;
}

int main(int argc, char const *argv[])
{

    t_general   *general;
    t_scene     *scene;
    t_mlib      *mlib;
    t_sprites   *sprites;
    t_keys      *keys;

    int         size_file;
    char const  *file_path;
    char        **copy;

    if (argc != 2)
    {
        printf("Invalid noumber of arguments\n");
        return (0);
    }
    file_path = argv[1];

    if (filename_is_valid(file_path) == 0)
    {
        printf("Error\n");
        return (0);       
    }

    size_file = get_size_file(file_path);
    if (size_file == -1)
    {
        printf("Error\n");
        return (0);
    }

    copy = copy_file (file_path, size_file);

    sprites = init_sprites("sprites/Wall_North.png", "sprites/Wall_South.png","sprites/Wall_West.png","sprites/Wall_East.png");
    if (sprites == NULL)
    {
        printf("Error\n");
        return (0);
    }

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

    int end_part_1 = parser(sprites, scene, copy);

    if (map_parser(copy, end_part_1) == 0)
    {
        printf("Error\n");
        return (0);
    }

    if (init_map(&scene->map, copy, end_part_1) == 0)
    {
        printf("Error\n");
        return (0);

    }
    init_scene(scene);

    general->keys = keys;
    general->mlib = mlib;
    general->scene = scene;
    general->sprites = sprites;

    load_texture_png(general);
    init_window(general, mlib);
    
    ft_free_tabs(scene->map.matrix);
    ft_free_tabs(copy);
    free(sprites);
    free(keys);
    free(scene);
    free(general);    

    return 0;
}

