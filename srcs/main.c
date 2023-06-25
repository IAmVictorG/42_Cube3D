
#include "../header.h"


int read_rt_file(const char *filename, t_scene *scene)
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
}

/*
void init_t_scene(t_scene *scene)
{


}
*/

int main(int argc, char const *argv[])
{
    (void) argc;
    (void) argv;

    /* SCOPE TESTS VICTOR */
    /*{
        t_scene *scene;
        scene = malloc(sizeof(t_scene));

        read_rt_file("map1.cub", scene);
        printf("%s\n", scene->sprite.north);
    }*/


    /* SCOPE TESTS FX */
    {
        char const *filename;
        filename = "map0.cub";

        printf("Map at line : %d\n", find_map(filename));



    }

    //printf("%s\n", scene->sprite.north);


    /*
    char **map;

    map = map_creator("map0.cub"); 

    scene->map.map = map;
    scene->map.height_map = 42;

    display_map(scene);
    */

    //printf("parse first wall = %d\n", parse_first_wall("111111111111111"));



    return 0;
}

