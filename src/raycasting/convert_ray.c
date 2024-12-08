/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:37:43 by nnagel            #+#    #+#             */
/*   Updated: 2024/12/08 16:41:38 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// static uint32_t put_color(t_data *d)
// {
// 	uint32_t	north = 0xFF0000FF;
// 	uint32_t	south = 0x00FF00FF;
// 	uint32_t	east = 0x0000FFFF;
// 	uint32_t	west = 0xFFFFFFFF;

// 	if (d->ray->v_hit)
// 	{
// 		if (d->ray->angle > M_PI_2 && d->ray->angle < 3 * M_PI_2)
// 			return (west);
// 		else
// 			return (east);
// 	}
// 	else
// 	{
// 		if (d->ray->angle < M_PI)
// 			return (south);
// 		else
// 			return (north);
// 	}
// }

// static void	draw_3d(t_data *d, float dist, int n)
// {
// 	int	x;
// 	int	y;
// 	int	end_y;
// 	int	line_height;

// 	x = n;
// 	line_height = ((CUB_SIZ * HEIGHT) / dist);
// 	if (line_height > HEIGHT)
// 		line_height = HEIGHT;
// 	end_y = line_height + (HEIGHT / 2) - (line_height / 2);
// 	y = 0;
// 	while (y < (HEIGHT / 2) - (line_height / 2))
// 		mlx_put_pixel(d->ibuffer, x, y++, d->color_top);
// 	while (y < end_y)
// 	{
// 		mlx_put_pixel(d->ibuffer, x, y, put_color(d));
// 		y++;
// 	}
// 	while (y < HEIGHT)
// 		mlx_put_pixel(d->ibuffer, x, y++, d->color_floor);
// }

int tex_color(t_data *d)
{
	return ((uint32_t)d->ray->tex4ray->pixels[d->ray->pixel + 0] << 24) | // Red
		((uint32_t)d->ray->tex4ray->pixels[d->ray->pixel + 1] << 16) | // Green
		((uint32_t)d->ray->tex4ray->pixels[d->ray->pixel + 2] << 8)  | // Blue
		0x000000FF;
}

static void	draw_3d(t_data *d, float dist, int n)
{
	int	y;
	int	end_y;
	int	line_height;
	double tex_y;

	line_height = ((CUB_SIZ * HEIGHT) / dist);
	end_y = line_height + (HEIGHT / 2) - (line_height / 2);
	y = 0;
	while (y < (HEIGHT / 2) - (line_height / 2))
		mlx_put_pixel(d->ibuffer, n, y++, d->color_top);
	d->ray->proportion = (double)d->ray->tex4ray->height / line_height;
	while (y < end_y)
	{
		tex_y = (((y * 256 - HEIGHT * 128 + line_height * 128)
						* TEX_HEIGHT) / line_height) / 256;
		d->ray->pixel = ((int) tex_y * d->ray->tex4ray->width + d->ray->texture_column) * 4;
		mlx_put_pixel(d->ibuffer, n, y, tex_color(d));
		tex_y += d->ray->proportion;
		y++;
		if (y == HEIGHT)
			break ;
	}
	while (y < HEIGHT)
		mlx_put_pixel(d->ibuffer, n, y++, d->color_floor);
}

void tex_choose(t_data *d, int hit_x, int hit_y)
{
	float	offset_portion;

	if (d->ray->v_hit == 1)
	{
		if (d->ray->angle < M_PI / 2 || d->ray->angle > 3 * M_PI_2)
			d->ray->tex4ray = d->teast;
		else
			d->ray->tex4ray = d->twest;
		offset_portion = (float)(hit_y % CUB_SIZ) / CUB_SIZ;
		d->ray->texture_column = (int) (offset_portion * d->ray->tex4ray->width);
	}
	else
	{
		if (d->ray->angle > 0 && d->ray->angle < M_PI)
			d->ray->tex4ray = d->tnorth;
		else
			d->ray->tex4ray = d->tsouth;
		offset_portion = (float)(hit_x % CUB_SIZ) / CUB_SIZ;
		d->ray->texture_column = (int) (offset_portion * d->ray->tex4ray->width);
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
	tex_choose(d, hit_x, hit_y);
	draw_3d(d, dist, n);
}
