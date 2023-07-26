
t_vec create_ray(t_scene *scene, int pixel_x, int pixel_y)
{
    (void) scene;
    float aspect_ratio;
    t_vec dir_r;
    float dx; //increment x
    float dy; //increment y

    float d; //distance total


    d = 2.0f * tanf((float) FOV * 0.5f);
    dx = d / (float) WIDTH;
    
    aspect_ratio = (float) HEIGHT / (float) WIDTH;
    dy = dx * aspect_ratio;


    dir_r = (t_vec) {dx * pixel_x, dy * pixel_y, 1.0f};
    dir_r = vec_normalize(dir_r);
    printVec(dir_r);
    return (dir_r);
}

t_vec   absolute_to_relative(int x, int y, t_vec origin)
{
    t_vec   result;

    result.x = x - origin.x;
    result.y = y - origin.y;
    result.z = 0.0f;

    return (result);
}

t_vec   relative_to_absolute(float x, float y, t_vec origin)
{
    t_vec   result;

    result.x = x + origin.x;
    result.y = y + origin.y;
    result.z = 0.0f;

    return (result);

}

static  int is_in_definition_domain(t_vec pixel_relative, t_vec direction)
{
    return (pixel_relative.x * direction.x + pixel_relative.y * direction.y > 0);
}


int position_is_valid_pix(t_general *general, int i, int j)
{

    int     size_wall;
    char    **matrix;

    matrix = general->scene->map.matrix;
    size_wall = general->scene->map.size_wall;

    printf("c = %c ", matrix[j / size_wall][i / size_wall]);

    return (!(matrix[j / size_wall][i / size_wall] == '1'));
}

int read_rt_file(const char *filename, t_scene *scene)
{
    int fd;
    char *line = NULL;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return -1;
    while ((line = get_next_line(fd)) != NULL)
    {
        parse_line(scene, line);
    }
    close(fd);
    if (line)
        free(line);
    return 0;
}

void test(t_general *general)
{
    char **matrix = general->scene->map.matrix;
    int size_wall = general->scene->map.size_wall;


    int i = 0;
    int j = 0;


    int map_h = general->scene->map.height_map;
    int map_w = general->scene->map.width_map;

    while (j / size_wall < map_h)
    {
        i = 0;
        while (i / size_wall < map_w)
        {
            printf("j = %d i = %d \n", j / size_wall, i / size_wall );
            printf("%c\n", matrix[j/size_wall][i/size_wall]);
            i++;
        }
        printf("\n");
        j++;
    }
    sleep(1);
}

int convert_char_to_int(char *color)
{
    return (*color << 24 | *(color + 1) << 16 | *(color + 2) << 8 | *(color + 3));
}

void    trace_wall(t_general *general, t_sprite *sprite)
{
    int h = sprite->sprite_h;
    int w = sprite->sprite_w;

    int i;
    int j;
    char *color;

    //printf("h = %d & w = %d\n", h,w);

    j = 0;
    while (j < h)
    {
        i = 0;
        while (i < w)
        {
            color = sprite->data_spr.addr + j * sprite->data_spr.line_length + i * sprite->data_spr.bits_per_pixel / 8;
            my_mlx_pixel_put(&general->mlib->data, i,j, *(unsigned int *)color);
            i++;
        }
        j++;
    }
}


