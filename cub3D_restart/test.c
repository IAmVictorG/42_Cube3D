#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include 

int file_exists(const char *filename) 
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1) 
    {
        return 0;
    }
    close(fd);
    return 1;
}

static int	check_points (char *filename)
{
	if (ft_strcmp(filename, "."))
		return (0);
	
	if (ft_strcmp(filename, ".."))
		return (0);
	return (1);
}

int main()
{
    char *filename = "...";

    printf("check points = %d\n", check_points(filename));


    if (file_exists(filename)) {
        printf("The file %s exists.\n", filename);
    } else {
        printf("The file %s does not exist.\n", filename);
    }

    return 0;
}