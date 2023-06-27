#include "../header.h"

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


/* Renvoie le nombre de ligne que fait la map */
/* Renvoie le nombre de ligne depuis ind_map jusqu'a la premiere ligne vide rencontrée */
int height_map(char **copy_file, int ind_map)
{
	int	i;

	i = 0;
	while (copy_file[ind_map + i] != NULL && copy_file[ind_map + i][0] != '\n')
	{
		i++;
	}
	return (i);
}

int check_EOF(char **copy_file, int ind_map, int h_map)
{
	int i;

	i = ind_map + h_map;
	while (copy_file[i] != NULL)
	{
		if (string_is_only_space(copy_file[i]) == 0)
			return (0);
		i++;
	}
	return (1);
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

char *line_matrix_creator(char *line, int w_matrix)
{
	char 	*copy_line;
	int		i;
	//printf("avan_matrix_creator = [%s]\n", line);

	copy_line = (char *) malloc(sizeof(char) * (w_matrix));
	if (copy_line == NULL)
		return (NULL);

	i = 0;
	while (line[i] != '\n')
	{	
		copy_line[i] = line[i];
		i++;
	}

	while (i < (w_matrix - 1))
	{
		copy_line[i] = ' ';
		i++;
	}
	copy_line[i] = '\0';
	//printf("line_matrix_creator = [%s]\n\n", copy_line);
	return (copy_line);

}

char	**matrix_creator(char **map_unc, int h_matrix, int w_matrix)
{
	int		i;
	char	**matrix;

	// printf("AVANT\n");
	// print_tab(map_unc);

	matrix = (char **) malloc(sizeof(char *) * (h_matrix + 1));
	if (matrix == NULL)
		return (NULL);

	i = 0;
	while (map_unc[i] != NULL)
	{
		matrix[i] = line_matrix_creator(map_unc[i], w_matrix);
		i++;
	}
	matrix[i] = NULL;

	return (matrix);
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
	//printf("i = %d\n", i);
	//printf("c = [%c]\n", line[i-1]);
	i--;
	while (is_space(line[i]) == 1 && i >= 0)
	{
		i--;
	}
	//i--;
	//printf("c = [%c]\n", line[i]);

	if (line[i] == '1')
		return (1);
	return (0);
}

int	check_last_first_one(char **matrix)
{
	int	i;

	i = 0;
	while(matrix[i] != NULL)
	{
		if (check_first_one(matrix[i]) == 0 || check_last_one(matrix[i]) == 0)
		{
			printf("first : %d\n", check_first_one(matrix[i]));
			printf("last : %d\n", check_last_one(matrix[i]));
			printf("error : [%s]\n", matrix[i]);
			return (0);
		}
		i++;
	}
	return (1);
}


int check_right(char **matrix, int lin, int col, t_coord size_matrix)
{
	int i;
	(void) size_matrix;

	i = 0;
	while (matrix[lin][col + i] != '\0')
	{
		if (matrix[lin][col + i] == '1')
		{
			return (1);
		}
		if (matrix[lin][col + i] == ' ')
		{
			return (0);
		}
		i++;
	}
	return (0);
}

int	check_top(char **matrix, int lin, int col, t_coord size_matrix)
{
	(void) size_matrix;

	while (lin >= 0)
	{
		if (matrix[lin][col] == '1')
		{
			return (1);
		}
		lin--;
	}
	return (0);
}

int	check_bottom(char **matrix, int lin, int col, t_coord size_matrix)
{
	//(void) size_matrix;

	while (lin < size_matrix.y)
	{
		if (matrix[lin][col] == '1')
		{
			return (1);
		}
		lin++;
	}
	return (0);
}

int	check_left(char **matrix, int lin, int col, t_coord size_matrix)
{
	(void) size_matrix;

	while (col >= 0)
	{
		if (matrix[lin][col] == '1')
		{
			return (1);
		}
		if (matrix[lin][col] == ' ')
		{
			return (0);
		}
		col--;
	}
	return (0);
}

int	caract_ONEWS (char c)
{
	return (c == '0'
			|| c == 'N' 
			|| c == 'S'
			|| c == 'E'
			|| c == 'W');

}

int	wall_inspector(char **matrix, int h_matrix, int w_matrix)
{
	int lin;
	int col;

	t_coord size_matrix;
	size_matrix.x = w_matrix;
	size_matrix.y = h_matrix;

	lin = 1;
	while (lin < h_matrix - 1)
	{
		col = 0;
		while (col < w_matrix)
		{
			if (caract_ONEWS(matrix[lin][col]) == 1)
			{
				if (check_right(matrix, lin, col, size_matrix) == 0)
				{
					printf("Le point (x = %d, y = %d) : Droite\n", lin, col);
					return (0);
				}
				if (check_top(matrix, lin, col, size_matrix) == 0)
				{
					printf("Le point (x = %d, y = %d) : Haut  \n", lin, col);
					return (0);
				}
				if (check_bottom(matrix, lin, col, size_matrix) == 0)
				{
					printf("Le point (x = %d, y = %d) : Bas   \n", lin, col);
					return (0);
				}
				if (check_left(matrix, lin, col, size_matrix) == 0)
				{
					printf("Le point (x = %d, y = %d) : Gauche\n", lin, col);
					return (0);
				}
			}
			col++;
		}
		lin++;
	}
	
	return (1);

}

int	check_player(char **matrix)
{
	int	lin;
	int	col;
	int	count;

	count = 0;
	lin = 0;
	while (matrix[lin] != NULL)
	{
		col = 0;
		while (matrix[lin][col] != '\0')
		{
			if (matrix[lin][col] == 'N' || matrix[lin][col] == 'S' || matrix[lin][col] == 'E' || matrix[lin][col] == 'W')
			{
				count++;
			}
			col++;
		}
		lin++;
	}
	if (count == 1)
		return (1);
	return (0);
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


