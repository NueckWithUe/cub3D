/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:18:19 by ajehle            #+#    #+#             */
/*   Updated: 2024/09/24 15:53:08 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	i_like_to_move_it_move_it(t_game *game, int new_x, int new_y)
{
	float	minimap_x;
	float	minimap_y;

	game->player->x = new_x;
	game->player->y = new_y;
	if (game->minimap && game->minimap->player
		&& game->minimap->player->instances)
	{
		minimap_x = (new_x * (MCELL / (float)CELL));
		minimap_y = (new_y * (MCELL / (float)CELL));
		game->minimap->player->instances[0].x = minimap_x - (PLAYER_SIZE / 2);
		game->minimap->player->instances[0].y = minimap_y - (PLAYER_SIZE / 2);
	}
}

int	check_move_up(t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player->x;
	new_y = game->player->y - PLYR_STEP;
	if (!check_collision(game, new_x, new_y))
		i_like_to_move_it_move_it(game, new_x, new_y);
	return (1);
}

int	check_move_down(t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player->x;
	new_y = game->player->y + PLYR_STEP;
	if (!check_collision(game, new_x, new_y))
		i_like_to_move_it_move_it(game, new_x, new_y);
	return (1);
}

int	check_move_left(t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player->x - PLYR_STEP;
	new_y = game->player->y;
	if (!check_collision(game, new_x, new_y))
		i_like_to_move_it_move_it(game, new_x, new_y);
	return (1);
}

int	check_move_right(t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player->x + PLYR_STEP;
	new_y = game->player->y;
	if (!check_collision(game, new_x, new_y))
		i_like_to_move_it_move_it(game, new_x, new_y);
	return (1);
}
