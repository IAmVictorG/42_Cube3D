#include "../header.h"

void trace_ray(t_general *general);

void    draw_grid(t_general *general)
{
	int		width_grid;
	int		heigth_grid;
    t_mlib  *mlib;
	int		i;
	int		j;

	width_grid = WIDTH / general->scene->map.width_matrix;
	heigth_grid = HEIGHT / general->scene->map.height_matrix;



    mlib = general->mlib;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			if (i % width_grid == 0)
			{
				my_mlx_pixel_put(&mlib->data, i, j, 0x00AA00);	
			}

			if (j % heigth_grid == 0)
			{
				my_mlx_pixel_put(&mlib->data, i, j, 0x00AA00);
			}

			j++;
		}
		i++;
	}
	
}


void    draw_wall(t_general *general, t_coord coord_wall)
{   
    int 	x;
    int 	y;
	t_mlib 	*mlib;
	int		width_grid;
	int		heigth_grid;

	width_grid = WIDTH / general->scene->map.width_matrix;
	heigth_grid = HEIGHT / general->scene->map.height_matrix;
    mlib = general->mlib;


    y = 0;
    while (y < heigth_grid)
    {
        x = 0;
        while (x < width_grid)
        {
            my_mlx_pixel_put(&mlib->data, coord_wall.x * width_grid + x, coord_wall.y * heigth_grid + y, 0x1100FF);
            x++;
        }
        y++;
    }
}

void render_wall2D(t_general *general)
{
	t_coord	coord_wall;
	// int		width_grid;
	// int		heigth_grid;
    int 	i;
    int 	j;

	// width_grid = WIDTH / general->scene->map.width_matrix;
	// heigth_grid = HEIGHT / general->scene->map.height_matrix;

    j = 0;
    while (j < general->scene->map.height_matrix)
    {
        i = 0;
        while (i < general->scene->map.width_matrix)
        {
            if (general->scene->map.matrix[j][i] == '1')
            {
				coord_wall.x = i;
				coord_wall.y = j;

				//printCoord(coord_wall);
                draw_wall(general, coord_wall);
            }
            i++;
        }
        j++;
    }

}

void draw_player(t_general *general)
{
    t_mlib  *mlib;
    int		color;
    int     size;
    int     x;
    int     y;

    mlib = general->mlib;
    x = general->scene->player.pos2D.x;
    y = general->scene->player.pos2D.y;
    color = 0x00FF00;
    size = 3;

    for(int i = -size; i <= size; i++) 
    {
        my_mlx_pixel_put(&mlib->data, x + i, y, color);
        my_mlx_pixel_put(&mlib->data, x, y + i, color);
    }
}

void draw_arrow(t_general *general, t_coord start_arrow, t_vec dir) 
{

    //t_mlib  *mlib;
    //mlib = general->mlib;

    int color = 0x00FF00;
    t_coord end_arrow;


    start_arrow = convert_coord_for_2D(start_arrow, general->scene->map.width_map, general->scene->map.height_map);
    end_arrow.x = start_arrow.x + 10 * dir.x;
    end_arrow.y = start_arrow.y + 10 * dir.y;


    // int x1 = start_arrow.x + end_arrow.x;
    // int y1 = start_arrow.y + end_arrow.y;

    //draw_line(general, x0, y0, x1, y1, color); // Draw the main line of the arrow

    // Compute the direction of the arrow for the arrowhead
    // float arrow_dir_x = end_arrow.x / sqrtf(end_arrow.x * end_arrow.x + end_arrow.y * end_arrow.y);
    // float arrow_dir_y = end_arrow.y / sqrtf(end_arrow.x * end_arrow.x + end_arrow.y * end_arrow.y);

    // Compute the perpendicular direction for the arrowhead
    // float arrow_perp_x = -arrow_dir_y;
    // float arrow_perp_y = arrow_dir_x;

    // Length of the arrowhead
    // float head_len = 7;

    my_mlx_pixel_put(&general->mlib->data, end_arrow.x, end_arrow.y, color);

    // Draw the two sides of the arrowhead
    //draw_line(general, x1, y1, x1 - head_len * (arrow_dir_x + arrow_perp_x), y1 - head_len * (arrow_dir_y + arrow_perp_y), color);
    //draw_line(general, x1, y1, x1 - head_len * (arrow_dir_x - arrow_perp_x), y1 - head_len * (arrow_dir_y - arrow_perp_y), color);
}


int	render_mini_map(t_general *general)
{
    t_mlib  *mlib = general->mlib;


    mlib->data.img_ptr = mlx_new_image(mlib->utils.mlx, WIDTH, HEIGHT);
    mlib->data.addr = mlx_get_data_addr(mlib->data.img_ptr, &mlib->data.bits_per_pixel, &mlib->data.line_length, &mlib->data.endian);

    render_wall2D(general);
    draw_grid(general);
    move(general);
    //launch_mid_ray(general);

    draw_player(general);

    draw_arrow(general, general->scene->player.pos, general->scene->player.dir);
    

    mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, mlib->data.img_ptr, 0, 0);
    mlx_destroy_image(mlib->utils.mlx, mlib->data.img_ptr);

    return (0);



}


int render(t_general *general)
{

    if (general->scene->mini_map == 1)
    {
        render_mini_map(general);
    }
    else
    {
        render_game(general);
    }

    return (1);
}



void init_window(t_general *general, t_mlib *mlib)
{

	(void) general;


    mlib->utils.win = mlx_new_window(mlib->utils.mlx, WIDTH, HEIGHT, "Cube3D");

    mlx_hook(mlib->utils.win, 2, 0, key_pression, general);  // Hook pour les touches pressées
    mlx_hook(mlib->utils.win, 3, 0, key_release, general);
    // mlx_hook(mlib->utils.win, 4, 0, mouse_press, mlib);  // Hook pour les clics de souris
    // mlx_hook(mlib->utils.win, 17, 0, close_window, mlib);  // Hook pour la fermeture de la fenêtre

    mlx_loop_hook(mlib->utils.mlx, render, general);
    


    //mlx_put_image_to_window(mlib->utils.mlx, mlib->utils.win, sprites->wall_north.data_spr.img_ptr, 0, 0);

    mlx_loop(mlib->utils.mlx);
}