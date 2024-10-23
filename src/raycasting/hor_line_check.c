/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hor_line_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:27:09 by nnagel            #+#    #+#             */
/*   Updated: 2024/10/23 16:31:18 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

float	horizontal_line_check(t_data *data)
{
	float	dist;
	int		map_x;
	int		map_y;

	dist = 0;
	if (data->ray->angle < M_PI)
	{
		data->ray->r_y = ((int)(data->player->pos_y / 64) * 64) - 0.0001;
		data->ray->r_x = (data->ray->r_y - data->player->pos_y) / tanf(data->ray->angle) + data->player->pos_x;
		data->ray->o_y = -64;
		data->ray->o_x = -data->ray->o_y / tanf(data->ray->angle);
	}
	else if (data->ray->angle > M_PI)
	{
		data->ray->r_y = ((int)(data->player->pos_y / 64) * 64) + 64;
		data->ray->r_x = (data->ray->r_y - data->player->pos_y) / tanf(data->ray->angle) + data->player->pos_x;
		data->ray->o_y = 64;
		data->ray->o_x = -data->ray->o_y / tanf(data->ray->angle);
	}
	else
	{
		data->ray->r_x = data->player->pos_x;
		data->ray->r_y = data->player->pos_y;
		return (0);
	}
	while (1)
	{
		map_x = (int)(data->ray->r_x / 64);
		map_y = (int)(data->ray->r_y / 64);
		if (map_y >= 0 && map_y < data->map->height && map_x >= 0 && map_x < data->map->len)
		{
			if (data->map->con[map_y][map_x] == '1')
			{
				dist = sqrtf(powf((data->ray->r_x - data->player->pos_x), 2) +
							powf((data->ray->r_y - data->player->pos_y), 2));
				break;
			}
		}
		else
			break;
		data->ray->r_x += data->ray->o_x;
		data->ray->r_y += data->ray->o_y;
	}
	return (dist);
}

