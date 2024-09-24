NAME	=		cub3D
CC		=		cc
CFLAGS	=		-Wall -Wextra -Werror

SRCDIR	=		src
SRC		=		main.c \
				error_handling.c \
				init.c \
				get_map.c

RTDIR	=		src/raycasting
RTSRC	=		raycasting.c

LIBFT	=		libs/libft/libft.a
GNL		=		libs/get_next_line/

VPATH	=		$(SRCDIR):$(RTDIR)

OBJ		=		$(addprefix obj/, $(SRC:%.c=%.o) $(RTSRC:%.c=%.o))

$(NAME):		$(LIBFT) install_mlx $(OBJ)
				$(CC) $(CFLAGS) $(GNL)*.c $(OBJ) $(LIBFT) -o $(NAME) ./libs/MLX42/build/libmlx42.a -Iinclude -lglfw

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