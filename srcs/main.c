
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

int map_parser(t_scene *scene, char **copy, int end_parse_1)
{
    int     ind_map;
    int     h_map;
    int     chk_EOF;
    char    **map_uncompleted;
    int     caract_ok;
    int     w_map;
    char    **matrix;
    int     chk_walls;
    int     chk_player;


    (void) scene;
    //(void) h_map;

    ind_map = find_map(copy, end_parse_1);
    if (ind_map == -1)
    {
        printf("ERROR 1 : Inconsistant map.\n");
        return (0);
    }

    h_map = height_map(copy, ind_map);
    if (h_map <= 2)
    {
        printf("ERROR 2 : Heigth map deficient.\n");
        return (0);
    }
    scene->map.height_map = h_map;

    chk_EOF = check_EOF(copy, ind_map, h_map);
    if (chk_EOF == 0)
    {
        printf("ERROR 3 : Inconsistant map.\n");
        return (0);
    }

    map_uncompleted = map_creator(copy, h_map, ind_map);
    if (map_uncompleted == NULL)
    {
        printf("ERROR 4 : Impossible to create map.\n");
        return (0);
    }

    caract_ok = check_caract_map(map_uncompleted);
    if (caract_ok == 0)
    {
        printf("ERROR 5 : Prohibited character in map.\n");
        return (0);
    }

    w_map = find_largest_line(map_uncompleted);
    if (w_map < 3)
    {
        printf("ERROR 6 : Width map deficient.\n");
        return (0);
    }
    scene->map.width_map = w_map;

    matrix = matrix_creator(map_uncompleted, h_map, w_map);
    if (matrix == NULL)
    {
        printf("ERROR 7 : Impossible to create matrix.\n");
        return (0);
    }
    scene->map.matrix = matrix;

    chk_walls = parse_first_wall(matrix[0]);
    if (chk_walls == 0)
    {
        printf("ERROR 8 : Inconsistent first wall.\n");
        return (0);
    }

    chk_walls = check_last_first_one(matrix);
    if (chk_walls == 0)
    {
        printf("ERROR 9 : Inconsistent middle wall.\n");
        return (0);
    }

    chk_walls = parse_first_wall(matrix[h_map - 1]);
    if (chk_walls == 0)
    {
        printf("ERROR 10 : Inconsistent last wall.\n");
        return (0);
    }

    chk_player = check_player(matrix);
    if (chk_player == 0)
    {
        printf("ERROR 11 : Inconsistent player.\n");
        return (0);
    }

    chk_walls = wall_inspector(matrix, h_map, w_map);
    if (chk_walls == 0)
    {
        printf("ERROR 12 : Leaks in wall.\n");
        return (0);
    }

    return (-1561);

}

void    printVec(t_vec vector)
{
    printf("x = %f, ", vector.x);
    printf("y = %f, ", vector.y);
    printf("z = %f", vector.z);
    printf("\n");

}

void    printCoord(t_coord coord)
{
    printf("Coord x = %d ", coord.x);
    printf("Coord y = %d", coord.y);
    printf("\n");

}

void    print_player(t_player player)
{
    printf("----PLAYER----\n");
    printCoord(player.coord_ini);
    printf("pos : ");
    printVec(player.pos);
    printf("dir : ");
    printVec(player.dir);
    printf("speed = %f\n", player.speed);
    printf("\n");

}

void    print_scene(t_scene *scene)
{

    printf("%s\n", scene->sprite.north);
    printf("%s\n", scene->sprite.south);
    printf("%s\n", scene->sprite.west);
    printf("%s\n", scene->sprite.east);
    printf("  sky_color : ");
    printVec(scene->sky_color);
    printf("floor_color : ");
    printVec(scene->sky_color);
    printf("\n");
    
    printf("----MAP----\n");
    printf("height map = %d\n", scene->map.height_map);
    printf(" width map = %d\n", scene->map.width_map);
    print_tab(scene->map.matrix);

    print_player(scene->player);
}


int main(int argc, char const *argv[])
{
    (void) argc;
    (void) argv;

    /* SCOPE TESTS VICTOR */
    {
        t_scene     *scene;
        t_mlib      *mlib;
        int         size_file;
        char const  *filename;
        char        **copy;

        filename = "map2.cub";
        scene = malloc(sizeof(t_scene));
        if (scene == NULL)
            return (0);

        size_file = get_size_file(filename);
        copy = copy_file (filename, size_file);

        int end_part_1 = parser(scene, copy);        
        map_parser(scene, copy, end_part_1);

        mlib = malloc(sizeof(t_mlib));
        if (mlib == NULL)
            return (0);
        
        parser(scene, copy);

        scene->player.coord_ini = get_player_coord(scene->map.matrix);

        scene->player.dir = get_player_orientation(scene->map.matrix, scene->player.coord_ini);
        
        scene->map.size_wall = get_size_wall(scene->map.width_map, scene->map.height_map);
        
        scene->player.pos = get_player_position(scene->player.coord_ini, scene->map.size_wall);

        scene->player.speed = scene->map.size_wall * 0.1f;

        print_scene(scene);

        printf("------------------------------------\n");

        init_window(mlib, scene);
    }

    /*SCOPE FX*/
    {

    }


    return 0;
}

