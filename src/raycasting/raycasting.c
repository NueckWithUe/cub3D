/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:42 by nnagel            #+#    #+#             */
/*   Updated: 2024/11/21 12:27:28 by nnagel           ###   ########.fr       */
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

void	raycaster(t_data *d)
{
	// t_data	*d;
	int		n;
	int		hit_x;
	int		hit_y;

	// d = (t_data *)param;
	d->ray->angle = d->player->angle - (DR * (FOV / 2));
	d->ray->angle = check_angle(d->ray->angle);
	n = 0;
	mlx_delete_image(d->mlx, d->ibuffer);
	d->ibuffer = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	while (n < FOV)
	{
		ddr(d, &hit_x, &hit_y);
		convert_ray(d, hit_x, hit_y, n);
		n++;
		d->ray->angle += DR;
		d->ray->angle = check_angle(d->ray->angle);
	}
	mlx_image_to_window(d->mlx, d->ibuffer, 0, 0);
}
