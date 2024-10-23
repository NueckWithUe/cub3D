/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:42 by nnagel            #+#    #+#             */
/*   Updated: 2024/10/23 16:27:03 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static float	check_angle(float ray)
{
	if (ray < 0)
		ray += 2 * M_PI;
	if (ray > 2 * M_PI)
		ray -= 2 * M_PI;
	return (ray);
}

void	raycaster(void *param)
{
	t_data	*d;
	int		n;
	float	dist;
	float	tmp;

	d = (t_data *)param;
	d->ray->angle = d->player->angle - (DR * 30);
	d->ray->angle = check_angle(d->ray->angle);
	n = 0;
	mlx_delete_image(d->mlx, d->ibuffer);
	d->ibuffer = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	while (n < FOV)
	{
		dist = horizontal_line_check(d);	// claculate distance with horizontal lines
		tmp = vertical_line_check(d);		// calculate distance with vertical lines
		convert_ray(d, dist, tmp);			// convert casted ray into 3D line
		n++;
		d->ray->angle += DR;
		d->ray->angle = check_angle(d->ray->angle);
	}
	mlx_image_to_window(d->mlx, d->ibuffer, 0, 0);
}
