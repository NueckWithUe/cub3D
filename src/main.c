#include "../include/cub3D.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	if (argc != 2)
		return (ft_print_error("Too few/much arguments"), 1);
	if (!ft_error_handling(argv))
		return (1);
	data = init_data();
	ft_printf("Player position x: %d\n", data->player->pos_x);
	return (0);
}