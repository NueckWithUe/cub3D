/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ddr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:20:35 by nnagel            #+#    #+#             */
/*   Updated: 2024/12/08 16:02:02 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	get_step(float angle, int x)
{
	if (x)
	{
		if (cosf(angle) * 5 < 0)
			return (-1);
		else
			return (1);
	}
	else
	{
		if (sinf(angle) * 5 < 0)
			return (-1);
		else
			return (1);
	}
}

static float	get_side_dist(t_data *data, int x)
{
	float	side_dist;
	int		mx;
	int		my;

	mx = (int)data->player->pos_x;
	my = (int)data->player->pos_y;
	if (x)
	{
		if (cosf(data->ray->angle) * 5 < 0)
			side_dist = (data->player->pos_x - mx)
				* fabsf(1 / cosf(data->ray->angle) * 5);
		else
			side_dist = (mx + 1 - data->player->pos_x)
				* fabsf(1 / cosf(data->ray->angle) * 5);
	}
	else
	{
		if (sinf(data->ray->angle) * 5 < 0)
			side_dist = (data->player->pos_y - my)
				* fabsf(1 / sinf(data->ray->angle) * 5);
		else
			side_dist = (my + 1 - data->player->pos_y)
				* fabsf(1 / sinf(data->ray->angle) * 5);
	}
	return (side_dist);
}

static void	init_values(t_data *data, int *map_x, int *map_y, float *side_dst)
{
	*map_x = (int)data->player->pos_x;
	*map_y = (int)data->player->pos_y;
	side_dst[0] = get_side_dist(data, 1);
	side_dst[1] = get_side_dist(data, 0);
}

void	ddr(t_data *data, int *hit_x, int *hit_y)
{
	float	side_dist[2];
	int		map_x;
	int		map_y;

	init_values(data, &map_x, &map_y, side_dist);
	while (1)
	{
		if (side_dist[0] < side_dist[1])
		{
			side_dist[0] += fabsf(1 / cosf(data->ray->angle) * 5);
			map_x += get_step(data->ray->angle, 1);
			data->ray->v_hit = 1;
		}
		else
		{
			side_dist[1] += fabsf(1 / sinf(data->ray->angle) * 5);
			map_y += get_step(data->ray->angle, 0);
			data->ray->v_hit = 0;
		}
		if (data->map->con[(map_y / 64)][(map_x / 64)] == '1')
			break ;
	}
	*hit_x = map_x;
	*hit_y = map_y;
}
