/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:37:43 by nnagel            #+#    #+#             */
/*   Updated: 2024/10/30 17:28:25 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// void draw_ray(t_data *data, float hit_x)
// {
// 	float	step_x, step_y;

// 	step_x = cosf(data->ray->angle);
// 	step_y = sinf(data->ray->angle);

// 	data->ray->r_x = data->player->pos_x;
// 	data->ray->r_y = data->player->pos_y;

// 	for (int i = 0; i < hit_x; i++)
// 	{
// 		if (data->ray->r_x >= 0 && data->ray->r_x < WIDTH && data->ray->r_y >= 0 && data->ray->r_y < HEIGHT)
// 		{
// 			mlx_put_pixel(data->ibuffer, (uint32_t)data->ray->r_x, (uint32_t)data->ray->r_y, 0x00FF00FF);
// 		}
// 		data->ray->r_x += step_x;
// 		data->ray->r_y += step_y;
// 	}
// }

// void	put_block(t_data *d, int i, int j)
// {
// 	//printf("put block\n");
// 	int		i_end;
// 	int		j_end;
// 	int		j_zero;

// 	j_zero = j;
// 	i_end = i + 64;
// 	j_end = j + 64;
// 	//printf("i_start: %d, i_end: %d, j_start: %d, j_end: %d, j_zero: %d\n", i, i_end, j, j_end, j_zero);
// 	while (i < i_end)
// 	{
// 		while (j < j_end)
// 		{
// 			//printf("coordinates to put pixel: [%d][%d]\n", i, j);
// 			mlx_put_pixel(d->ibuffer, i, j, 0xFF00FFFF);
// 			j++;
// 		}
// 		j = j_zero;
// 		i++;
// 	}

// }

// void draw_vert (t_data *d)
// {
// 	//printf("draw vert\n");
// 	int		i;
// 	int		j;
// 	int		k;

// 	i = 0;
// 	k = 0;
// 	j = 1;
// 	while (k < d->map->len)
// 	{
// 		while (i < 64 * (d->map->height))
// 		{
// 			mlx_put_pixel(d->ibuffer, 64*j, i, 0xFF00FFFF);
// 			i++;
// 		}
// 		i = 0;
// 		j++;
// 		k++;
// 	}
// }

// void draw_horiz (t_data *d)
// {
// 	//printf("draw horiz\n");
// 	int		i;
// 	int		j;
// 	int		k;

// 	i = 0;
// 	k = 0;
// 	j = 1;
// 	while (k < d->map->height)
// 	{
// 		while (i < 64 * (d->map->len))
// 		{
// 			mlx_put_pixel(d->ibuffer, i, 64 * j, 0xFF00FFFF);
// 			i++;
// 		}
// 		i = 0;
// 		j++;
// 		k++;
// 	}
// }

// void	draw_minimap(t_data *d)
// {
// 	// printf("draw walls\n");
// 	int	x;
// 	int	y;

// 	x = -1;
// 	while (d->map->con[++x])
// 	{
// 		y = -1;
// 		while (d->map->con[x][++y])
// 		{
// 			if (d->map->con[x][y] == '1')
// 				put_block(d, y * 64, x * 64);
// 		}
// 	}
// }

// void draw_player (t_data *d)
// {
// 	//printf("draw player\n");
// 	mlx_put_pixel(d->ibuffer, d->player->pos_x, d->player->pos_y, 0x00FF00FF);
// 	mlx_put_pixel(d->ibuffer, d->player->pos_x + 1, d->player->pos_y, 0x00FF00FF);
// 	mlx_put_pixel(d->ibuffer, d->player->pos_x + 2, d->player->pos_y, 0x00FF00FF);
// 	mlx_put_pixel(d->ibuffer, d->player->pos_x - 1, d->player->pos_y, 0x00FF00FF);
// 	mlx_put_pixel(d->ibuffer, d->player->pos_x - 2, d->player->pos_y, 0x00FF00FF);
// 	mlx_put_pixel(d->ibuffer, d->player->pos_x, d->player->pos_y + 1, 0x00FF00FF);
// 	mlx_put_pixel(d->ibuffer, d->player->pos_x, d->player->pos_y - 1, 0x00FF00FF);
// 	mlx_put_pixel(d->ibuffer, d->player->pos_x, d->player->pos_y + 2, 0x00FF00FF);
// 	mlx_put_pixel(d->ibuffer, d->player->pos_x, d->player->pos_y - 2, 0x00FF00FF);
// }

static void	draw_3D(t_data *d, float dist, int n)
{
	int	x, end_x, y, end_y, top_color_start, floor_color_start;
	x = n * (WIDTH / FOV);
	end_x = x + (WIDTH / FOV);
	end_y = ((CUB_SIZ * HEIGHT) / dist) + (HEIGHT / 2);
	if (end_y > HEIGHT)
		end_y = HEIGHT;
	while (x < end_x)
	{
		top_color_start = 0;
		floor_color_start = end_y;
		y = (HEIGHT / 2);
		while (top_color_start < y)
			mlx_put_pixel(d->ibuffer, x, top_color_start++, d->color_top);
		while (y < end_y)
			mlx_put_pixel(d->ibuffer, x, y++, 0xFFFFFFFF);
		while (floor_color_start < HEIGHT)
			mlx_put_pixel(d->ibuffer, x, floor_color_start++, d->color_floor);
		x++;
	}
}

void	convert_ray(t_data *d, int hit_x, int hit_y, int n)
{
	float	dist;
	float	ff;

	dist = sqrtf(powf(d->player->pos_x - hit_x, 2) + powf(d->player->pos_y - hit_y, 2));
	ff = d->player->angle - d->ray->angle;
	if (ff < 0)
		ff += 2 * M_PI;
	if (ff > 2 * M_PI)
		ff -= 2 * M_PI;
	dist *= cosf(ff);
	draw_3D(d, dist, n);
}

	// draw_minimap(d);
	// draw_horiz(d);
	// draw_vert(d);
	// draw_player(d);
	// draw_ray(d, dist);