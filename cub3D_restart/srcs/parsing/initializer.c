#include "../../header.h"


t_mlib  *init_mlib()
{
    t_mlib  *mlib;

    mlib = (t_mlib *) malloc(sizeof(t_mlib));
    if (mlib == NULL)
        return (NULL);
    else
    {
        printf("%s : %p (%lu bytes)\n", "mlib", mlib, sizeof(t_mlib));
    }
    
    mlib->utils.mlx = mlx_init();


    return (mlib);
}

t_keys *init_key()
{
    t_keys *keys;

    keys = (t_keys *) malloc(sizeof(t_keys));
    if (keys == NULL)
    {
        return (NULL);
    }
    else
    {
        printf("%s : %p (%lu bytes)\n", "keys", keys, sizeof(t_keys));
    }


    keys->w = 0;
    keys->a = 0;
    keys->s = 0;
    keys->d = 0;
    keys->arrow_l = 0;
    keys->arrow_r = 0;

    return (keys);

}

t_sprite *init_sprite(char *path)
{

    //printf("path = %s\n", path);
    t_sprite    *wall;

    wall = (t_sprite *) malloc(sizeof(t_sprite));
    if (wall == NULL)
    {
        return (NULL);
    }
    else
    {
        printf("%s : %p (%lu bytes)\n", path, wall, sizeof(t_sprite));
    }
    wall->path = path;

    //print_sprite(wall);
    //printf("%s\n", wall->path);
    return (wall);
}

t_sprites   *init_sprites(char *wall_north, char *wall_south, char *wall_west, char *wall_east)
{


    t_sprites *sprites;

    sprites = (t_sprites *) malloc(sizeof(t_sprites));
    if (sprites == NULL)
        return (NULL);
    else
    {
        printf("%s : %p (%lu bytes)\n", "sprites", sprites, sizeof(t_sprites));
    }

    sprites->wall_east = init_sprite(wall_east);
    sprites->wall_west = init_sprite(wall_west);
    sprites->wall_south = init_sprite(wall_south);
    sprites->wall_north = init_sprite(wall_north);

    return sprites;
}