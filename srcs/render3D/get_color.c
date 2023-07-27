#include "../../header.h"

int get_color_wall_north(t_general *general, float x, int h_wall, int max_wall_h)
{
    t_sprites       *sprites;
    char            *pixel;
    unsigned int    color;
    int             size_wall;

    int             x_pix;
    int             y_pix;

    size_wall = 64;
    sprites = general->sprites;

    int xx = x;
    x_pix = roundf(((float)(xx % size_wall) + (float)(x - xx))* (float)general->sprites->wall_north->sprite_w/(float)size_wall); /*arrondi ???*/
    y_pix = roundf(h_wall * general->sprites->wall_north->sprite_h/ max_wall_h);

    pixel = sprites->wall_north->data_spr.addr + (y_pix * sprites->wall_north->data_spr.line_length + x_pix * (sprites->wall_north->data_spr.bits_per_pixel / 8));
    color = *(unsigned int *)pixel;

    return (color);
}

int get_color_wall_south(t_general *general, int x, int h_wall, int max_wall_h)
{
    t_sprites       *sprites;
    char            *pixel;
    unsigned int    color;
    int             size_wall;
    
    int             x_pix;
    int             y_pix;

    size_wall = 64;
    sprites = general->sprites;
    
    x_pix = roundf((x % size_wall)*general->sprites->wall_south->sprite_w/size_wall);
    y_pix = roundf(h_wall * general->sprites->wall_south->sprite_h/ max_wall_h);
    
    pixel = sprites->wall_south->data_spr.addr + (y_pix * sprites->wall_south->data_spr.line_length + x_pix * (sprites->wall_south->data_spr.bits_per_pixel / 8));
    color = *(unsigned int *)pixel;
    
    return (color);
}

int get_color_wall_east(t_general *general, int x, int h_wall, int max_wall_h)
{

    t_sprites       *sprites;
    int             size_wall;
    char            *pixel;
    unsigned int    color;

    int             x_pix;
    int             y_pix;
    
    sprites = general->sprites;
    size_wall = 64;
    
    x_pix = roundf((x % size_wall)*general->sprites->wall_east->sprite_w/size_wall);
    y_pix = roundf(h_wall * general->sprites->wall_east->sprite_h/ max_wall_h);

    //printf("EST %d\n", h_wall);

    pixel = sprites->wall_east->data_spr.addr + y_pix * sprites->wall_east->data_spr.line_length + x_pix * (sprites->wall_east->data_spr.bits_per_pixel / 8);
    color = *(unsigned int *)pixel;
    return (color);
}

int get_color_wall_west(t_general *general, int x, int h_wall, int max_wall_h)
{
    t_sprites       *sprites;
    int             size_wall;
    char            *pixel;
    unsigned int    color;

    int             x_pix;
    int             y_pix;
    
    sprites = general->sprites;
    size_wall = 64;

    x_pix = roundf((x % size_wall)*general->sprites->wall_west->sprite_w/size_wall);
    y_pix = roundf(h_wall * general->sprites->wall_west->sprite_h / max_wall_h);


    pixel = sprites->wall_west->data_spr.addr + y_pix * sprites->wall_west->data_spr.line_length + x_pix * (sprites->wall_west->data_spr.bits_per_pixel / 8);
    color = *(unsigned int *)pixel;
    return (color);
}
