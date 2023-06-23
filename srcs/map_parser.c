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

//int valid_first_line();

void	display_map(char **map)
{
	int	i;

	printf("---MAP--\n");
	printf("\n");
	i = 0;
	while (map[i] != NULL)
	{
		printf("%s", map[i]);
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