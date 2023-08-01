#include "../../header.h"

char *get_filename(const char *file_path)
{
    char    *filename;
    int     i;
    int     filename_len;

    i = ft_strlen(file_path);
    filename_len = 0;
    while (i > 0 && file_path[i] != '/')
    {
        i--;
        filename_len ++;
    }
    if (file_path[i] == '/')
    {
        i++;
    }
    filename = ft_substr(file_path, i, filename_len);
    return (filename);
}

char    *get_extension(char *filename)
{
    int     filename_len;
    int     extension_len;
    int     i;
    
    filename_len = ft_strlen(filename);
    i = filename_len;
    extension_len = 0;
    while (filename[i] != '.' && i > 0)
    {
        i--;
        extension_len ++;
    }
    if (i == 0 || i == filename_len - 1 )
    {
        return (NULL);
    }
    return (ft_substr(filename, filename_len - extension_len, extension_len));
}

int filename_is_valid(const char *file_path)
{
    char    *extension;
    char    *filename;

    filename = get_filename(file_path);
    extension = get_extension(filename);
    if (filename == NULL || extension == NULL)
        return (1);
    if (ft_strncmp(extension, ".cub", 4) != 0)
    {
        free(filename);
        free(extension);
        return (0);
    }

    free(filename);
    free(extension);
    return (1);
}