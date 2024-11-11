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

static uint32_t put_color(t_data *d)
{
	if (d->ray->v_hit)
	{
		if (d->ray->angle < M_PI)
		{
			if (d->ray->angle < M_PI / 2)
				return (0xFF00FF00);
			else
				return (0xFFFFFF00);
		}
		else
		{
			if (d->ray->angle > (3 * M_PI) / 2)
				return (0xFFFF00FF);
			else
				return (0xFF0000FF);
		}
	}
	else
	{
		if (d->ray->angle < M_PI)
		{
			if (d->ray->angle < M_PI / 2)
				return (0xFFF0F0F0);
			else
				return (0xFF0F0F0F);
		}
		else
		{
			if (d->ray->angle > (3 * M_PI) / 2)
				return (0xFF808080);
			else
				return (0xFF080808);
		}
	}
}

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
			mlx_put_pixel(d->ibuffer, x, y++, put_color(d));
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
