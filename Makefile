NAME = cube3D

INCLUDES = includes

LINUX_FLAGS = -lm -lX11 -lXext -lpthread

MAC_FLAGS = -framework OpenGL -framework AppKit

SRCS =  $(addprefix srcs/, main.c display.c render.c init_window.c) \
		$(addprefix srcs/game_tools/, hook.c utils.c) \
		$(addprefix includes/get_next_line/, get_next_line.c get_next_line_utils.c) \
		$(addprefix srcs/parsing/, copy_file_utils.c map_parser.c parse_utils.c parsing.c) \
		$(addprefix srcs/render2D/, mini_map.c 2D_player_render.c 2D_wall_render.c) \
		$(addprefix srcs/render3D/, ray_caster.c get_color.c 3D_wall_render.c) 

LIBS 	= $(addprefix includes/, libft/libft.a)
OBJS	= ${SRCS:.c=.o}
CFLAGS	=  -Wall -Wextra -Werror
CC		= gcc
RM		= rm -f
LEAKS   = leaks_cube3D
PROD	= test
LINUX = linux

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	make -C includes/mlx
	make -C includes/libft
	cp includes/mlx/libmlx.dylib .
	$(CC)   $(CFLAGS) $(OBJS) $(LIBS) -lz -L includes/mlx -lmlx $(MAC_FLAGS) -o $(NAME) -fsanitize=address -O2

$(LEAKS): $(OBJS)
	$(CC)   $(CFLAGS) $(OBJS) $(LIBS) -lz -L includes/mlx -lmlx $(MAC_FLAGS) -o $(LEAKS)

$(PROD): $(OBJS)
	$(CC)   $(CFLAGS) $(OBJS) $(LIBS)  $(MAC_FLAGS) -o $(NAME) -fsanitize=address

$(LINUX) : $(OBJS)
	make -C includes/minilibx-linux
	make -C includes/libft
	cp includes/minilibx-linux/libmlx.a .
	$(CC) $(OBJS) $(LIBS) -L includes/minilibx-linux  libmlx.a $(LINUX_FLAGS) -o $(NAME)
	



all:		$(NAME)

clean:
			$(RM) $(OBJS)
			make clean -C includes/mlx_opengl
			make clean -C includes/minilibx-linux

fclean:		clean
			$(RM) $(NAME)
			make fclean -C includes/libft

re:			fclean all

.PHONY: all clean fclean re