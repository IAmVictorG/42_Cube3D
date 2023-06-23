
#include "../header.h"

int main(int argc, char const *argv[])
{
    (void) argc;
    (void) argv;

    //char *map[6];
    
    //parse_map(map);

    int fd = open("map0.cub", O_RDONLY);

    char *line = get_next_line(fd);


    


    printf("%s\n", line);


    return 0;
}

