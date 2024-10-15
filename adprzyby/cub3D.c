/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adprzyby <adprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:53:39 by adprzyby          #+#    #+#             */
/*   Updated: 2024/10/10 14:13:15 by adprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char *argv[])
{
	t_game	*game;

	errno = 0;
	game = (t_game *)malloc(sizeof (t_game));
	init(game);
	check_input(game, argc, argv);
	parser(game, argv);
	spawn_player(game);
	mlx_loop_hook(game->mlx, &key_binds, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_up(game);
	return (0);
}
