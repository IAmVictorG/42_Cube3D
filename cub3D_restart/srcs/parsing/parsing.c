#include "../../header.h"

int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == '\f');
}

int string_is_only_space(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (!is_space(str[i]) && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

char *go_to_next_and_get_arg(char *line)
{
	int i;

	i = 0;
    while (*line && (!is_space(*line)))
	{
		line++;
	}
	while (*line && (is_space(*line)))
	{
		line++;
	}
	while (line[i] && !is_space(line[i]) && line[i] != '\n')
	{
		i++;
	}
	return (ft_substr(line, 0, i));
}

int is_numeric(char *str) 
{
    if (!str || *str == '\0') 
    {
        return 0;
    }

    while (*str) 
    {
        if (*str < '0' || *str > '9') 
		{
            return 0;
        }
        str++;
    }
    return 1;
}

t_coord	set_vector(char *str)
{
	int i;
	int	start;
	char *r;
	t_coord	color;

	color.x = -1;
	color.y = -1;
	color.z = -1;

	start = 0;
	i = 0;
	while (str[i] && str[i] != ',')
		i++;
	r = ft_substr(str, start, i);
	if (is_numeric(r) == 1)
	{
		color.x = atoi(r);
	}
	free(r);

	start = ++i;
	while (str[i] && str[i] != ',')
		i++;
	r = ft_substr(str, start, i - start);	
	if (is_numeric(r) == 1)
	{
		color.y = atoi(r);
	}
	free(r);

	start = ++i;
	while (str[i] && str[i] != ',')
		i++;
	r = ft_substr(str, start, i - start);	
	if (is_numeric(r) == 1)
	{
		color.z = atoi(r);
	}
	free(r);

	return (color);
}

int check_coord_color (t_coord color)
{
    if (color.x < 0 || color.x > 255)
    {
        return (0);
    }
    if (color.y < 0 || color.y > 255)
    {
        return (0);
    }
    if (color.z < 0 || color.z > 255)
    {
        return (0);
    }
    return (1);
}

char	*get_floor_ceil (char **copy_of_file, char caract)
{
    int i;
    int ind_c;
	char	*str;

    i = 0;
    while (copy_of_file[i])
    {
        ind_c = 0;
        if (string_is_only_space(copy_of_file[i]) == 1)
        {
            i++;
        }
        else
        {
            while (is_space(copy_of_file[i][ind_c]) == 1)
            {
                ind_c ++;
            }
            if (copy_of_file[i][ind_c] == caract && is_space(copy_of_file[i][ind_c + 1]))
            {
                str = go_to_next_and_get_arg(&copy_of_file[i][ind_c]);				
				return str;
            }
        	i++;
        }
    }
    printf("Error : Floor color not found.\n");
    return (NULL);
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

static int parse_line(char *line)
{
    if (check_if_is_wall(line))
    {
        return (1);
    }
    else if (line[0] == 'F' && is_space(line[1]))
    {
        return (1);
    }
    else if (line[0] == 'C' && is_space(line[1]))
    {
        return (1);
    }
    else if (check_for_1_or_0(line))
    {
        return (-1);
    }
    else
        return (0);
    return (1);
}

int parser(char **copy)
{
    int i;
    int found;
    int end;

    i = 0;
    found = 0;

    while (copy[i])
    {
		//printf("line = %d : %s\n",i, copy[i]);
        if (parse_line(copy[i]) == 1)
        {
            found ++;
            end = i;
        }
        else if (parse_line(copy[i]) == -1 && found != 6)
        {
            printf("Error : You didn't initialise all the stuff as it should be before the map.\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    return (end);
}
