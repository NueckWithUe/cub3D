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

LIBFT	=		libs/libft/libft.a

VPATH	=		$(SRCDIR):$(RCDIR)

OBJ		=		$(addprefix obj/, $(SRC:%.c=%.o) $(RCSRC:%.c=%.o))

$(NAME):		$(OBJ) $(LIBFT) install_mlx
				$(CC) $(CFLAGS) $(OBJ) $(LIBFT) ./libs/MLX42/build/libmlx42.a -Iinclude -lglfw -o $(NAME)

$(LIBFT):
				cd libs/libft && make

libs/MLX42:
				@cd libs && git clone https://github.com/codam-coding-college/MLX42.git
				@cd libs/MLX42 && cmake -B build && cmake --build build -j4

install_mlx:	libs/MLX42

all:			$(NAME)

obj/%.o:		%.c
				@mkdir -p obj/
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				cd libs/libft && make clean
				rm -rf obj/

fclean:			clean
				cd libs/libft && make fclean
				rm -rf $(NAME)

re:				fclean install_mlx all

.PHONY:			all clean fclean re install_mlx