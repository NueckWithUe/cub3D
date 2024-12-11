/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:29:54 by nnagel            #+#    #+#             */
/*   Updated: 2024/12/11 14:20:07 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	*ft_free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	*sanitize_line(char *line)
{
	char	*back;

	if (!line)
		return (NULL);
	back = line;
	while (*line == ' ')
		line++;
	if (*line == '1' || *line == '0')
		return (back);
	return (line);
}

static int	check_player(char **m)
{
	int	x;
	int	y;

	y = 0;
	while (m[y])
	{
		x = 0;
		while (m[y][x])
		{
			if (m[y][x] == 'N' || m[y][x] == 'S'
				|| m[y][x] == 'E' || m[y][x] == 'W')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

static int	check_invalid(char **m)
{
	int	x;
	int	y;

	y = 0;
	while (m[y])
	{
		x = 0;
		while (m[y][x])
		{
			if (m[y][x] != 'N' && m[y][x] != 'S'
				&& m[y][x] != 'E' && m[y][x] != 'W'
				&& m[y][x] != '0' && m[y][x] != '1'
				&& m[y][x] != ' ' && m[y][x] != '\n')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(char **m)
{
	if (!check_player(m))
		return (ft_print_error("No player found"));
	if (!check_invalid(m))
		return (ft_print_error("Invalid character detected"));
	if (!check_newline(m))
		return (ft_print_error("Newline in map"));
	return (1);
}
