/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:42 by nnagel            #+#    #+#             */
/*   Updated: 2024/10/16 15:13:23 by nnagel           ###   ########.fr       */
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
	mlx_delete_image(d->mlx, d->iBuffer);
	d->iBuffer = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	while (n < FOV)
	{
		dist = horizontal_line_check(d);	// claculate distance with horizontal lines
		tmp = vertical_line_check(d);		// calculate distance with vertical lines
		convert_ray(d, dist, tmp);			// convert casted ray into 3D line
		n++;
	}
	mlx_image_to_window(d->mlx, d->iBuffer, 0, 0);
}
