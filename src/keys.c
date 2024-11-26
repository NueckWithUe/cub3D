/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:19 by nnagel            #+#    #+#             */
/*   Updated: 2024/11/26 15:38:28 by nnagel           ###   ########.fr       */
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

static void	w_and_a(t_player *p, mlx_t *mlx, char **m)
{
	int	npx;
	int	npy;

	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		npx = p->pos_x + cos(p->angle) * 5;
		npy = p->pos_y + sin(p->angle) * 5;
		if (m[npy/64][npx/64] != '1')
		{
			p->pos_x = npx;
			p->pos_y = npy;
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		npx = p->pos_x - cos(p->angle + (M_PI / 2)) * 5;
		npy = p->pos_y - sin(p->angle + (M_PI / 2)) * 5;
		if (m[npy/64][npx/64] != '1')
		{
			p->pos_x = npx;
			p->pos_y = npy;
		}
	}
}

static void	move(t_player *p, mlx_t *mlx, char **m)
{
	int	npx;
	int	npy;

	w_and_a(p, mlx, m);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		npx = p->pos_x - cos(p->angle) * 5;
		npy = p->pos_y - sin(p->angle) * 5;
		if (m[npy/64][npx/64] != '1')
		{
			p->pos_x = npx;
			p->pos_y = npy;
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		npx = p->pos_x - cos(p->angle - (M_PI / 2)) * 5;
		npy = p->pos_y - sin(p->angle - (M_PI / 2)) * 5;
		if (m[npy/64][npx/64] != '1')
		{
			p->pos_x = npx;
			p->pos_y = npy;
		}
	}
}

void	ft_keypress(void *param)
{
	t_data	*d;

	d = (t_data *)param;
	raycaster(d);
	if (mlx_is_key_down(d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(d->mlx);
	if (mlx_is_key_down(d->mlx, 87) || mlx_is_key_down(d->mlx, 65)
		|| mlx_is_key_down(d->mlx, 83) || mlx_is_key_down(d->mlx, 68))
		move(d->player, d->mlx, d->map->con);
	if (mlx_is_key_down(d->mlx, 263) || mlx_is_key_down(d->mlx, 262))
		rotate(d->player, d->mlx);
}
