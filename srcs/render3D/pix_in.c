#include "../../header.h"

int	pix_in_S (t_vec ray, int size_wall)
{
	return (int) ray.y % size_wall == 0;
}

int	pix_in_N (t_vec ray, int size_wall)
{
	return (int) ray.y % size_wall == size_wall - 1;
}

int	pix_in_E (t_vec ray, int size_wall)
{
	return (int) ray.x % size_wall == 0;
}

int	pix_in_W (t_vec ray, int size_wall)
{
	return (int) ray.x % size_wall == size_wall - 1;
}