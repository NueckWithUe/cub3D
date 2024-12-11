/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:10 by nnagel            #+#    #+#             */
/*   Updated: 2024/12/11 14:50:06 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static float	get_ang(char direction)
{
	if (direction == 'N')
		return ((3 * M_PI) / 2);
	if (direction == 'S')
		return (M_PI / 2);
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
	while (data->map->con[y][x])
	{
		curr = data->map->con[y][x];
		if ((curr == 'N') || (curr == 'S') || (curr == 'E') || (curr == 'W'))
		{
			data->player->pos_x = (x * CUB_SIZ) + (CUB_SIZ / 2);
			data->player->pos_y = (y * CUB_SIZ) + (CUB_SIZ / 2);
			data->player->angle = get_ang(curr);
			data->player_x = y;
			data->player_y = x;
		}
		x++;
		if (data->map->con[y][x] == '\n')
		{
			y++;
			x = 0;
		}
	}
	return (data->player);
}

static int	check_conf(t_data *data)
{
	if (data->tnorth && data->tsouth && data->teast && data->twest)
		return (1);
	ft_print_error("Texture is missing");
	return (0);
}

void leaks()
{
	system("leaks cub3D");
}

int	main(int argc, char **argv)
{
	atexit(leaks);
	t_data	*data;

	if (argc != 2)
		return (ft_print_error("Too few/much arguments"), 1);
	if (!ft_error_handling(argv))
		return (1);
	data = init_data();
	if (!data)
		return (1);
	if (data->error > 0)
		return (free_data(data), 1);
	data->map = get_map(argv, data);
	if (!validate_map(data->map->con))
	{
		data = ft_free(data);
		return (1);
	}
	if (!check_conf(data))
		exit(1);
	data->player = get_pos(data);
	ff_go(data);
	mlx_loop_hook(data->mlx, &ft_keypress, (void *)data);
	mlx_loop(data->mlx);
	data = ft_free(data);
	return (0);
}