void    draw_ray2(t_general *general)
{
    /*Il faut ecrire a nouveau draw_ray en parcourant
    la range de x jusqu'au bord de la fenetre
    OU
    la range de y jusqu au bord de la fenetre
    penser a utiliser la trigonometrie
    
    */
    t_mlib *mlib;
    mlib = general->mlib;

    t_coord position = general->scene->player.pos;
    int     x_pix = general->scene->player.pos.x;
    int     y_pix = general->scene->player.pos.y;

    float   y_pix_f;
    float   x_pix_f;

    t_vec   direction = general->scene->player.dir;
    float   angle_player;
    float   x_div_y = 0;
    float   y_div_x = 0;


    if (direction.x > 0 && direction.y > 0)
    {
        angle_player = atan2f(direction.y, direction.x);
        //printf("SW ");
        //printf("angle_player = %f (%f)\n", angle_player, rad_to_deg(angle_player));
        y_div_x = direction.y / direction.x;
        x_div_y = direction.x / direction.y;

        //printf("y_div_x = %f x_div_y = %f\n", y_div_x, x_div_y);

        while (x_pix < WIDTH && y_pix < HEIGHT)
        {
            y_pix_f = (x_pix - position.x) * y_div_x + position.y;
            x_pix_f = (y_pix - position.y) * x_div_y + position.x;

            if (y_pix_f < HEIGHT)
            {
                my_mlx_pixel_put(&mlib->data, x_pix, y_pix_f, 0xFF0000);
            }

            if (x_pix_f < WIDTH)
            {
                my_mlx_pixel_put(&mlib->data, x_pix_f, y_pix, 0xFF0000);
            }



            x_pix++;
            y_pix++;
        }
        //exit(42);


    }

    if (direction.x < 0 && direction.y < 0)
    {
        angle_player = atan2f(direction.y, direction.x);
        printf("NE ");
        printf("angle_player = %f (%f)\n", angle_player, rad_to_deg(angle_player));


    }

    if (direction.x > 0 && direction.y < 0)
    {
        angle_player = atan2f(direction.y, direction.x);
        printf("NW ");
        printf("angle_player = %f (%f)\n", angle_player, rad_to_deg(angle_player));

    }

    if (direction.x < 0 && direction.y > 0)
    {
        angle_player = atan2f(direction.y, direction.x);
        printf("SE ");
        printf("angle_player = %f (%f)\n", angle_player, rad_to_deg(angle_player));

    }


//    t_coord range;

//     int x;
//     int y;

//     int range;

//     if (WIDTH - position.x < HEIGHT - position.y)
//     {
//         range = WIDTH - position.x;
//         while (position.x < range)
//         {
            


//             position.x++;
//         }



//     }
//     else
//     {
//         range = HEIGHT - position.y;
//     }



}

char *get_extension(const char *file_path)
{
    char    **tab;
    int     size_tb;

    tab = ft_split((char *) file_path, '.');
    if (tab == NULL)
        return (NULL);

    size_tb = size_tab(tab);
    printf("get_extension addr = %p\n", &(tab[size_tb - 1]));
    return (tab[size_tb - 1]);
}

/*t_vec calculate_rays(t_general *general, int x0, int y0, int x1, int y1, int size_wall, int window_width, int window_height) 
{
	//t_mlib *mlib;
	t_vec r;

	//mlib = general->mlib;


	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);

	//printf("dx = %d, dy = %d\n", dx, dy);

	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;
	(void) size_wall;

	while (42) 
	{
		// Ensure the pixel coordinates are within window bounds
		if (x0 >= 0 && x0 < window_width && y0 >= 0 && y0 < window_height) 
		{
			if (hit_a_wall(general,x0, y0) == 1)
				break;
		}
		else
			break;


		// if (x0 == x1 && y0 == y1)   
		//     break;
		int e2 = 2 * err;
		if (e2 > -dy) 
		{
			err -= dy;
			x0 += sx;
		}
		else if (e2 < dx) 
		{
			err += dx;
			y0 += sy;
		}
	}
	r.x = x0;
	r.y = y0;
	r.z = 0;
	return (r);
}

t_vec calculate_rays_bef(t_general *general, int x0, int y0, int x1, int y1, int size_wall, int window_width, int window_height) 
{
	//t_mlib *mlib;

	t_vec r_temp;

	//mlib = general->mlib;


	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);

	//printf("dx = %d, dy = %d\n", dx, dy);

	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;
	(void) size_wall;

	while (42) 
	{
		// Ensure the pixel coordinates are within window bounds
		if (x0 >= 0 && x0 < window_width && y0 >= 0 && y0 < window_height) 
		{
			if (hit_a_wall(general,x0, y0) == 1)
				break;
		}
		else
			break;

		r_temp.x = x0;
		r_temp.y = y0;

		// if (x0 == x1 && y0 == y1)   
		//     break;
		int e2 = 2 * err;
		if (e2 > -dy) 
		{
			err -= dy;
			x0 += sx;

		}
		else if (e2 < dx) 
		{
			err += dx;
			y0 += sy;
		}

	}

	return (r_temp);
}*/