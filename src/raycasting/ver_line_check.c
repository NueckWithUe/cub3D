/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ver_line_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:29:41 by nnagel            #+#    #+#             */
/*   Updated: 2024/10/16 19:10:39 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

float	vertical_line_check(t_data *data)
{
	float	dist;

	dist = 0;
	if (data->ray->angle < 3 * (M_PI / 2) && data->ray->angle > (M_PI / 2))
	{
		data->ray->r_x = ((int)(data->player->pos_x / 64) * 64) - 0.0001;
		data->ray->r_y = (data->ray->r_x - data->player->pos_x) * (tan(data->ray->angle) * -1) + data->player->pos_y;
		data->ray->o_x -= 64;
		data->ray->o_y = -data->ray->o_x * (tan(data->ray->angle) * -1);
	}
	else if (data->ray->angle < (M_PI / 2) || data->ray->angle > 3 * (M_PI / 2))
	{
		data->ray->r_x = ((int)(data->player->pos_x / 64) * 64) + 64;
		data->ray->r_y = (data->ray->r_x - data->player->pos_x) * (tan(data->ray->angle) * -1) + data->player->pos_y;
		data->ray->o_x = 64;
		data->ray->o_y = -data->ray->o_x * (tan(data->ray->angle) * -1);
	}
	else if (data->ray->angle == 0 || data->ray->angle == M_PI)
	{
		data->ray->r_x = data->player->pos_y;
		data->ray->r_y = data->player->pos_x;
	}
	return (dist);
}
