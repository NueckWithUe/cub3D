/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:36 by nnagel            #+#    #+#             */
/*   Updated: 2024/09/30 13:20:05 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_check_extension(char *s)
{
	int		i;
	int		c;
	char	s2[5];

	s2[0] = '.';
	s2[1] = '.';
	s2[2] = 'c';
	s2[3] = 'u';
	s2[4] = 'b';
	c = 4;
	i = ft_strlen(s);
	i--;
	while (c != 0)
	{
		if (s[i] != s2[c])
			return (0);
		c--;
		i--;
	}
	if (s2[0] == s[i])
		return (0);
	return (1);
}

static int	ft_check_exist(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (read(fd, 0, 0) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	ft_error_handling(char **argv)
{
	if (!ft_check_extension(argv[1]))
		return (ft_print_error("Map extension should be (.cub)"));
	if (!ft_check_exist(argv[1]))
		return (ft_print_error("File not readable or doesn't exist"));
	return (1);
}

int	ft_print_error(char *errmsg)
{
	ft_printf("Error\n%s\n", errmsg);
	return (0);
}

int	ft_check_void(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == '0'
					&& (map[y + 1][x] == '\n' || map[y][x + 1] == '\n'))
			{
				return (0);
			}
			x++;
		}
		y++;
		x = 0;
	}
	return (1);
}
