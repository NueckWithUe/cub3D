/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:42 by nnagel            #+#    #+#             */
/*   Updated: 2024/10/14 18:24:49 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	raycaster(void *param)
{
	t_data	*d = (t_data *)param;
	int		n;

	d->ray->angle = d->player->angle;
	n = 0;
	while (n < FOV)
	{
		// claculate distance with horizontal lines
		// calculate distance with vertical lines
		// get the shortest distance
		// convert casted ray into 3D line
		n++;
	}
}
