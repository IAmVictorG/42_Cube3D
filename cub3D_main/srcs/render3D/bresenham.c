#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void	draw_line(int x0, int y0, int x1, int y1)
{
	printf("Control function\n");
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = x0 < x1 ? 1 : -1;
	sy = y0 < y1 ? 1 : -1;
	if (dx > dy)
		err = dx / 2;
	else
		err = -dy / 2;
	while (42) 
	{
		printf("Draw at (%d, %d)\n", x0, y0);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void draw_segment(int x0, int y0, int x1, int y1)
{
	printf("My DrawSegment Function\n");

	int dx = x1 - x0;
	int dy = y1 - y0;
	float err = 0.5f;

	if (abs(dx) >= abs(dy))
	{
		while (42)
		{
			if (err > 1.001f)
			{
				if (dy > 0)
					y0++;
				else
					y0--;
				err -= 1.0f;
			}
			printf("Draw at (%d, %d) {%f}\n", x0, y0, err);
			err += fabs((float) dy / (float)dx);
			if (x0 == x1)
				break;
			if (dx > 0)
				x0++;
			else
				x0--;
		}
	}
	else
	{
		while (42)
		{
			if (err > 1.001f)
			{
				if (dx > 0)
					x0++;
				else
					x0--;
				err -= 1.0f;
			}
			printf("Draw at (%d, %d) {%f}\n", x0, y0, err);
			err += fabs((float) dx / (float) dy);
			if (y0 == y1)
				break;
			if (dy > 0)
				y0++;
			else
				y0--;
		}
	}
}

int main(int argc, char const *argv[])
{
	draw_segment(0, 0, -10, 2);
	draw_line(0, 0, -10, 2);
	return (0);
}
