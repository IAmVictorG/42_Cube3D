
#include "../header.h"

/*int read_rt_file(const char *filename, t_scene *scene)
{
    int fd;
    char *line = NULL;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return -1;
    while ((line = get_next_line(fd)) != NULL)
    {
        parse_line(scene, line);
    }
    close(fd);
    if (line)
        free(line);
    return 0;
}*/







int main(int argc, char const *argv[])
{
    (void) argc;
    (void) argv;

    /* SCOPE TESTS VICTOR */
    {
        t_scene     *scene;
        t_mlib      *mlib;
        t_sprites   *sprites;
        int         size_file;
        char const  *filename;
        char        **copy;

        filename = "map2.cub";
        scene = malloc(sizeof(t_scene));
        if (scene == NULL)
            return (0);

        size_file = get_size_file(filename);
        copy = copy_file (filename, size_file);

        sprites = malloc(sizeof(t_sprites));

        int end_part_1 = parser(sprites, scene, copy);        
        map_parser(scene, copy, end_part_1);

        mlib = malloc(sizeof(t_mlib));
        if (mlib == NULL)
            return (0);

        
        parser(sprites, scene, copy);

        scene->player.coord_ini = get_player_coord(scene->map.matrix);

        scene->player.dir = get_player_orientation(scene->map.matrix, scene->player.coord_ini);
        
        scene->map.size_wall = get_size_wall(scene->map.width_map, scene->map.height_map);
        
        scene->player.pos = get_player_position(scene->player.coord_ini, scene->map.size_wall);

        scene->player.speed = scene->map.size_wall * 0.02f;

        //print_scene(scene);

        printf("------------------------------------\n");

        /*create_ray(scene, 0, 0);
        create_ray(scene, 1920, 0);
        create_ray(scene, 0, 1080);

        create_ray(scene, 1920, 1080);*/

        init_window(mlib, scene, sprites);

        ft_free_tabs(copy);
        ft_free_tabs(scene->map.matrix);
    }

    /*SCOPE FX*/
    {

    }


    return 0;
}

