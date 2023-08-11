#include "../../header.h"

int parse_first_wall(char *line, char **matrix, char **map_uncompleted)
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
			ft_free_tabs(matrix);
			ft_free_tabs(map_uncompleted);
			printf("Error : Inconsistent first or last wall.\n");


			return (0);
		}
		++i;
	}
	return is_valid;
}

int	find_map(char **copy_file, int end_part_1)
{
	int	i;

	i = end_part_1 + 1;
    while (copy_file[i] != NULL)
	{
		if (string_is_only_space(copy_file[i]) == 0)
		{
			return (i);
		}
		i++;
	}
	printf("Error : map not found or misplace.\n");
	return (-1);
}


/* Renvoie le nombre de ligne que fait la map */
/* Renvoie le nombre de ligne depuis ind_map jusqu'a la premiere ligne vide rencontrée */
int get_height_map(char **copy_file, int ind_map)
{
	int	i;

	i = 0;
	while (copy_file[ind_map + i] != NULL
			&& string_is_only_space(copy_file[ind_map + i]) == 0)
	{
		i++;
	}
    if (i <= 2 || i > (HEIGHT / SCALE_MINI_MAP))
	{
		printf("Error : heigth map incorrect.\n");
        return (0);
	}


	return (i);
}


int	get_width_map(char **map)
{
	int	size_current_line;
	int	max_size;
	int	i;
	int	j;

	i = 0;
	j = 0;
	max_size = 0;
	size_current_line = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] == ' ')
		{
			size_current_line++;
			j++;
		}
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '1' ||  caract_ONEWS(map[i][j]) == 1 || map[i][j] == ' ')
				size_current_line++;
			j++;
		}
		if (size_current_line > max_size)
			max_size = size_current_line;
		size_current_line = 0;
		i++;
	}
    if (max_size < 3 || max_size > (WIDTH / SCALE_MINI_MAP))
	{
		ft_free_tabs(map);
		printf("Error : width map incorrect.\n");		
        return (0);
	}
	return (max_size);
}


int check_EOF(char **copy_file, int ind_map, int h_map)
{
	int i;

	i = ind_map + h_map;
	while (copy_file[i] != NULL)
	{
		if (string_is_only_space(copy_file[i]) == 0)
		{
			printf("Error : EOF invalid.\n");
			return (0);
		}
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

	if (check_EOF(copy_file, ind_map, h_map) == 0)
		return (NULL);


	map = (char **) malloc(sizeof(char *) * (h_map + 1));
	if (map == NULL)
	{
		printf("Error : uncompleted map (allocation error).\n");
		return (NULL);
	}
	else
    {
        printf("%s : %p (%lu bytes)\n", "map", map, (sizeof(char *) * (h_map + 1)));
    }

	i = 0;
	while (i < h_map)
	{
		map[i] = ft_strdup(copy_file[ind_map + i]);
		i++;
	}
	map[i] = NULL;

    if (check_caract_map(map) == 0)
        return (NULL);	

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
		{
			ft_free_tabs(map_unc);
			printf("Error : inconsistent character in map.\n");
			return (0);	
		}
		i++;
	}
	return (1);
}



char *line_matrix_creator(char *line, int w_matrix)
{
	char 	*copy_line;
	int		i;

	copy_line = (char *) malloc(sizeof(char) * (w_matrix + 1));
	if (copy_line == NULL)
		return (NULL);
    else
    {
        printf("%s : %p (%lu bytes)\n", "copy_line", copy_line, (sizeof(char) * (w_matrix + 1)));
    }

	i = 0;
	while (line[i] != '\n' && line[i] != '\0' && i < w_matrix)
	{
		copy_line[i] = line [i];
		i++;
	}
	while (i < w_matrix)
	{
		copy_line[i] = ' ';
		i++;
	}
	copy_line[i] = '\0';
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
	{
		ft_free_tabs(matrix);
		ft_free_tabs(map_unc);
		printf("Error : issue with matrix allocation.\n");


		return (NULL);
	}
	else
    {
        printf("%s : %p (%lu bytes)\n", "matrix", matrix, (sizeof(char *) * (h_matrix + 1)));
    }



	i = 0;
	while (map_unc[i] != NULL)
	{
		matrix[i] = line_matrix_creator(map_unc[i], w_matrix);
		i++;
	}
	matrix[i] = NULL;

	//print_tab(matrix);
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

	i--;
	while (is_space(line[i]) == 1 && i >= 0)
	{
		i--;
	}

	if (line[i] == '1')
		return (1);

	//printf("line : %s\n", line);
	return (0);
}

