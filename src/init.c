/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:25 by nnagel            #+#    #+#             */
/*   Updated: 2024/09/30 13:12:26 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static t_ray	*init_ray(void)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	ray->angle = 0;
	ray->o_x = 0;
	ray->o_y = 0;
	ray->r_x = 0;
	ray->r_y = 0;
	return (ray);
}

static t_player	*init_player(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	player->pos_x = 0;
	player->pos_y = 0;
	player->angle = 0;
	return (player);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->player = init_player();
	if (!data->player)
		return (NULL);
	data->ray = init_ray();
	if (!data->ray)
		return (NULL);
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 0);
	if (!data->mlx)
		return (NULL);
	return (data);
}
