/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:37:43 by nnagel            #+#    #+#             */
/*   Updated: 2024/11/22 13:01:44 by nnagel           ###   ########.fr       */
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

static uint32_t put_color(t_data *d, int y, int height)
{
	mlx_texture_t	*tmp;
	int				x_tex = 20;
	int				y_tex;
	uint32_t		*tex_color;
	uint32_t		new_color;

	y_tex = (((y * 256 - HEIGHT * 128 + height * 128) * TEX_HEIGHT) / height) / 256;
	if (d->ray->v_hit)
	{
		if (d->ray->angle > M_PI_2 && d->ray->angle < 3 * M_PI_2)
			tmp = d->twest;
		else
			tmp = d->teast;
	}
	else
	{
		if (d->ray->angle < M_PI)
			tmp = d->tsouth;
		else
			tmp = d->tnorth;
	}
	tex_color = (uint32_t *)(tmp->pixels + (y_tex * TEX_WIDTH + x_tex) * sizeof(uint32_t));
	new_color = ((*tex_color & 0xFF000000) >> 24) | ((*tex_color & 0x00FF0000) >> 8) | ((*tex_color & 0x0000FF00) << 8) | ((*tex_color & 0x000000FF) << 24);
	return (new_color);
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
	if (n == FOV - 1)
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
		{
			mlx_put_pixel(d->ibuffer, x, y, put_color(d, y, line_height));
			y++;
		}
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
