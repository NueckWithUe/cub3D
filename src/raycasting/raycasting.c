/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:42 by nnagel            #+#    #+#             */
/*   Updated: 2024/10/15 13:09:31 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	raycaster(void *param)
{
	t_data	*d = (t_data *)param;
	int		n;
	float	dist;
	float	tmp;

	d->ray->angle = d->player->angle;
	n = 0;
	while (n < FOV)
	{
		dist = horizontal_line_check(d);	// claculate distance with horizontal lines
		tmp = vertical_line_check(d);		// calculate distance with vertical lines
		convert_ray(d, dist, tmp);			// convert casted ray into 3D line
		n++;
	}
}
