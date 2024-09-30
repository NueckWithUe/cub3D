/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:30 by nnagel            #+#    #+#             */
/*   Updated: 2024/09/30 13:12:31 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	get_height(char **argv)
{
	int	fd;
	int	height;

	fd = open(argv[1], O_RDONLY);
	height = 0;
	while (get_next_line(fd))
		height++;
	close(fd);
	return (height);
}

char	**get_map(char **argv)
{
	char	**map;
	int		fd;
	int		height;
	int		y;

	y = 0;
	height = get_height(argv);
	map = malloc(sizeof(char *) * height + 1);
	fd = open(argv[1], O_RDONLY);
	while (y <= height)
	{
		map[y] = get_next_line(fd);
		y++;
	}
	close(fd);
	return (map);
}
