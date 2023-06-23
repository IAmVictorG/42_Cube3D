NAME = cube3D

INCLUDES = includes

LINUX_FLAGS = -lm -lX11 -lXext -lpthread

MAC_FLAGS = -framework OpenGL -framework AppKit

SRCS =  $(addprefix srcs/, main.c) \
		$(addprefix includes/get_next_line/, get_next_line.c get_next_line_utils.c)

LIBS = $(addprefix includes/, libft/libft.a)
OBJS	= ${SRCS:.c=.o}
CFLAGS	=  -Wall -Wextra -Werror
CC		= gcc
RM		= rm -f

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	make -C includes/libft
	make -C includes/mlx_openGL
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) includes/mlx_openGL/libmlx.a $(MAC_FLAGS) -o $(NAME)


all:		$(NAME)

clean:
			$(RM) $(OBJS)
			make clean -C includes/mlx_openGL

fclean:		clean
			$(RM) $(NAME)
			make fclean -C includes/libft

re:			fclean all

.PHONY: all clean fclean re