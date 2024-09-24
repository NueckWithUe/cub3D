#include "../include/cub3D.h"

// static void print_arr(char **arr)
// {
// 	int i = 0;

// 	while (arr[i])
// 	{
// 		ft_printf("%s", arr[i]);
// 		i++;
// 	}
// 	ft_printf("\n");
// }

static t_player	*get_pos(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->map[y])
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'P')
			{
				data->player->pos_x = x;
				data->player->pos_y = y;
			}
			x++;
		}
		y++;
		x = 0;
	}
	return (data->player);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (ft_print_error("Too few/much arguments"), 1);
	if (!ft_error_handling(argv))
		return (1);
	data = init_data();
	data->map = get_map(argv);
	if (!ft_check_void(data->map))
		return (ft_print_error("Map leads into void"), 1);
	data->player = get_pos(data);
	raycaster();
	mlx_key_hook(data->mlx, &ft_keypress, (void *)data);
	mlx_loop(data->mlx);
	return (0);
}