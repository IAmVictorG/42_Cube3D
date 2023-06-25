
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

/* Renvoie le nombre de ligne du fichier a parser */
int get_size_file(const char *filename)
{
    int     fd;
    char    *line = NULL;
    int     size_file;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return -1;
    size_file = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        size_file++;
        free(line);
    }
    close(fd);
    if (line)
        free(line);
    return (size_file);
}

/* Copie le fichier a parser dans un tableau 2D de char */
char **copy_file(const char *filename, int size_file)
{
    int     fd;
    char    *line = NULL;
    char    **copy;
    int     i;

    copy = (char **) malloc(sizeof(char *) * (size_file + 1));
    if (copy == NULL)
        return (NULL);

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (NULL);
    i = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        copy[i] = line;
        i++;
    }
    copy[i] = NULL;
    close(fd);
    if (line)
        free(line);
    return (copy);
}

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
        filename = "map1.cub";

        int size_file;
        size_file = get_size_file(filename);
        printf("size_file : %d\n", size_file);

        char **copy;
        copy = copy_file (filename, size_file);

        print_tab(copy);

        /*

        int ind_map;
        ind_map = find_map(filename);
        printf("Ind of map : %d\n", ind_map);

        int h_map;
        h_map = height_map(filename, ind_map);
        printf("Size of map : %d\n", h_map);
        
        printf("-----------------------------\n");

        char **map_uncompleted;
        map_uncompleted = map_creator(filename, h_map, ind_map);

        (void) map_uncompleted;
        */
        /*
        t_scene *scene;
        scene = malloc(sizeof(t_scene));
        scene->map.map = map_uncompleted;

        display_map(scene);

        printf("check first last one = %d\n", check_last_first_one(map_uncompleted));
        
        int largest_line;
        largest_line = find_largest_line(map_uncompleted);
        printf("largest line = %d\n", largest_line);
        */

    }

    return 0;
}

