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

static void	rotate(mlx_key_data_t keydata)
{
	if ((keydata.key == MLX_KEY_Q
			|| keydata.key == MLX_KEY_LEFT) && keydata.action == 2)
	{
		write(1, "View rotate left\n", 17);
	}
	if ((keydata.key == MLX_KEY_E
			|| keydata.key == MLX_KEY_RIGHT) && keydata.action == 2)
	{
		write(1, "View rotate right\n", 18);
	}
}

static void	move(mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_W && keydata.action == 2)
	{
		write(1, "Move forward\n", 13);
	}
	if (keydata.key == MLX_KEY_A && keydata.action == 2)
	{
		write(1, "Move left\n", 10);
	}
	if (keydata.key == MLX_KEY_S && keydata.action == 2)
	{
		write(1, "Move backwards\n", 15);
	}
	if (keydata.key == MLX_KEY_D && keydata.action == 2)
	{
		write(1, "Move right\n", 11);
	}
}

void	ft_keypress(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == 1)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_W && keydata.action == 2)
		move(keydata);
	if (keydata.key == MLX_KEY_A && keydata.action == 2)
		move(keydata);
	if (keydata.key == MLX_KEY_S && keydata.action == 2)
		move(keydata);
	if (keydata.key == MLX_KEY_D && keydata.action == 2)
		move(keydata);
	if ((keydata.key == MLX_KEY_Q
			|| keydata.key == MLX_KEY_LEFT) && keydata.action == 2)
		rotate(keydata);
	if ((keydata.key == MLX_KEY_E
			|| keydata.key == MLX_KEY_RIGHT) && keydata.action == 2)
		rotate(keydata);
}
