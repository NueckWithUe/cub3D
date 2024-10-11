/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:19 by nnagel            #+#    #+#             */
/*   Updated: 2024/09/30 13:19:03 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	rotate(mlx_key_data_t keydata, t_player *p)
{
	if ((keydata.key == MLX_KEY_Q
			|| keydata.key == MLX_KEY_LEFT) && keydata.action == 2)
	{
		write(1, "View rotate left\n", 17);
		p->angle -= 0.1;
		if (p->angle < 0)
			p->angle += 2 * M_PI;
		p->d_x = cos(p->angle) * 5;
		p->d_y = sin(p->angle) * 5;
	}
	if ((keydata.key == MLX_KEY_E
			|| keydata.key == MLX_KEY_RIGHT) && keydata.action == 2)
	{
		write(1, "View rotate right\n", 18);
		p->angle += 0.1;
		if (p->angle > 2 * M_PI)
			p->angle -= 2 * M_PI;
		p->d_x = cos(p->angle) * 5;
		p->d_y = sin(p->angle) * 5;
	}
}

static void	move(mlx_key_data_t keydata, t_player *p)
{
	if (keydata.key == MLX_KEY_W && keydata.action == 2)
	{
		write(1, "Move forward\n", 13);
		p->pos_x += p->d_x;
		p->pos_y += p->d_y;
	}
	if (keydata.key == MLX_KEY_A && keydata.action == 2)
	{
		write(1, "Move left\n", 10);
		p->pos_x -= 5;
	}
	if (keydata.key == MLX_KEY_S && keydata.action == 2)
	{
		write(1, "Move backwards\n", 15);
		p->pos_x -= p->d_x;
		p->pos_y -= p->d_y;
	}
	if (keydata.key == MLX_KEY_D && keydata.action == 2)
	{
		write(1, "Move right\n", 11);
		p->pos_x += 5;
	}
}

void	ft_keypress(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == 1)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_W && keydata.action == 2)
		move(keydata, data->player);
	if (keydata.key == MLX_KEY_A && keydata.action == 2)
		move(keydata, data->player);
	if (keydata.key == MLX_KEY_S && keydata.action == 2)
		move(keydata, data->player);
	if (keydata.key == MLX_KEY_D && keydata.action == 2)
		move(keydata, data->player);
	if ((keydata.key == MLX_KEY_Q
			|| keydata.key == MLX_KEY_LEFT) && keydata.action == 2)
		rotate(keydata, data->player);
	if ((keydata.key == MLX_KEY_E
			|| keydata.key == MLX_KEY_RIGHT) && keydata.action == 2)
		rotate(keydata, data->player);
}
