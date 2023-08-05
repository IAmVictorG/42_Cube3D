#ifndef PARSING_H
# define PARSING_H

#include "../../header.h"

/* parsing/args_manager.c */
char	*get_filename(const char *file_path);
char    *get_extension(char *filename);
int		filename_is_valid(const char *file_path);
int		file_exists (char *filename);

/* parsing/copy_file_utils.c */
int		get_size_file(char *filename);
char	**copy_file(char *filename, int size_file);


/* parsing/parsing.c */
int		is_space(char c);
int		string_is_only_space(char *str);
char	*go_to_next_and_get_arg(char *line);
char	*get_wall (char **copy_of_file, char first, char second);
int		is_numeric(char *str);
t_coord	set_vector(char *str);
char	*get_floor_ceil (char **copy_of_file, char caract);

# endif