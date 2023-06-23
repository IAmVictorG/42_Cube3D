SRCS 	= main.c

OBJS	= ${SRCS:.c=.o}

NAME	= cub3D

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make -C mlx
			make -C mlx_opengl
			cp mlx/libmlx.dylib .
			${CC} $^ -Lmlx -lmlx -o ${NAME}

	
all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re