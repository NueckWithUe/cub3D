/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:42:40 by sgeiger           #+#    #+#             */
/*   Updated: 2024/09/27 00:44:42 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_mapchars(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1'
				&& !is_player_char(map[i][j]))
			{
				game->my_error = "Map has undefined chars";
				terminate(game);
			}
			if (is_player_char(map[i][j]))
				set_start_pos(game, game->map, i, j);
			j++;
		}
		i++;
	}
}

char	*skip_empty_lines(int fd)
{
	char		*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_empty_line(line))
		{
			free(line);
			continue ;
		}
		else
			return (line);
	}
	return (NULL);
}

char	*check_map(t_game *game, char *line, int fd)
{
	char	*buf;

	buf = NULL;
	while (line)
	{
		if (is_map(game, line))
			buf = load_map(game, line);
		else if (is_empty_line(line))
		{
			if (buf)
				create_map(game, buf);
			return (line);
		}
		else
		{
			game->my_error = "Invalid file content";
			free(line);
			free(buf);
			terminate(game);
		}
		line = get_next_line(fd);
	}
	create_map(game, buf);
	return (NULL);
}

void	check_end(t_game *game, char *line, int fd)
{
	while (line)
	{
		if (is_empty_line(line))
			free(line);
		else
		{
			game->my_error = "Invalid file content";
			free(line);
			terminate(game);
		}
		line = get_next_line(fd);
	}
}

void	check_map_part(t_game *game, int fd)
{
	char	*line;

	line = skip_empty_lines(fd);
	if (line)
	{
		line = check_map(game, line, fd);
		if (line)
			check_end(game, line, fd);
	}
}
