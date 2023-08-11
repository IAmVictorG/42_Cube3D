#include "../header.h"

void	printVec(t_vec vector)
{
	printf("x = %f, ", vector.x);
	printf("y = %f, ", vector.y);
	printf("z = %f", vector.z);
	printf("\n");
}

void	printCoord(t_coord coord)
{
	printf("Coord x = %d ", coord.x);
	printf("y = %d ", coord.y);
	printf("z = %d\n", coord.z);
}

void	print_tab(char **tab)
{
	int i;
	
	printf("--------------------------------\n\n");
	i = 0;
	while (tab[i] != NULL)
	{
		printf("[%s] (%d)\n", tab[i],i);
		i++;
	}
	printf("\n---------------------------------\n");
}

void	printMap(t_map  map)
{
	printf("----MAP----\n");
	print_tab(map.matrix);
	printf("   height_map = %d\n", map.height_map);
	printf("    width_map = %d\n", map.width_map);
	printf("heigth_matrix = %d\n", map.height_matrix);
	printf(" width_matrix = %d\n", map.width_matrix);
	printf("    size_wall = %d\n", SIZE_WALL);
	printf("\n");

}

void	print_player(t_player player)
{
	printf("----PLAYER----\n");
	printCoord(player.coord_ini);
	printf("pos : ");
	printCoord(player.pos);
	printf("pos2D : \n");
	printCoord(player.pos2D);
	printf("dir : ");
	printVec(player.dir);
	printf("speed = %f\n", player.speed);
	printf("\n");
}

void	print_sprite(t_sprite *sprite)
{
	printf("         path = %s\n", sprite->path);
	printf(" sprite width = %d\n", sprite->sprite_w);
	printf("sprite heigth = %d\n", sprite->sprite_h);
	printf("  line length = %d\n", sprite->data_spr.line_length);
	printf("\n");
}

void	print_sprites(t_sprites *sprites)
{
	printf("----TEXTURES SPRITES----\n");
	printf("NORTH :\n");
	print_sprite(sprites->wall_north);
	printf("SOUTH :\n");
	print_sprite(sprites->wall_south);
	printf("EAST  :\n");
	print_sprite(sprites->wall_east);
	printf("WEST  :\n");
	print_sprite(sprites->wall_west);
	printf("\n");
}

void	print_scene (t_scene *scene)
{
	printf("----SCENE----\n");
	printf("button minimap = %d\n", scene->mini_map);
	printf("    ceil_color = %X\n", scene->sky_color);
	printf("   floor_color = %X\n", scene->floor_color);
	printf("\n");
	printMap(scene->map);
	print_player(scene->player);
}
