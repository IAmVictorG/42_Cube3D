#ifndef PARSING
# define PARSING

# include "header.h"

char *go_to_next_and_get_arg(char **line);
int is_space(char c);
void	set_vector(char *str, t_vec *vec);
int string_is_only_space(char *str);

#endif