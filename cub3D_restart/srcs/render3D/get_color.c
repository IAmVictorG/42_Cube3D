#include "render3D.h"

int get_color_wall_north(t_general *general, int x, int h_wall, int max_wall_h)
{
    t_sprites       *sprites;
    char            *pixel;
    unsigned int    color;


    int             x_pix;
    int             y_pix;


    sprites = general->sprites;


    //x_pix = (int) roundf((((float)((int) x % size_wall) + (float)(x - (int) x)) / (float) size_wall) * (float) sprites->wall_north->sprite_w); 
    
    
    
    
    x_pix = (x % SIZE_WALL) * sprites->wall_north->sprite_w / SIZE_WALL;
    y_pix = (h_wall * general->sprites->wall_north->sprite_h / max_wall_h) % SIZE_WALL;


    if (x_pix < 0 || x_pix >= 64)
    {

        printf("x_pix = %d %d\n",x, x_pix);
    }
    if (y_pix < 0 || y_pix >= 64)
    {

        printf("y_pix = %d %d\n",h_wall, y_pix);
    }

    pixel = sprites->wall_north->data_spr.addr + (y_pix * sprites->wall_north->data_spr.line_length + x_pix * (sprites->wall_north->data_spr.bits_per_pixel / 8));
    color = *(unsigned int *)pixel;

    return (color);
}

int get_color_wall_south(t_general *general, int x, int h_wall, int max_wall_h)
{
    t_sprites       *sprites;
    char            *pixel;
    unsigned int    color;

    
    int             x_pix;
    int             y_pix;


    sprites = general->sprites;

    //x_pix = (int) round((((float)((int) x % size_wall) + (float)(x - (int) x)) / (float) size_wall) * (float) sprites->wall_north->sprite_w); 
    x_pix = (x % SIZE_WALL) * sprites->wall_south->sprite_w / SIZE_WALL;

    
    //x_pix = roundf(((int)x % size_wall)*general->sprites->wall_south->sprite_w/size_wall);
    y_pix = (h_wall * general->sprites->wall_south->sprite_h/ max_wall_h) % SIZE_WALL;
    
    if (x_pix < 0 || x_pix >= 64)
        printf("x_pix = %d\n", x_pix);

    if (y_pix < 0 || y_pix >= 64)
        printf("y_pix = %d\n", y_pix);



    pixel = sprites->wall_south->data_spr.addr + (y_pix * sprites->wall_south->data_spr.line_length + x_pix * (sprites->wall_south->data_spr.bits_per_pixel / 8));
    color = *(unsigned int *)pixel;

    //printCoord(create_trgb_reverse(color));

    return (color);
}

int get_color_wall_east(t_general *general, int x, int h_wall, int max_wall_h)
{

    t_sprites       *sprites;

    char            *pixel;
    unsigned int    color;

    int             x_pix;
    int             y_pix;
    
    sprites = general->sprites;

    

    //x_pix = (int) roundf((((float)((int) x % size_wall) + (float)(x - (int) x)) / (float) size_wall) * (float) sprites->wall_north->sprite_w); 

    x_pix = (x % SIZE_WALL) * sprites->wall_east->sprite_w / SIZE_WALL;


    //x_pix = roundf((x % size_wall)*general->sprites->wall_east->sprite_w/size_wall);
    y_pix = (h_wall * general->sprites->wall_east->sprite_h/ max_wall_h) % SIZE_WALL;

    //printf("EST %d\n", h_wall);

    if (x_pix < 0 || x_pix >= 64)
        printf("x_pix = %d\n", x_pix);

    if (y_pix < 0 || y_pix >= 64)
        printf("y_pix = %d\n", y_pix);


    pixel = sprites->wall_east->data_spr.addr + y_pix * sprites->wall_east->data_spr.line_length + x_pix * (sprites->wall_east->data_spr.bits_per_pixel / 8);
    color = *(unsigned int *)pixel;
    return (color);
}

int get_color_wall_west(t_general *general, int x, int h_wall, int max_wall_h)
{
    t_sprites       *sprites;

    char            *pixel;
    unsigned int    color;

    int             x_pix;
    int             y_pix;
    
    sprites = general->sprites;


    //x_pix = roundf((x % size_wall)*general->sprites->wall_west->sprite_w/size_wall);
    //x_pix = (int) roundf((((float)((int) x % size_wall) + (float)(x - (int) x)) / (float) size_wall) * (float) sprites->wall_north->sprite_w); 

    x_pix = (x % SIZE_WALL) * sprites->wall_west->sprite_w / SIZE_WALL;
    y_pix = (h_wall * general->sprites->wall_west->sprite_h / max_wall_h) % SIZE_WALL;

    if (x_pix < 0 || x_pix >= 64)
        printf("x_pix = %d\n", x_pix);

    if (y_pix < 0 || y_pix >= 64)
        printf("y_pix = %d\n", y_pix);

    pixel = sprites->wall_west->data_spr.addr + y_pix * sprites->wall_west->data_spr.line_length + x_pix * (sprites->wall_west->data_spr.bits_per_pixel / 8);
    color = *(unsigned int *)pixel;
    return (color);
}
