#include "../parsing.h"

static void parse_floor(t_scene *scene, char *line)
{
    char *r;

    (void) scene;
    r = go_to_next_and_get_arg(&line);
    set_vector(r, &scene->floor_color);
   // printf("%s", r);
}

static void parse_ceiling(t_scene *scene, char *line)
{
    char *r;

    (void) scene;
    r = go_to_next_and_get_arg(&line);
    set_vector(r, &scene->sky_color);

}

static void parse_wall(t_scene *scene, char *line)
{
    char *r;
    t_sprite *sprite;

    sprite = &scene->sprite;

    if (line[0] == 'N' && line[1] == 'O' && is_space(line[2]))
    {
        r = go_to_next_and_get_arg(&line);
        sprite->north = r;
    }
    else if (line[0] == 'S' && line[1] == 'O' && is_space(line[2]))
    {
        r = go_to_next_and_get_arg(&line);
        sprite->south = r;
    }
    else if (line[0] == 'W' && line[1] == 'E' && is_space(line[2]))
    {
        r = go_to_next_and_get_arg(&line);
        sprite->west = r;
    }
    else if (line[0] == 'E' && line[1] == 'A' && is_space(line[2]))
    {
        r = go_to_next_and_get_arg(&line);
        sprite->east = r;
    }
    r = go_to_next_and_get_arg(&line);
    if (ft_strlen(r) != 0 && string_is_only_space(r) == 0)
    {
        printf("R = %s\n", r);
        printf("[Error] Too many arguments on line\n");
    }
}

static int check_if_is_wall(char *line)
{
    if (line[0] == 'N' && line[1] == 'O' && is_space(line[2])) // Sphere
    {
        return (1);
    }
    else if (line[0] == 'S' && line[1] == 'O' && is_space(line[2])) // Plane
    {
        return (1);
    }
    else if (line[0] == 'W' && line[1] == 'E' && is_space(line[2])) // Cylinder
    {
        return (1);
    }
    else if (line[0] == 'E' && line[1] == 'A' && is_space(line[2])) // Cylinder
    {
        return (1);
    }
    return (0);
}

int parse_line(t_scene *scene, char *line)
{
    if (check_if_is_wall(line))
    {
        parse_wall(scene, line);
    }
    else if (line[0] == 'F' && is_space(line[1]))
    {
        parse_floor(scene, line);
    }
    else if (line[0] == 'C' && is_space(line[1]))
    {
        parse_ceiling(scene, line);
    }
    else
        return (0);
    return (1);
}
