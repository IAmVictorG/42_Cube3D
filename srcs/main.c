
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

int main(int argc, char const *argv[])
{
    (void) argc;
    (void) argv;


    t_scene *scene;

    scene = malloc(sizeof(t_scene));
    //char *map[6];
    
    //parse_map(map);

    read_rt_file("map1.cub", scene);
    printf("%s\n", scene->sprite.north);

    char **map;

    map = map_creator("map0.cub"); 
    display_map(map);




    return 0;
}

