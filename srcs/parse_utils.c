#include "../parsing.h"

int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == '\f');
}

void	set_vector(char *str, t_vec *vec)
{
	int i;
	int	start;
	char *r;

	start = 0;
	i = 0;
	while (str[i] && str[i] != ',')
		i++;
	r = ft_substr(str, start, i);	
	vec->x = atof(r);
	free(r);
	start = ++i;
	while (str[i] && str[i] != ',')
		i++;
	r = ft_substr(str, start, i - start);	
	vec->y  = atof(r);
	free(r);
	start = ++i;
	while (str[i] && str[i] != ',')
		i++;
	r = ft_substr(str, start, i - start);	
	vec->z  = atof(r);
	free(r);
}

char *go_to_next_and_get_arg(char **line)
{
	int i;

	i = 0;
    while (**line && (!is_space(**line)))
	{
		(*line)++;
	}
	while (**line && (is_space(**line)))
	{
		(*line)++;
	}
	while (**line && is_space(**line))
	{
		(*line)++;;
	}
	while ((*line)[i] && !is_space((*line)[i]))
	{
		i++;
	}
	return (ft_substr(*line, 0, i));
}
