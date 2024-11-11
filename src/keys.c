/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:19 by nnagel            #+#    #+#             */
/*   Updated: 2024/11/11 12:39:31 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	rotate(t_player *p, mlx_t *mlx)
{
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		p->angle -= 0.1;
		if (p->angle < 0)
			p->angle += 2 * M_PI;
		p->d_x = cos(p->angle) * 5;
		p->d_y = sin(p->angle) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		p->angle += 0.1;
		if (p->angle > 2 * M_PI)
			p->angle -= 2 * M_PI;
		p->d_x = cos(p->angle) * 5;
		p->d_y = sin(p->angle) * 5;
	}
}

static void	move(t_player *p, mlx_t *mlx)
{
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		p->pos_x += cos(p->angle) * 5;
		p->pos_y += sin(p->angle) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		p->pos_x -= cos(p->angle + (M_PI / 2)) * 5;
		p->pos_y -= sin(p->angle + (M_PI / 2)) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		p->pos_x -= cos(p->angle) * 5;
		p->pos_y -= sin(p->angle) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		p->pos_x -= cos(p->angle - (M_PI / 2)) * 5;
		p->pos_y -= sin(p->angle - (M_PI / 2)) * 5;
	}
}

void	ft_keypress(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) || mlx_is_key_down(data->mlx, MLX_KEY_A) || mlx_is_key_down(data->mlx, MLX_KEY_S) || mlx_is_key_down(data->mlx, MLX_KEY_D))
		move(data->player, data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT) || mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate(data->player, data->mlx);
}
