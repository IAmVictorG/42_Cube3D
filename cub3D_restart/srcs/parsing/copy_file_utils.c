#include "../header.h"


/* Renvoie le nombre de ligne du fichier a parser */
int get_size_file(char *filename)
{
    int     fd;
    char    *line = NULL;
    int     size_file;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (-1);
    size_file = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        size_file++;
        free(line);
    }
    close(fd);
    if (line)
        free(line);
    return (size_file);
}

/* Copie le fichier a parser dans un tableau 2D de char */
char **copy_file(char *filename, int size_file)
{
    int     fd;
    char    *line = NULL;
    char    **copy;
    int     i;

    copy = (char **) malloc(sizeof(char *) * (size_file + 1));
    if (copy == NULL)
        return (NULL);

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (NULL);
    i = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        copy[i] = line;
        i++;
    }
    copy[i] = NULL;
    close(fd);
    if (line)
        free(line);
    return (copy);
}