NAME = cub3D

INCLUDES = includes

LINUX_FLAGS = -lm -lX11 -lXext -lpthread

MAC_FLAGS = -framework OpenGL -framework AppKit

SRCS =  $(addprefix includes/get_next_line/, get_next_line.c get_next_line_utils.c) \
		$(addprefix srcs/, main.c init_window.c hook.c display.c) \
		$(addprefix srcs/render2D/, minimap.c) \
		$(addprefix srcs/parsing/, initializer.c args_manager.c copy_file_utils.c parsing.c wall_manager.c map_parser.c) \
		$(addprefix srcs/game_tools/, utils.c draw_segment.c) \
		$(addprefix srcs/render3D/, ray_caster.c get_color.c 3D_wall_render.c find_pixel_screen.c) 

LIBS 	= $(addprefix includes/, libft/libft.a)
OBJS	= ${SRCS:.c=.o}
CFLAGS	=  -Wall -Wextra -Werror
CC		= gcc
RM		= rm -f
LEAKS   = leaks_cube3D
PROD	= test

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	make -C includes/mlx
	make -C includes/libft
	make -C includes/mlx_opengl
	cp includes/mlx/libmlx.dylib .
	$(CC)   $(CFLAGS) $(OBJS) $(LIBS) -L includes/mlx -lmlx $(MAC_FLAGS) -o $(NAME)

#-fsanitize=address -O2

$(LEAKS): $(OBJS)
	$(CC)   $(CFLAGS) $(OBJS) $(LIBS) -lz -L includes/mlx -lmlx $(MAC_FLAGS) -o $(LEAKS)

$(PROD): $(OBJS)
	$(CC)   $(CFLAGS) $(OBJS) $(LIBS) -L includes/mlx -lmlx $(MAC_FLAGS) -o $(NAME) -fsanitize=address


all:		$(NAME)

clean:
			$(RM) $(OBJS)
			make clean -C includes/mlx_opengl

fclean:		clean
			$(RM) $(NAME)
			make fclean -C includes/libft

re:			fclean all

.PHONY: all clean fclean re