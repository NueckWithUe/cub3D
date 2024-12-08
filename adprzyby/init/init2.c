/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adprzyby <adprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:04:42 by adprzyby          #+#    #+#             */
/*   Updated: 2024/10/15 13:58:10 by adprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_game_struct(t_game *game)
{
	game->mlx = NULL;
	game->buffer = NULL;
	game->map = NULL;
	game->view = NULL;
	game->ray = NULL;
	game->textures = NULL;
	game->my_error = NULL;
	game->mlx = mlx_init(SCREEN_W, SCREEN_H, "cub3D", false);
	if (!game->mlx)
		quit_error();
}

void	spawn_player(t_game *game)
{
	if (game->map->start_orientation == 'W'
		|| game->map->start_orientation == 'E')
		spawn_pos_w_e(game);
	else if (game->map->start_orientation == 'N'
		|| game->map->start_orientation == 'S')
		spawn_pos_n_s(game);
	game->view->pos_x = game->map->start_pos.x + 0.5;
	game->view->pos_y = game->map->start_pos.y + 0.5;
}

void	spawn_pos_w_e(t_game *game)
{
	if (game->map->start_orientation == 'E')
	{
		game->view->dir_x = 1;
		game->view->dir_y = 0;
		game->view->cam_x = 0;
		game->view->cam_y = 0.5;
	}
	else if (game->map->start_orientation == 'W')
	{
		game->view->dir_x = -1;
		game->view->dir_y = 0;
		game->view->cam_x = 0;
		game->view->cam_y = -0.5;
	}
}

void	spawn_pos_n_s(t_game *game)
{
	if (game->map->start_orientation == 'N')
	{
		game->view->dir_x = 0;
		game->view->dir_y = -1;
		game->view->cam_x = 0.5;
		game->view->cam_y = 0;
	}
	else if (game->map->start_orientation == 'S')
	{
		game->view->dir_x = 0;
		game->view->dir_y = 1;
		game->view->cam_x = -0.5;
		game->view->cam_y = 0;
	}
}
