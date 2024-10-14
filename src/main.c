/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:10 by nnagel            #+#    #+#             */
/*   Updated: 2024/10/14 18:00:06 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static double	get_ang(char direction)
{
	if (direction == 'N')
		return (M_PI / 2);
	if (direction == 'S')
		return ((3 * M_PI) / 2);
	if (direction == 'E')
		return (0);
	if (direction == 'W')
		return (M_PI);
	return (42);
}

static t_player	*get_pos(t_data *data)
{
	int		x;
	int		y;
	char	curr;

	x = 0;
	y = 0;
	while (data->map->con[y])
	{
		while (data->map->con[y][x])
		{
			curr = data->map->con[y][x];
			if ((curr == 'N') || (curr == 'S')
				|| (curr == 'E') || (curr == 'W'))
			{
				data->player->pos_x = x;
				data->player->pos_y = y;
				data->player->angle = get_ang(curr);
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
	data->map = get_map(argv, data);
	if (!ft_check_void(data->map))
		return (ft_print_error("Map leads into void"), 1);
	data->player = get_pos(data);
	mlx_key_hook(data->mlx, &ft_keypress, (void *)data);
	mlx_loop_hook(data->mlx, &raycaster, (void *)data);
	mlx_loop(data->mlx);
	return (0);
}
