#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>

# include "libft.h"
# include "get_next_line.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_player
{
	int	pos_x;
	int	pos_y;
}	t_player;

typedef struct s_data
{
	mlx_t		*mlx;
	t_player	*player;
	char		**map;
}	t_data;

int		ft_error_handling(char **argv);
int		ft_check_extension(char *s);
int		ft_print_error(char *errmsg);
t_data	*init_data(void);

#endif