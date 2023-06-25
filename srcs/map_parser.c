#include "../header.h"

/* Renvoie le nombre de ligne que fait la map */
/* Renvoie le nombre de ligne depuis ind_map jusqu'a EOF */
int height_map(const char *filename, int ind_map)
{
	char	*line;
	int		size;
    int		fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return -1;
	line = NULL;
	while (ind_map > 0)
	{
		line = get_next_line(fd);
		ind_map--;
	}
	size = 0;
	while (42)
	{
		line = get_next_line(fd);
		size++;
		if (line == NULL)
			return (size);
	}
	close(fd);
    if (line)
        free(line);
	return(-1);
}

/* Parcours les lignes du fichier depuis ind_map jusqu a ind_map + h_map */
/* Renvoie un tableau 2D de char contenant toutes les lignes lues */
char **map_creator(const char *file_name, int h_map, int ind_map)
{
	int 	fd;
	char	**map;
	int		i;
	char	*line;

	map = malloc(sizeof(char *) * (h_map + 1));
	if (map == NULL)
		return (NULL);

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (NULL);

	i = 0;
	while (i < ind_map - 1)
	{
		line = get_next_line(fd);
		//printf("i = %d : %s\n", i, line);

		free(line);
		i++;
	}
	//printf("i = %d\n", i);
	i = 0;
	while (i < h_map)
	{
		map[i] = get_next_line(fd);
		//printf("i = %d : %s\n", i, map[i]);
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

int	check_first_one(char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]) == 1 && line[i] != '\0')
		i++;
	if (line[i] == '1')
		return (1);
	return (0);
}

int check_last_one(char *line)
{
	int	i;

	i = ft_strlen(line);
	while (is_space(line[i]) == 1 && i > 0)
		i--;
	i-=2;
	//printf("c = [%c]\n", line[i]);
	if (line[i] == '1')
		return (1);
	return (0);
}

int	check_last_first_one(char **map)
{
	int	i;

	i = 0;
	while(map[i] != NULL)
	{
		//printf("map[%d] = (%s)\n", i, map[i]);
		if (check_first_one(map[i]) == 0 || check_last_one(map[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	find_largest_line(char **map)
{
	int	size_current_line;
	int	max_size;
	int	i;

	i = 0;
	max_size = 0;
	while (map[i] != NULL)
	{
		size_current_line = ft_strlen(map[i]);
		if (size_current_line > max_size)
			max_size = size_current_line;
		i++;
	}

	return (max_size);
}

int	find_map(const char *filename)
{
    int		fd;
    char	*line = NULL;
	int		i;

	i = 1;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return -1;
    while ((line = get_next_line(fd)) != NULL)
    {
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
		if (is_space(line[i]) == 1 || line[i] == '1')
		{
			is_valid = 1;
		}
		else
		{
			return (0);
		}
		++i;
	}
	return is_valid;
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