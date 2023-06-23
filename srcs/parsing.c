#include "../parsing.h"

static parse_floor(t_scene *scene, char *line)
{
    char *r;

    r = go_to_next_and_get_arg(&line);
    printf("%s", r);
}

static parse_floor(t_scene *scene, char *line)
{
    char *r;

    r = go_to_next_and_get_arg(&line);
    printf("%s", r);
}

static void parse_wall(t_scene *scene, char *line)
{
    char *r;
    t_sprite *sprite;

    sprite = &scene->sprite;
    r = go_to_next_and_get_arg(&line);
    if (line[0] == 'N' && line[1] == 'O' && is_space(line[2])) // Sphere
        sprite->north = r;
    else if (line[0] == 'S' && line[1] == 'O' && is_space(line[2])) // Plane
        sprite->south = r;
    else if (line[0] == 'W' && line[1] == 'E' && is_space(line[2])) // Cylinder
        sprite->west = r;
    else if (line[0] == 'E' && line[1] == 'A' && is_space(line[2])) // Cylinder
        sprite->east = r;
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

void parse_line(t_scene *scene, char *line)
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
        parse_camera(scene, line);
    }
}