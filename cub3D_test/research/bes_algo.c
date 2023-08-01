#include <stdio.h>


typedef struct s_vec 
{
    float x;
    float y;
} t_vec;

t_vec algo_bresenham_border(t_vec start, t_vec end, int W, int H) 
{

	float fraction;
    float dx;
    float dy;

    int stepx;
	int stepy;

	dx = (float) end.x - (float) start.x; //dx = 50 - 25 = 25
	dy = (float) end.y - (float) start.y; //dy = 25 - 50 = -25


	/* Permet de savoir dans lequel des cadrans on se trouve */
    if (dy < 0.0f) 
	{
        dy = -dy;     
        stepy = -1;
    } 
	else 
	{
        stepy = 1;
    }

    if (dx < 0.0f) 
	{
        dx = -dx;
        stepx = -1;
    } 
	else 
	{
        stepx = 1;
    }

    dy *= 2;  // dy = 25 * 2 = 50
    dx *= 2;  // dx = 25 * 2 = 50

	//printf("dx = %f dy = %f\n", dx, dy);

    if (dx > dy) 
	{
        fraction = dy - (dx / 2);
        while (start.x >= 0 && start.x < W && start.y >= 0 && start.y < H) 
		{
            if (fraction >= 0) 
			{
                start.y += stepy;
                fraction -= dx;
            }
            start.x += stepx;
            fraction += dy;
        }
    } 
	else 
	{
        fraction = dx - (dy / 2);
        while (start.x >= 0 && start.x < W && start.y >= 0 && start.y < H) 
		{
            if (fraction >= 0) 
			{
                start.x += stepx;
                fraction -= dy;
            }
            start.y += stepy;
            fraction += dx;
        }
    }

    // Adjust to get the last point inside the window
    if (start.x < 0)
	{ 
		start.x = 0;
	}
    if (start.x >= W)
	{
		start.x = W - 1;
	}
    if (start.y < 0) 
	{
		start.y = 0;
	}
    if (start.y >= H) 
	{
		start.y = H - 1;
	}

    return start;
}

int main() 
{
    t_vec start = {1.0, 1.0};
    t_vec end = {50.0, 20.0};
    int W = 100, H = 100;

    t_vec border_point = algo_bresenham_border(start, end, W, H);
    printf("Point on the border: (%f, %f)\n", border_point.x, border_point.y);

    return 0;
}