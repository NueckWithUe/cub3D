NAME	=		cub3D
CC		=		cc
CFLAGS	=		-Wall -Wextra -Werror

SRCDIR	=		src
SRC		=		main.c \
				error_handling.c \
				init.c \
				get_map.c \
				map_utils.c \
				keys.c \
				map_error.c \
				free.c

RCDIR	=		src/raycasting
RCSRC	=		raycasting.c \
				convert_ray.c \
				ddr.c

LIBFT	=		lib/libft/libft.a
MLX_LIB	=		lib/MLX42/build/libmlx42.a

VPATH	=		$(SRCDIR):$(RCDIR)

OBJ		=		$(addprefix obj/, $(SRC:%.c=%.o) $(RCSRC:%.c=%.o))

$(NAME):		$(LIBFT) $(MLX_LIB) $(OBJ)
				@echo "Compiling $(NAME)"
				@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) ./lib/MLX42/build/libmlx42.a -Iinclude -lglfw -lm -o $(NAME) && echo "Compiling successful"

$(LIBFT):
				@cd lib/libft && make

$(MLX_LIB):
	@echo "Pulling MLX library"
	@git clone https://github.com/codam-coding-college/MLX42.git lib/MLX42 > /dev/null 2>&1
	@cd lib/MLX42 && git checkout 4c275721d0de1a9c514c857c29e9dd235d874591 > /dev/null 2>&1 && cd ..
	@cmake lib/MLX42 -B lib/MLX42/build > /dev/null 2>&1
	@cmake --build lib/MLX42/build -j4 > /dev/null 2>&1

all:			$(NAME)

obj/%.o:		%.c
				@mkdir -p obj/
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@cd lib/libft && make clean
				@rm -rf obj/

fclean:			clean
				@cd lib/libft && make fclean
				@rm -rf $(NAME) lib/MLX42

re:				fclean all

.PHONY:			all clean fclean re
