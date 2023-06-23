#include "../parsing.h"

static char *go_to_next_and_get_arg(char **line)
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
