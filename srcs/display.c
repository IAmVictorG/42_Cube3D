#include "../header.h"

void    printVec(t_vec vector)
{
    printf("x = %f, ", vector.x);
    printf("y = %f, ", vector.y);
    printf("z = %f", vector.z);
    printf("\n");
}

void    printCoord(t_coord coord)
{
    printf("Coord x = %d ", coord.x);
    printf("Coord y = %d", coord.y);
    printf("\n");
}

void    print_player(t_player player)
{
    printf("----PLAYER----\n");
    printCoord(player.coord_ini);
    printf("pos : ");
    printVec(player.pos);
    printf("dir : ");
    printVec(player.dir);
    printf("speed = %f\n", player.speed);
    printf("\n");
}

void    print_scene(t_scene *scene)
{
    printf("%s\n", scene->sprite.north);
    printf("%s\n", scene->sprite.south);
    printf("%s\n", scene->sprite.west);
    printf("%s\n", scene->sprite.east);
    printf("  sky_color : ");
    printVec(scene->sky_color);
    printf("floor_color : ");
    printVec(scene->sky_color);
    printf("\n");
    
    printf("----MAP----\n");
    printf("height map = %d\n", scene->map.height_map);
    printf(" width map = %d\n", scene->map.width_map);
    print_tab(scene->map.matrix);

    print_player(scene->player);
}