int	check_last_first_one(char **matrix, char **map_uncompleted)
{
	int	i;

	i = 0;
	while(matrix[i] != NULL)
	{
		if (check_first_one(matrix[i]) == 0 || check_last_one(matrix[i]) == 0)
		{
			ft_free_tabs(matrix);
			ft_free_tabs(map_uncompleted);

			printf("Error : Inconsistent wall.\n");
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
		if (matrix[lin][col] == ' ')
		{
			return (0);
		}
		lin--;
	}
	return (0);
}

int	check_bottom(char **matrix, int lin, int col, t_coord size_matrix)
{
	while (lin < size_matrix.y)
	{
		if (matrix[lin][col] == '1')
		{
			return (1);
		}
		if (matrix[lin][col] == ' ')
		{
			return (0);
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


static int flood_fill(char **matrix, int lin, int col, t_coord size_matrix)
{
	if (caract_ONEWS(matrix[lin][col]) == 1)
	{
		if (check_right(matrix, lin, col, size_matrix) == 0)
		{
			return (0);
		}
		if (check_top(matrix, lin, col, size_matrix) == 0)
		{
			return (0);
		}
		if (check_bottom(matrix, lin, col, size_matrix) == 0)
		{
			return (0);
		}
		if (check_left(matrix, lin, col, size_matrix) == 0)
		{
			return (0);
		}
	}
	return (1);
}




int	wall_inspector(char **map_uncompleted, char **matrix, t_coord size_matrix)
{
	int lin;
	int col;

	lin = 1;
	while (lin < size_matrix.y - 1)
	{
		col = 0;
		while (col < size_matrix.x)
		{
			if (caract_ONEWS(matrix[lin][col]) == 1)
			{
				if (flood_fill(matrix, lin, col, size_matrix) == 0)
				{
					printf("Error : wall inspection issue.\n");
					ft_free_tabs(matrix);
					ft_free_tabs(map_uncompleted);
					return (0);
				}
			}
			col++;
		}
		lin++;
	}
	return (1);
}

int	check_player(char **matrix, char **map_uncompleted)
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

	ft_free_tabs(matrix);
	ft_free_tabs(map_uncompleted);
	printf("Error : Issue with player.\n");
	return (0);
}


char	get_letter_oreintation(char **matrix)
{
	int		i;
	int		j;

	i = 0;
	while (matrix[i] != NULL)
	{
		j = 0;
		while (matrix[i][j] != '\0')
		{
			if (matrix[i][j] == 'N' || matrix[i][j] == 'S' || matrix[i][j] == 'E' || matrix[i][j] == 'W')
				return (matrix[i][j]);
			j++;
		}
		i++;
	}
	return (0);
}

t_coord	get_player_coord(char **matrix)
{
	int		lin;
	int		col;
	t_coord	coord_ini;

	coord_ini.x = -1;
	coord_ini.y = -1;
	coord_ini.z = 0;
	lin = 0;
	while (matrix[lin] != NULL)
	{
		col = 0;
		while (matrix[lin][col] != '\0')
		{
			if (matrix[lin][col] == 'N' || matrix[lin][col] == 'S' || matrix[lin][col] == 'E' || matrix[lin][col] == 'W')
			{
				coord_ini.y = lin * SIZE_WALL + SIZE_WALL / 2;
				coord_ini.x = col * SIZE_WALL + SIZE_WALL / 2;

				return(coord_ini);	
			}
			col++;
		}
		lin++;
	}
	return (coord_ini);
}

t_vec	get_player_orient(char **matrix)
{
	char	orientation;
	t_vec	orientation_ini;

	orientation_ini.x = -1;
	orientation_ini.y = -1;
	orientation_ini.z = 0;

	orientation = get_letter_oreintation(matrix);
	
	if (orientation == 'N')
	{
		orientation_ini.x = 0;
		orientation_ini.y = -1;
	}
	else if (orientation == 'S')
	{
		orientation_ini.x = 0;
		orientation_ini.y = 1;
	}
	else if (orientation == 'W')
	{
		orientation_ini.x = -1;
		orientation_ini.y = 0;
	}
	else if (orientation == 'E')
	{
		orientation_ini.x = 1;
		orientation_ini.y = 0;
	}
	return (orientation_ini);
}

int get_size_wall (int map_w, int map_h)
{
    int size_wall;

	int rap_h = HEIGHT / map_h;
	int rap_w = WIDTH  / map_w;

	if (rap_h < rap_w)
	{
		size_wall = (HEIGHT -1) / map_h;
	}
    else
    {
        size_wall = (WIDTH-1) / map_w;
    }

    //scene->map.size_wall = size_wall;
	printf("size_wall = %d\n", size_wall);
    return (size_wall);
}

t_coord	get_player_position(t_coord coord_ini, int size_wall)
{
	t_coord position;
	float	size_wall_f = (float) size_wall;

	position.y = (int)(coord_ini.y * size_wall + size_wall_f * 0.5);
	position.x = (int)(coord_ini.x * size_wall + size_wall_f * 0.5);
	//position.z = .5f;

	//printCoord(position);

	return (position);
}

int init_map(t_map *map, char **copy, int end_parse_1)
{
    int     ind_map;
    int     h_map;
    char    **map_uncompleted;
    int     w_map;
    char    **matrix;

    ind_map = find_map(copy, end_parse_1);
    h_map = get_height_map(copy, ind_map);


    map_uncompleted = map_creator(copy, h_map, ind_map);
    if (map_uncompleted == NULL)
        return (0);
    else
    {
        printf("%s : %p (%lu bytes)\n", "map_uncompleted", map_uncompleted, sizeof(map_uncompleted));
    }

    w_map = get_width_map(map_uncompleted);

    matrix = matrix_creator(map_uncompleted, h_map, w_map);
    if (matrix == NULL)
        return (0);

    
    map->width_map = w_map * SIZE_WALL;
	map->height_map = h_map * SIZE_WALL;
	map->height_matrix = h_map;
	map->width_matrix = w_map;
    map->matrix = matrix;

    ft_free_tabs(map_uncompleted);
    return (1);
}