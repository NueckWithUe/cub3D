/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:30 by nnagel            #+#    #+#             */
/*   Updated: 2024/09/30 14:07:16 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	get_height(char **argv)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		height++;
		if (line[0] == '\n' || line[0] == 'N' || line[0] == 'S' || line[0] == 'E' || line[0] == 'W' || line[0] == 'F' || line[0] == 'C')
			height--;
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

char	**get_map(char **argv)
{
	char	**map;
	char	*line;
	int		fd;
	int		height;
	int		y;

	y = 0;
	height = get_height(argv);
	map = malloc(sizeof(char *) * height + 1);
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line[0] == '\n' || line[0] == 'N' || line[0] == 'S' || line[0] == 'E' || line[0] == 'W' || line[0] == 'F' || line[0] == 'C')
	{

		line = get_next_line(fd);
	}
	while (y <= height)
	{
		map[y] = get_next_line(fd);
		y++;
	}
	close(fd);
	return (map);
}
