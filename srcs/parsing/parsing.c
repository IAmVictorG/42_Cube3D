#include "../parsing.h"

static void parse_floor(t_scene *scene, char *line)
{
    char *r;

    r = go_to_next_and_get_arg(&line);
    set_vector(r, &scene->floor_color);
}

static void parse_ceiling(t_scene *scene, char *line)
{
    char *r;

    (void) scene;
    r = go_to_next_and_get_arg(&line);
    set_vector(r, &scene->sky_color);
}

static void parse_wall(t_sprites *sprites, char *line)
{
    char *r;

    if (line[0] == 'N' && line[1] == 'O' && is_space(line[2]))
    {
        r = go_to_next_and_get_arg(&line);
        sprites->wall_north.path = r;
    }
    else if (line[0] == 'S' && line[1] == 'O' && is_space(line[2]))
    {
        r = go_to_next_and_get_arg(&line);
        sprites->wall_south.path = r;
    }
    else if (line[0] == 'W' && line[1] == 'E' && is_space(line[2]))
    {
        r = go_to_next_and_get_arg(&line);
        sprites->wall_west.path = r;
    }
    else if (line[0] == 'E' && line[1] == 'A' && is_space(line[2]))
    {
        r = go_to_next_and_get_arg(&line);
        sprites->wall_east.path = r;
    }
    r = go_to_next_and_get_arg(&line);
    if (ft_strlen(r) != 0 && string_is_only_space(r) == 0)
    {
        printf("R = %s\n", r);
        printf("Error\n Too many arguments on line\n");
    }
}

static int check_if_is_wall(char *line)
{
    if (line[0] == 'N' && line[1] == 'O' && is_space(line[2]))
    {
        return (1);
    }
    else if (line[0] == 'S' && line[1] == 'O' && is_space(line[2]))
    {
        return (1);
    }
    else if (line[0] == 'W' && line[1] == 'E' && is_space(line[2]))
    {
        return (1);
    }
    else if (line[0] == 'E' && line[1] == 'A' && is_space(line[2]))
    {
        return (1);
    }
    return (0);
}

static int check_for_1_or_0(char *line)
{
    int i;

    i = 0;
    while (is_space(line[i]))
    {
        i++;
    }
    if (line[i] == '1' || line[i] == '0')
    {
        return (1);
    }
    return (0);
}

static int parse_line(t_sprites *sprites, t_scene *scene, char *line)
{
    if (check_if_is_wall(line))
    {
        parse_wall(sprites, line);
    }
    else if (line[0] == 'F' && is_space(line[1]))
    {
        parse_floor(scene, line);
    }
    else if (line[0] == 'C' && is_space(line[1]))
    {
        parse_ceiling(scene, line);
    }
    else if (check_for_1_or_0(line))
    {
        return (-1);
    }
    else
        return (0);
    return (1);
}

int parser(t_sprites *sprites, t_scene *scene, char **copy)
{
    int i;
    int found;
    int end;

    i = 0;
    found = 0;

    while (copy[i])
    {
        if (parse_line(sprites, scene, copy[i]) == 1)
        {
            found ++;
            end = i;
        }
        else if (parse_line(sprites, scene, copy[i]) == -1 && found != 6)
        {
            printf("Error\n You didn't initialise all the stuff needed before the map\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    return (end);
}

