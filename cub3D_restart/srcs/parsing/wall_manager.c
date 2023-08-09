#include "../../header.h"

char *get_wall (char **copy_of_file, char first, char second)
{
    int i;
    int ind_c;

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
            if (copy_of_file[i][ind_c] == first && copy_of_file[i][ind_c + 1] == second && is_space(copy_of_file[i][ind_c + 2]))
            {
                return go_to_next_and_get_arg(&copy_of_file[i][ind_c]);
            }
        	i++;
        }
    }
    return (NULL);
}

int walls_manager_exists (char **walls)
{
    int i;

    i = 0;
    while (walls[i] != NULL)
    {
        if (file_exists(walls[i]) == 0)
        {
            //printf("Error : Impossible to open %s\n", walls[i]);
            return (0);
        }
        i++;
    }
    return (1);
}

char **walls_manager (char **copy_of_file)
{
    char    **walls;

    walls = (char **) ft_calloc(5, sizeof(char *)); // malloc(5 * sizeof(char *));
    if (walls == NULL)
    {
        return (NULL);
    }
    walls[0] = NULL;
    walls[1] = NULL;
    walls[2] = NULL;
    walls[3] = NULL;
    walls[4] = NULL;
    
    
    walls[0] = get_wall(copy_of_file, 'N', 'O');
    if (walls[0] == NULL)
    {
        printf("Error : No Wall North.\n");
        free(walls);
        return (NULL);
    }
    walls[1] = get_wall(copy_of_file, 'S', 'O');
    if (walls[1] == NULL)
    {
        printf("Error : No Wall South.\n");
        ft_free_tabs(walls);
        return (NULL);
    }    
    walls[2] = get_wall(copy_of_file, 'E', 'A');
    if (walls[2] == NULL)
    {
        printf("Error : No Wall East.\n");
        ft_free_tabs(walls);
        return (NULL);
    }    
    walls[3] = get_wall(copy_of_file, 'W', 'E');
    if (walls[3] == NULL)
    {
        printf("Error : No Wall West.\n");
        ft_free_tabs(walls);
        return (NULL);
    }
    //print_tab(walls);
    return (walls);
}