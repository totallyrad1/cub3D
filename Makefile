NAME = cub3D

NAME_B = cub3D_bonus

SRCS = manda/exitfn.c manda/get_next_line/get_next_line.c manda/get_next_line/get_next_line_utils.c manda/main.c manda/mlx.c manda/mouse.c manda/parsing/fn_write.c manda/parsing/ft_atoi.c manda/parsing/ft_strncmp.c manda/parsing/ft_substr.c manda/parsing/parsing.c manda/parsing/parsing1.c manda/parsing/parsing2.c manda/parsing/syntaxerror.c manda/parsing/syntaxerror1.c manda/ray_casting.c manda/ray_casting_utils.c manda/ray_casting_utils2.c manda/ray_generator.c manda/render.c manda/textures.c

SRCS_B = bonus/draw_map_bonus.c bonus/exitfn_bonus.c bonus/get_next_line/get_next_line_bonus.c bonus/get_next_line/get_next_line_utils_bonus.c bonus/main_bonus.c bonus/minimap_bonus.c bonus/mlx_bonus.c bonus/mouse_bonus.c bonus/parsing/fn_write_bonus.c bonus/parsing/ft_atoi_bonus.c bonus/parsing/ft_strncmp_bonus.c bonus/parsing/ft_substr_bonus.c bonus/parsing/parsing1_bonus.c bonus/parsing/parsing2_bonus.c bonus/parsing/parsing_bonus.c bonus/parsing/syntaxerror1_bonus.c bonus/parsing/syntaxerror_bonus.c bonus/ray_casting_bonus.c bonus/ray_casting_utils_bonus.c bonus/ray_casting_utils_bonus2.c bonus/ray_generator_bonus.c bonus/render_bonus.c bonus/textures_bonus.c
OBJS = $(SRCS:.c=.o)

OBJS_B = $(SRCS_B:.c=.o)

HEADER = manda/defines.h manda/get_next_line/get_next_line.h manda/header.h 

HEADER_B = bonus/defines_bonus.h bonus/get_next_line/get_next_line_bonus.h bonus/header_bonus.h

CC = cc -O3 -I ./mlx -Wall -Werror -Wextra

RM = rm -f

LIBMLX = ./mlx/libmlx.a

MLX = $(LIBMLX) -lm -framework OpenGL -framework AppKit

all : $(NAME)

bonus : $(NAME_B)

manda/%.o : manda/%.c $(HEADER)
	$(CC) -c $< -o $@

bonus/%.o : bonus/%.c $(HEADER_B)
	$(CC) -c $< -o $@

$(NAME) : $(OBJS) $(LIBMLX)
	$(CC) $(MLX) $(OBJS) -o $(NAME)

$(NAME_B) : $(OBJS_B) $(LIBMLX) 
	$(CC) $(MLX) $(OBJS_B) -o $(NAME_B)

clean :
	$(RM) $(OBJS) $(OBJS_B)

fclean : clean
	$(RM) $(NAME) $(NAME_B)

re : fclean all

.PHONY : clean