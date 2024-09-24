NAME	=		cub3D
CC		=		cc
CFLAGS	=		-Wall -Wextra -Werror

SRCDIR	=		src
SRC		=		main.c \
				error_handling.c \
				init.c \
				get_map.c \
				keys.c

RCDIR	=		src/raycasting
RCSRC	=		raycasting.c

LIBFT	=		lib/libft/libft.a

VPATH	=		$(SRCDIR):$(RCDIR)

OBJ		=		$(addprefix obj/, $(SRC:%.c=%.o) $(RCSRC:%.c=%.o))

$(NAME):		install_mlx $(LIBFT) $(OBJ)
				$(CC) $(CFLAGS) $(OBJ) $(LIBFT) ./lib/MLX42/build/libmlx42.a -Iinclude -lglfw -o $(NAME)

$(LIBFT):
				cd lib/libft && make

install_mlx:
				@cd lib/MLX42 && cmake -B build && cmake --build build -j4

all:			$(NAME)

obj/%.o:		%.c
				@mkdir -p obj/
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				cd lib/libft && make clean
				rm -rf obj/

fclean:			clean
				cd lib/libft && make fclean
				rm -rf $(NAME)

re:				fclean install_mlx all

.PHONY:			all clean fclean re install_mlx