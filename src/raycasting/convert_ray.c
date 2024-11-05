/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:37:43 by nnagel            #+#    #+#             */
/*   Updated: 2024/11/05 13:04:40 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	draw_3d(t_data *d, float dist, int n)
{
	int	x;
	int	end_x;
	int	y;
	int	end_y;
	int	line_height;

	x = n * (WIDTH / FOV);
	end_x = x + (WIDTH / FOV);
	if (n == 59)
		end_x = WIDTH;
	line_height = ((CUB_SIZ * HEIGHT) / dist);
	if (line_height > HEIGHT)
		line_height = HEIGHT;
	end_y = line_height + (HEIGHT / 2) - (line_height / 2);
	while (x < end_x)
	{
		y = 0;
		while (y < (HEIGHT / 2) - (line_height / 2))
			mlx_put_pixel(d->ibuffer, x, y++, d->color_top);
		while (y < end_y)
			mlx_put_pixel(d->ibuffer, x, y++, 0xFFFFFFFF);
		while (y < HEIGHT)
			mlx_put_pixel(d->ibuffer, x, y++, d->color_floor);
		x++;
	}
}

void	convert_ray(t_data *d, int hit_x, int hit_y, int n)
{
	float	dist;
	float	ff;

	dist = sqrtf(powf(d->player->pos_x - hit_x, 2)
			+ powf(d->player->pos_y - hit_y, 2));
	ff = d->player->angle - d->ray->angle;
	if (ff < 0)
		ff += 2 * M_PI;
	if (ff > 2 * M_PI)
		ff -= 2 * M_PI;
	dist *= cosf(ff);
	draw_3d(d, dist, n);
}
