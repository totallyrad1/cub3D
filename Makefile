NAME = cub3D

SRCS = main.c mlx.c ./get_next_line/get_next_line_utils.c ./get_next_line/get_next_line.c ./parsing/parsing.c ./parsing/fn_write.c ./parsing/syntaxerror.c
OBJS = $(SRCS:.c=.o)

CC = cc -Wall -Wextra -Werror -g -fsanitize=address

RM = rm -f

MLX = -lm -lmlx -framework OpenGL -framework AppKit

%.o : %.c header.h defines.h 
	$(CC) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(MLX) $(OBJS) -o $(NAME)

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : clean