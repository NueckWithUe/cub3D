/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:19 by nnagel            #+#    #+#             */
/*   Updated: 2024/10/24 10:00:07 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	rotate(mlx_key_data_t keydata, t_player *p)
{
	if ((keydata.key == MLX_KEY_LEFT) && (keydata.action == 2 || keydata.action == 1))
	{
		p->angle -= 0.1;
		if (p->angle < 0)
			p->angle += 2 * M_PI;
		p->d_x = cos(p->angle) * 5;
		p->d_y = sin(p->angle) * 5;
	}
	if ((keydata.key == MLX_KEY_RIGHT) && (keydata.action == 2 || keydata.action == 1))
	{
		p->angle += 0.1;
		if (p->angle > 2 * M_PI)
			p->angle -= 2 * M_PI;
		p->d_x = cos(p->angle) * 5;
		p->d_y = sin(p->angle) * 5;
	}
}

static void	move(mlx_key_data_t keydata, t_player *p)
{
	if (keydata.key == MLX_KEY_W && (keydata.action == 2 || keydata.action == 1))
	{
		p->pos_x += cos(p->angle) * 5;
		p->pos_y += sin(p->angle) * 5;
	}
	if (keydata.key == MLX_KEY_A && (keydata.action == 2 || keydata.action == 1))
	{
		p->pos_x -= cos(p->angle + (M_PI / 2)) * 5;
		p->pos_y -= sin(p->angle + (M_PI / 2)) * 5;
	}
	if (keydata.key == MLX_KEY_S && (keydata.action == 2 || keydata.action == 1))
	{
		p->pos_x -= cos(p->angle) * 5;
		p->pos_y -= sin(p->angle) * 5;
	}
	if (keydata.key == MLX_KEY_D && (keydata.action == 2 || keydata.action == 1))
	{
		p->pos_x -= cos(p->angle - (M_PI / 2)) * 5;
		p->pos_y -= sin(p->angle - (M_PI / 2)) * 5;
	}
}

void	ft_keypress(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == 1)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_W && (keydata.action == 2 || keydata.action == 1))
		move(keydata, data->player);
	if (keydata.key == MLX_KEY_A && (keydata.action == 2 || keydata.action == 1))
		move(keydata, data->player);
	if (keydata.key == MLX_KEY_S && (keydata.action == 2 || keydata.action == 1))
		move(keydata, data->player);
	if (keydata.key == MLX_KEY_D && (keydata.action == 2 || keydata.action == 1))
		move(keydata, data->player);
	if ((keydata.key == MLX_KEY_LEFT) && (keydata.action == 2 || keydata.action == 1))
		rotate(keydata, data->player);
	if ((keydata.key == MLX_KEY_RIGHT) && (keydata.action == 2 || keydata.action == 1))
		rotate(keydata, data->player);
}
