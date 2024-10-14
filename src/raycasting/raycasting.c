/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:42 by nnagel            #+#    #+#             */
/*   Updated: 2024/10/14 17:44:36 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	raycaster(void *param)
{
	t_data *d = (t_data *)param;
	d->ray->angle = d->player->angle;
	int h = d->map->height;
	int i = 0;
	while (i < h)
		i++;
}
