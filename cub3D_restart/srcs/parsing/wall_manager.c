#include "../../header.h"

char	*get_wall(char **copy_of_file, char first, char second)
{
	int	i;
	int	ind_c;

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
				ind_c ++;
			if (copy_of_file[i][ind_c] == first
			&& copy_of_file[i][ind_c + 1] == second
			&& is_space(copy_of_file[i][ind_c + 2]))
			{
				return (go_to_next_and_get_arg(&copy_of_file[i][ind_c]));
			}
			i++;
		}
	}
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

static int	check_points(char *filename)
{
	if (ft_strcmp(filename, ".") == 0)
		return (0);
	if (ft_strcmp(filename, "..") == 0)
		return (0);
	return (1);
}

int	walls_manager_exists(char **walls)
{
	int	i;

	i = 0;
	while (walls[i] != NULL)
	{
		if (check_points (walls[i]) == 0)
			return (0);
		if (file_exists(walls[i]) == 0)
		{
			printf("Error : Impossible to open (%s)\n", walls[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	norm_init_walls(char **walls)
{
	walls[0] = NULL;
	walls[1] = NULL;
	walls[2] = NULL;
	walls[3] = NULL;
	walls[4] = NULL;
}

static char	*norm_get_no(char **walls, char **copy_of_file)
{
	char	*wall_no;

	wall_no = get_wall(copy_of_file, 'N', 'O');
	if (wall_no == NULL)
	{
		printf("Error : No Wall North.\n");
		ft_free_tabs(copy_of_file);
		free(walls);
		return (NULL);
	}
	return (wall_no);
}

static char	*norm_get_so(char **walls, char **copy_of_file)
{
	char	*wall_so;

	wall_so = get_wall(copy_of_file, 'S', 'O');
	if (wall_so == NULL)
	{
		printf("Error : No Wall South.\n");
		ft_free_tabs(copy_of_file);
		ft_free_tabs(walls);
		return (NULL);
	}
	return (wall_so);
}

static char	*norm_get_ea(char **walls, char **copy_of_file)
{
	char	*wall_ea;

	wall_ea = get_wall(copy_of_file, 'E', 'A');
	if (wall_ea == NULL)
	{
		printf("Error : No Wall East.\n");
		ft_free_tabs(copy_of_file);
		ft_free_tabs(walls);
		return (NULL);
	}
	return (wall_ea);
}

static char	*norm_get_we(char **walls, char **copy_of_file)
{
	char	*wall_we;

	wall_we = get_wall(copy_of_file, 'W', 'E');
	if (wall_we == NULL)
	{
		printf("Error : No Wall West.\n");
		ft_free_tabs(copy_of_file);
		ft_free_tabs(walls);
		return (NULL);
	}
	return (wall_we);
}

static void	norm_free_wm(char **copy_of_file, char **walls)
{
	ft_free_tabs(copy_of_file);
	ft_free_tabs(walls);
}

char	**walls_manager(char **copy_of_file)
{
	char	**walls;

	walls = (char **) ft_calloc(5, sizeof(char *));
	if (walls == NULL)
		return (NULL);
	norm_init_walls(walls);
	walls[0] = norm_get_no(walls, copy_of_file);
	if (walls[0] == NULL)
		return (NULL);
	walls[1] = norm_get_so(walls, copy_of_file);
	if (walls[0] == NULL)
		return (NULL);
	walls[2] = norm_get_ea(walls, copy_of_file);
	if (walls[0] == NULL)
		return (NULL);
	walls[3] = norm_get_we(walls, copy_of_file);
	if (walls[0] == NULL)
		return (NULL);
	if (walls_manager_exists(walls) == 0)
	{
		norm_free_wm(copy_of_file, walls);
		printf("Error : Issue with wall file.\n");
		return (NULL);
	}
	return (walls);
}
