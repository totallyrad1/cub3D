NAME = cub3D

NAME_B = cub3D_bonus

SRCS = manda/get_next_line/get_next_line.c manda/get_next_line/get_next_line_utils.c manda/main.c manda/mlx.c manda/parsing/fn_write.c manda/parsing/ft_atoi.c manda/parsing/ft_strncmp.c manda/parsing/ft_substr.c manda/parsing/parsing.c manda/parsing/parsing1.c manda/parsing/parsing2.c manda/parsing/syntaxerror.c manda/parsing/syntaxerror1.c manda/ray_casting.c manda/ray_casting_utils.c

SRCS_B = bonus/get_next_line/get_next_line_bonus.c bonus/get_next_line/get_next_line_utils_bonus.c bonus/main_bonus.c bonus/minimap_bonus.c bonus/mlx_bonus.c bonus/parsing/fn_write_bonus.c bonus/parsing/ft_atoi_bonus.c bonus/parsing/ft_strncmp_bonus.c bonus/parsing/ft_substr_bonus.c bonus/parsing/parsing1_bonus.c bonus/parsing/parsing2_bonus.c bonus/parsing/parsing_bonus.c bonus/parsing/syntaxerror1_bonus.c bonus/parsing/syntaxerror_bonus.c bonus/ray_casting_bonus.c bonus/ray_casting_utils_bonus.c bonus/sound_bonus.c

OBJS = $(SRCS:.c=.o)

OBJS_B = $(SRCS_B:.c=.o)

HEADER = manda/defines.h manda/get_next_line/get_next_line.h manda/header.h 

HEADER_B = bonus/defines_bonus.h bonus/get_next_line/get_next_line_bonus.h bonus/header_bonus.h

CC = cc -O3 -I ./mlx -g #-fsanitize=address #-Wall -Werror -Wextra -g -fsanitize=address 

RM = rm -f

LIBMLX = ./mlx/libmlx.a

MLX = $(LIBMLX) -lm -framework OpenGL -framework AppKit

all : $(NAME)

bonus : $(NAME_B)

manda/%.o : manda/%.c $(HEADER)
	$(CC) -c $< -o $@

bonus/%.o : bonus/%.c $(HEADER_B)
	$(CC) -c $< -o $@

$(LIBMLX) : 
	make -C ./mlx

$(NAME) : $(OBJS) $(LIBMLX)
	$(CC) $(MLX) $(OBJS) -o $(NAME)

$(NAME_B) : $(OBJS_B) $(LIBMLX) 
	$(CC) $(MLX) $(OBJS_B) -o $(NAME_B)

clean :
	$(RM) $(OBJS) $(OBJS_B)

fclean : clean
	make clean -C ./mlx
	$(RM) $(NAME) $(NAME_B)

re : fclean all

.PHONY : clean