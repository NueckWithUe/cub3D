/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:04:42 by sgeiger           #+#    #+#             */
/*   Updated: 2024/09/27 00:42:55 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*load_map(t_game *game, char *line)
{
	static char	*buf = NULL;
	char		*temp;

	if (!buf)
	{
		buf = (char *)malloc(sizeof(char));
		if (!buf)
			terminate(game);
		buf[0] = '\0';
	}
	temp = ft_strjoin(buf, line);
	if (!temp)
		terminate(game);
	free(line);
	free(buf);
	buf = temp;
	return (buf);
}

void	set_map_values(t_map *map)
{
	int	height;
	int	width;
	int	len;

	height = 0;
	width = 0;
	len = 0;
	while (map->map[height])
	{
		len = (int)ft_strlen(map->map[height]);
		if (len > width)
			width = len;
		height++;
	}
	map->map_height = height;
	map->map_width = width;
}

char	*create_filled_string(char *line, size_t width, size_t len)
{
	char	*temp;

	temp = (char *)malloc(sizeof(char) * width + 1);
	ft_strlcpy(temp, line, len + 1);
	while (len < width)
	{
		temp[len] = '0';
		len++;
	}
	temp[len] = '\0';
	return (temp);
}

void	fill_map(t_game *game, char **map)
{
	char	*temp;
	size_t	width;
	size_t	len;
	int		i;

	width = game->map->map_width;
	len = 0;
	i = 0;
	ft_replace_char(game->map->map, ' ', '0');
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len < width)
		{
			temp = create_filled_string(map[i], width, len);
			free(map[i]);
			map[i] = temp;
		}
		i++;
	}
}

void	create_map(t_game *game, char *buf)
{
	game->map->map = ft_split(buf, '\n');
	free(buf);
	set_map_values(game->map);
	fill_map(game, game->map->map);
	check_mapchars(game, game->map->map);
	game->map->ff_map = copy_map(game->map->map);
	if (game->map->start_pos.x == -1 && game->map->start_pos.y == -1)
	{
		game->my_error = "Map does not contain N, S, W or E";
		terminate(game);
	}
	flood_fill(game, game->map->start_pos.x, game->map->start_pos.y);
}
