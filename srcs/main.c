#include "../header.h"

char *get_filename(const char *file_path)
{
    char    *filename;
    int     i;
    int     filename_len;

    i = ft_strlen(file_path);
    filename_len = 0;
    while (i > 0 && file_path[i] != '/')
    {
        i--;
        filename_len ++;
    }
    if (file_path[i] == '/')
    {
        i++;
    }
    filename = ft_substr(file_path, i, filename_len);
    return (filename);
}

char    *get_extension(char *filename)
{
    int     filename_len;
    int     extension_len;
    int     i;
    
    filename_len = ft_strlen(filename);
    i = filename_len;
    extension_len = 0;
    while (filename[i] != '.' && i > 0)
    {
        i--;
        extension_len ++;
    }
    if (i == 0 || i == filename_len - 1 )
    {
        return (NULL);
    }
    return (ft_substr(filename, filename_len - extension_len, extension_len));
}

int filename_is_valid(const char *file_path)
{
    char    *extension;
    char    *filename;

    filename = get_filename(file_path);
    extension = get_extension(filename);
    if (filename == NULL || extension == NULL)
        return (1);
    if (ft_strncmp(extension, ".cub", 4) != 0)
    {
        free(filename);
        free(extension);
        return (0);
    }

    free(filename);
    free(extension);
    return (1);
}

int main(int argc, char const *argv[])
{

    t_scene     *scene;
    t_mlib      *mlib;
    t_sprites   *sprites;
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

    sprites = malloc(sizeof(t_sprites));
    if (sprites == NULL)
    {
        printf("Error\n");
        return (0);
    }


    t_sprite    *wall_north = malloc(sizeof(t_sprite));
    t_sprite    *wall_south = malloc(sizeof(t_sprite));
    t_sprite    *wall_east = malloc(sizeof(t_sprite));
    t_sprite    *wall_west = malloc(sizeof(t_sprite));


    sprites->wall_north = wall_north;
    sprites->wall_south = wall_south;
    sprites->wall_east = wall_east;
    sprites->wall_west = wall_west;



    scene = malloc(sizeof(t_scene));
    if (scene == NULL)
        return (0);


    int end_part_1 = parser(sprites, scene, copy);






    if (map_parser(scene, copy, end_part_1) == 0)
    {
        printf("Error\n");
        return (0);

    }

    mlib = malloc(sizeof(t_mlib));
    if (mlib == NULL)
        return (0);



    scene->player.coord_ini = get_player_coord(scene->map.matrix);

    scene->player.dir = get_player_orientation(scene->map.matrix, scene->player.coord_ini);
    
    scene->map.size_wall = get_size_wall(scene->map.width_map, scene->map.height_map);
    
    scene->player.pos = get_player_position(scene->player.coord_ini, scene->map.size_wall);

    scene->player.speed = 0.1f;

    //print_scene(scene);

    printf("------------------------------------\n");


    init_window(mlib, scene, sprites);



    
    ft_free_tabs(scene->map.matrix);

    ft_free_tabs(copy);
    free((void *) wall_north->path);
    free(wall_north);
    free((void *) wall_south->path);
    free(wall_south);
    free((void *) wall_east->path);
    free(wall_east);
    free((void *) wall_west->path);
    free(wall_west);
    free(sprites);

    //free(mlib->data.addr);
    
    free(scene);
    return (42);

    return 0;
}

