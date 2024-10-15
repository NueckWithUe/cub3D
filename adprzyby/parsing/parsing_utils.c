/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:49:37 by sgeiger           #+#    #+#             */
/*   Updated: 2024/09/26 19:24:08 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

bool	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

void	ft_replace_char(char **line, char c1, char c2)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		j = 0;
		while (line[i][j])
		{
			if (line[i][j] == c1)
				line[i][j] = c2;
			j++;
		}
		i++;
	}
}

bool	is_map(t_game *game, char *line)
{
	int	i;

	i = 0;
	(void)game;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (true);
	return (false);
}

void	set_start_pos(t_game *game, t_map *map, int i, int j)
{
	if (map->start_pos.x == -1 && map->start_pos.y == -1)
	{
		map->start_pos.x = j;
		map->start_pos.y = i;
		map->start_orientation = map->map[i][j];
	}
	else
	{
		game->my_error = "Map can only contain one N, S, E or W!";
		terminate(game);
	}
}

//   TEMP
// void	print_map(char **map)
// {
// 	int	i;

// 	i = 0;
// 	while (map[i])
// 	{
// 		if (i < 10)
// 			printf(" %d - %s\n", i, map[i]);
// 		else
// 			printf("%d - %s\n", i, map[i]);
// 		i++;
// 	}
// }

//   TEMP
// void	print_line(char *line)
// {
// 	int	i;
// 
//	i = 0;
// 	printf("len: %zu line: %s\n", ft_strlen(line), line);
// 	while (i < 37)
// 	{
// 		printf("%d: %c - %d\n", i, line[i], line[i]);
// 		// write(1,&line[i], 1);
// 		// printf("-%d\n", line[i]);
// 		i++;
// 	}
// 	write(1, "\n", 1);
// }
