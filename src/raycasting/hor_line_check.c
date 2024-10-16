/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hor_line_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:27:09 by nnagel            #+#    #+#             */
/*   Updated: 2024/10/16 18:59:19 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

float	horizontal_line_check(t_data *data)
{
	float	dist;

	dist = 0;
	if (data->ray->angle < M_PI)
	{
		data->ray->r_y = ((int)(data->player->pos_y / 64) * 64) - 0.0001;
		data->ray->r_x = (data->ray->r_y - data->player->pos_y) * atanf(data->ray->angle) + data->player->pos_x;
		data->ray->o_y -= 64;
		data->ray->o_x = -data->ray->o_y * atanf(data->ray->angle);
	}
	else if (data->ray->angle > M_PI)
	{
		data->ray->r_y = ((int)(data->player->pos_y / 64) * 64) + 64;
		data->ray->r_x = (data->ray->r_y - data->player->pos_y) * atanf(data->ray->angle) + data->player->pos_x;
		data->ray->o_y = 64;
		data->ray->o_x = -data->ray->o_y * atanf(data->ray->angle);
	}
	else if (data->ray->angle == 0 || data->ray->angle == M_PI)
	{
		data->ray->r_x = data->player->pos_x;
		data->ray->r_y = data->player->pos_y;
	}
	return (dist);
}
