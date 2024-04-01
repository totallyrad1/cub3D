NAME = cub3D

SRCS = main.c mlx.c ./get_next_line/get_next_line_utils.c ./get_next_line/get_next_line.c ./parsing/parsing.c ./parsing/fn_write.c ./parsing/syntaxerror.c ./parsing/ft_atoi.c ./parsing/ft_substr.c ./parsing/ft_strncmp.c ./parsing/syntaxerror1.c ray_casting.c ray_casting_utils.c ./parsing/parsing1.c ./parsing/parsing2.c minimap.c sound.c
OBJS = $(SRCS:.c=.o)

CC = cc -O3 -I ./mlx #-Wall -Werror -Wextra #-g -fsanitize=address 

RM = rm -f

LIBMLX = ./mlx/libmlx.a

MLX = $(LIBMLX) -lm -framework OpenGL -framework AppKit

all : $(NAME)

%.o : %.c header.h defines.h 
	$(CC) -c $< -o $@

$(LIBMLX) : 
	make -C ./mlx

$(NAME) : $(OBJS) $(LIBMLX)
	$(CC) $(MLX) $(OBJS) -o $(NAME)


clean :
	$(RM) $(OBJS)

fclean : clean
	make clean -C ./mlx
	$(RM) $(NAME)

re : fclean all

.PHONY : clean