/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:10 by nnagel            #+#    #+#             */
/*   Updated: 2024/11/11 12:32:23 by nnagel           ###   ########.fr       */
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

static void	*ft_free(t_data *data)
{
	int	i;

	i = 0;
	while (data->map->con[i])
	{
		free(data->map->con[i]);
		i++;
	}
	free(data->map);
	free(data->player);
	free(data->ray);
	mlx_delete_texture(data->tnorth);
	mlx_delete_texture(data->tsouth);
	mlx_delete_texture(data->teast);
	mlx_delete_texture(data->twest);
	mlx_delete_image(data->mlx, data->ibuffer);
	mlx_terminate(data->mlx);
	free(data);
	return (NULL);
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
	data->player = get_pos(data);
	mlx_loop_hook(data->mlx, &ft_keypress, (void *)data);
	mlx_loop_hook(data->mlx, &raycaster, (void *)data);
	mlx_loop(data->mlx);
	data = ft_free(data);
	return (0);
}
