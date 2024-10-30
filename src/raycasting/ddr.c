/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ddr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:20:35 by nnagel            #+#    #+#             */
/*   Updated: 2024/10/30 16:33:57 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ddr(t_data *data, int *hit_x, int *hit_y)
{
	float	dir_x;
	float	dir_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	side_dist_x;
	float	side_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;

	map_x = (int)data->player->pos_x;
	map_y = (int)data->player->pos_y;
	dir_x = data->player->d_x;
	dir_y = data->player->d_y;
	delta_dist_x = fabsf(1 / dir_x);
	delta_dist_y = fabsf(1 / dir_y);
	if (dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (data->player->pos_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1 - data->player->pos_x) * delta_dist_x;
	}
	if (dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (data->player->pos_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1 - data->player->pos_y) * delta_dist_y;
	}
	while (1)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
		}
		if (data->map->con[(int)(map_y / 64)][(int)(map_x / 64)] == '1')
			break ;
	}
	*hit_x = map_x;
	*hit_y = map_y;
}
