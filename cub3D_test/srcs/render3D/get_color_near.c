#include "../../header.h"

int get_color_wall_south_near(t_general *general, int x, int h_wall, float dist)
{

    char            *pixel;
    int             x_pix;
    int             y_pix;
    int             start;
    int             end;

    x_pix = roundf((x % general->scene->map.size_wall) * general->sprites->wall_south->sprite_w / general->scene->map.size_wall);

    start = (general->sprites->wall_south->sprite_h - (int) roundf(dist * general->sprites->wall_south->sprite_h)) / 2;
    end = start + (int) roundf(dist * general->sprites->wall_south->sprite_h);

    y_pix = start + (int) roundf(((float) h_wall / (float) HEIGHT) * (float) (end - start));
    pixel = general->sprites->wall_south->data_spr.addr + (y_pix * general->sprites->wall_south->data_spr.line_length + x_pix * (general->sprites->wall_south->data_spr.bits_per_pixel / 8));
    
    return (*(unsigned int *)pixel);
}

int get_color_wall_north_near(t_general *general, int x, int h_wall, float dist)
{

    char            *pixel;
    int             x_pix;
    int             y_pix;
    int             start;
    int             end;

    x_pix = roundf((x % general->scene->map.size_wall) * general->sprites->wall_north->sprite_w / general->scene->map.size_wall);

    start = (general->sprites->wall_north->sprite_h - (int) roundf(dist * general->sprites->wall_north->sprite_h)) / 2;
    end = start + (int) roundf(dist * general->sprites->wall_north->sprite_h);

    y_pix = start + (int) roundf(((float) h_wall / (float) HEIGHT) * (float) (end - start));
    pixel = general->sprites->wall_north->data_spr.addr + (y_pix * general->sprites->wall_north->data_spr.line_length + x_pix * (general->sprites->wall_north->data_spr.bits_per_pixel / 8));
    
    return (*(unsigned int *)pixel);
}

int get_color_wall_west_near(t_general *general, int x, int h_wall, float dist)
{

    char            *pixel;
    int             x_pix;
    int             y_pix;
    int             start;
    int             end;

    x_pix = roundf((x % general->scene->map.size_wall) * general->sprites->wall_west->sprite_w / general->scene->map.size_wall);

    start = (general->sprites->wall_west->sprite_h - (int) roundf(dist * general->sprites->wall_west->sprite_h)) / 2;
    end = start + (int) roundf(dist * general->sprites->wall_west->sprite_h);

    y_pix = start + (int) roundf(((float) h_wall / (float) HEIGHT) * (float) (end - start));
    pixel = general->sprites->wall_west->data_spr.addr + (y_pix * general->sprites->wall_west->data_spr.line_length + x_pix * (general->sprites->wall_west->data_spr.bits_per_pixel / 8));
    
    return (*(unsigned int *)pixel);
}

int get_color_wall_east_near(t_general *general, int x, int h_wall, float dist)
{

    char            *pixel;
    int             x_pix;
    int             y_pix;
    int             start;
    int             end;

    x_pix = roundf((x % general->scene->map.size_wall) * general->sprites->wall_east->sprite_w / general->scene->map.size_wall);

    start = (general->sprites->wall_east->sprite_h - (int) roundf(dist * general->sprites->wall_east->sprite_h)) / 2;
    end = start + (int) roundf(dist * general->sprites->wall_east->sprite_h);

    y_pix = start + (int) roundf(((float) h_wall / (float) HEIGHT) * (float) (end - start));
    pixel = general->sprites->wall_east->data_spr.addr + (y_pix * general->sprites->wall_east->data_spr.line_length + x_pix * (general->sprites->wall_east->data_spr.bits_per_pixel / 8));
    
    return (*(unsigned int *)pixel);
}
