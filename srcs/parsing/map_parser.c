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
	return (-1);
}


/* Renvoie le nombre de ligne que fait la map */
/* Renvoie le nombre de ligne depuis ind_map jusqu'a la premiere ligne vide rencontrée */
int height_map(char **copy_file, int ind_map)
{
	int	i;

	i = 0;
	while (copy_file[ind_map + i] != NULL
			&& string_is_only_space(copy_file[ind_map + i]) == 0)
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

	map = (char **) malloc(sizeof(char *) * (h_map + 1));
	if (map == NULL)
		return (NULL);

	i = 0;
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

	return (max_size -1 );
}

char *line_matrix_creator(char *line, int w_matrix)
{
	char 	*copy_line;
	int		i;
	//printf("avan_matrix_creator = [%s]\n", line);

	copy_line = (char *) malloc(sizeof(char) * (w_matrix + 1));
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

	i--;
	while (is_space(line[i]) == 1 && i >= 0)
	{
		i--;
	}

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

t_coord	get_player_coord(char **matrix)
{
	int		lin;
	int		col;
	t_coord	coord_ini;

	coord_ini.x = -1;
	coord_ini.y = -1;
	lin = 0;
	while (matrix[lin] != NULL)
	{
		col = 0;
		while (matrix[lin][col] != '\0')
		{
			if (matrix[lin][col] == 'N' || matrix[lin][col] == 'S' || matrix[lin][col] == 'E' || matrix[lin][col] == 'W')
			{
				coord_ini.y = lin;
				coord_ini.x = col;

				return(coord_ini);	
			}
			col++;
		}
		lin++;
	}
	return (coord_ini);
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

t_vec	get_player_orientation(char **matrix, t_coord coord_ini)
{
	char	orientation;
	t_vec	orientation_ini;

	orientation_ini.x = -1;
	orientation_ini.y = -1;
	orientation_ini.z = 0;

	orientation = matrix[coord_ini.y][coord_ini.x];
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

t_vec	get_player_position(t_coord coord_ini, int size_wall)
{
	t_vec position;
	float	size_wall_f = (float) size_wall;

	position.y = .5f;
	position.y = coord_ini.y * size_wall_f + size_wall_f * 0.5;
	position.x = coord_ini.x * size_wall_f + size_wall_f * 0.5;

	return (position);
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
    ft_free_tabs(map_uncompleted);

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


