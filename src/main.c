#include "../include/cub3D.h"

static void print_arr(char **arr)
{
	int i = 0;

	while (arr[i])
	{
		ft_printf("%s", arr[i]);
		i++;
	}
	ft_printf("\n");
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
	print_arr(data->map);
	mlx_loop(data->mlx);
	ft_printf("Player position x: %d\n", data->player->pos_x);
	return (0);
}