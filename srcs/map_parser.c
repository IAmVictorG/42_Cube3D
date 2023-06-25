#include "../header.h"

int height_map(int fd)
{
	char	*line;
	int		size;

	size = 0;
	while (42)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (size);
		size++;
	}
	return(-1);
}

char **map_creator(char *file_name)
{
	int 	fd;
	char	**map;
	int		size;
	int		i;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	size = height_map(fd);
	close(fd);
	map = malloc(sizeof(char *) * (size + 1));
	if (map == NULL)
		return (NULL);
	fd = open(file_name, O_RDONLY);
	i = 0;
	while (i < size)
	{
		map[i] = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

void set_map(char **map, t_scene *scene)
{
	scene->map.map = map;
}

int	find_map(const char *filename)
{
    int		fd;
    char	*line = NULL;
	int		i;

	i = 0;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return -1;
    while ((line = get_next_line(fd)) != NULL)
    {
		printf("[%s] : %d\n", line, parse_first_wall(line));
		if (parse_first_wall(line) == 1)
		{
			close(fd);
			if (line)
				free(line);			
			return (i);
		}
		i++;
    }
    close(fd);
    if (line)
        free(line);
    return (0);

}

int parse_first_wall(char *line)
{
	int i;
	int	is_valid;

	i = 0;
	is_valid = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (!(is_space(line[i]) == 1 || line[i] == '1'))
		{
			return (0);
		}
		++i;
	}
	return (1);
}

void	display_map(t_scene *scene)
{
	int	i;

	printf("---MAP--\n");
	printf("Hauteur = %d\n", scene->map.height_map);
	printf("\n");

	i = 0;
	while ((scene->map.map)[i] != NULL)
	{
		printf("%s", (scene->map.map)[i]);
		i++;
	}
	printf("\n");
	printf("\n");
}


// int parse_map(char **map)
// {
// 	int	i;

// 	i = 0;
// 	while (map[i] != NULL)
// 	{


// 	}

// 	return 0;
// }