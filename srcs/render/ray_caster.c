#include "../../header.h"

 t_vec create_ray(t_scene *scene, int pixel_x, int pixel_y)
{
    (void) scene;
    float aspect_ratio;
    t_vec dir;
    float dx; //increment x
    float dy; //increment y

    float d; //distance total

    aspect_ratio = (float) WIDTH / (float) HEIGHT;

    d = 2.0f * tanf((float) FOV * 0.5f);
    dx = d / (float) WIDTH;
    dy = dx * aspect_ratio;


    dir = (t_vec) {dx * pixel_x, dy * pixel_y, 1.0f};
    //dir = (t_vec) {d * (pixel_x / (float)WIDTH - 0.5f), d * (pixel_y / (float)HEIGHT - 0.5f) * aspect_ratio, 1.0f};
    dir = vec_normalize(dir);
    return (dir);
}

 int check_intesection(t_scene *scene, t_vec player_pos, t_vec dir)
{
    (void) scene;
    int hit;
    int i;
    int ngx; //next goal x
    int ngy; //next goal y

    if (dir.x > 0)
        ngx = (int) player_pos.x + 1;
    else
        ngx = (int) player_pos.x;
    if (dir.y > 0)
        ngy = (int) player_pos.y + 1;
    else
        ngy = (int) player_pos.y;
    hit = 0;
    i = 0;
    /*while (!hit && i < MAX_DISTANCE)
    {

    }*/
    return (0);
}

/*void draw_line(t_mlib *mlib, int x0, int y0, int x1, int y1, int color)
{
    // Bresenham's line algorithm
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        my_mlx_pixel_put(mlib->data.img_ptr, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
    my_mlx_pixel_put(mlib->data.img_ptr, 20, 20, 0x00FFFFFF);
}*/

void render(t_scene *scene, t_mlib *mlib)
{
    (void) scene;
    mlib->data.img_ptr = mlx_new_image(mlib->utils.mlx, WIDTH, HEIGHT);
    mlib->data.addr = mlx_get_data_addr(mlib->data.img_ptr, &mlib->data.bits_per_pixel, &mlib->data.line_length, &mlib->data.endian);

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            t_vec dir = create_ray(scene, i, j);
            my_mlx_pixel_put(&mlib->data, 200, 200, 0xFF00FF);
            (void) dir;
        }
    }
    printf("%d\n", mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, mlib->data.img_ptr, 0, 0));
}