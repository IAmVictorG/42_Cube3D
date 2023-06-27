#include "../header.h"

/* Renvoie le nombre de ligne que fait la map */
/* Renvoie le nombre de ligne depuis ind_map jusqu'a la premiere ligne vide rencontrée */
int height_map(char **copy_file, int ind_map)
{
	int		i;

	i = 0;
	while (copy_file[ind_map + i] != NULL && copy_file[ind_map + i][0] != '\n')
	{
		i++;
	}
	return (i);
}

/* Parcours les lignes du fichier depuis ind_map jusqu a ind_map + h_map */
/* Renvoie un tableau 2D de char contenant toutes les lignes lues entre ind_map et ind_map + h_map*/
char **map_creator(char **copy_file, int h_map, int ind_map)
{
	char	**map;
	int		i;
	char	*line;

	map = (char **) malloc(sizeof(char *) * (h_map + 1));
	if (map == NULL)
		return (NULL);

	i = 0;
	line = NULL;

	//printf("i = %d\n", i);

	while (i < h_map)
	{
		map[i] = ft_strdup(copy_file[ind_map + i]);
		//printf("i = %d : %s\n", i, map[i]);
		i++;
	}
	map[i] = NULL;
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

int	find_map(char **copy_file)
{
	int		i;

	i = 0;
    while (copy_file[i] != NULL)
    {
		if (parse_first_wall(copy_file[i]) == 1)
			return (i);
		i++;
    }
    return (-1);
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

char *line_matrix_creator(char *line, int w_matrix)
{
	char 	*copy_line;
	int		i;

	copy_line = (char *) malloc(sizeof(char) * (w_matrix + 1));
	i = 0;

	while (line[i] != '\0')
	{	
		copy_line[i] = line[i];
		i++;
	}

	while (i < w_matrix)
	{
		copy_line[i] = '.';
		i++;
	}
	line[i] = '\0';
	printf("line_matrix_creator = %s\n", copy_line);
	return (line);

}

int	check_caract_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '1'
			&& line[i] != '0'
			&& line[i] != 'N'
			&& line[i] != 'W'
			&& line[i] != 'E'
			&& line[i] != 'S'
			&& line[i] != ' '
			&& line[i] != '\n')
		{
			//printf("line %s : 0\n", line);
			return (0);
		}
		i++;
	}
	//printf("line %s : 1\n", line);
	return (1);
}

int	check_caract_map(char **map_unc)
{
	int	i;

	i = 0;
	while (map_unc[i] != NULL)
	{
		//printf("lien = %s :", map_unc[i]);
		if (check_caract_line(map_unc[i]) == 0)
			return (0);	
		i++;
	}
	return (1);
}


char	**matrix_creator(char **map_unc, int h_matrix, int w_matrix)
{
	int		i;
	char	**matrix;
	(void) w_matrix;
	matrix = (char **) malloc(sizeof(char *) * (h_matrix + 1));
	if (matrix == NULL)
		return (NULL);

	i = 0;
	while (map_unc[i] != NULL)
	{

		i++;
	}
	


	return (NULL);
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