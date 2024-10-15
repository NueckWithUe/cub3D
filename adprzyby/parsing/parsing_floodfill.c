/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_floodfill.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:40:49 by sgeiger           #+#    #+#             */
/*   Updated: 2024/09/27 00:50:23 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	**copy_map(char **map)
{
	char	**new_map;
	int		i;

	i = 0;
	while (map[i])
		i++;
	new_map = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (map[i])
	{
		new_map[i] = ft_strdup(map[i]);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

void	flood_fill(t_game *game, int x, int y)
{
	if (y < 0 || !game->map->ff_map[y] || x < 0 || !game->map->ff_map[y][x])
	{
		game->my_error = "Map is not surrounded by walls";
		terminate(game);
	}
	if (game->map->ff_map[y][x] == '1' || game->map->ff_map[y][x] == 'X')
		return ;
	else if (game->map->ff_map[y][x] == '0'
		|| is_player_char(game->map->ff_map[y][x]))
	{
		game->map->ff_map[y][x] = 'X';
	}
	flood_fill(game, x + 1, y);
	flood_fill(game, x - 1, y);
	flood_fill(game, x, y + 1);
	flood_fill(game, x, y - 1);
}
