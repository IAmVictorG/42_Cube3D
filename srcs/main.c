
#include "../header.h"

int main(int argc, char const *argv[])
{
    (void) argc;
    (void) argv;

    char **map;

    map = map_creator("map0.cub"); 
    display_map(map);



    return 0;
}

