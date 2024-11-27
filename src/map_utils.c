/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:29:54 by nnagel            #+#    #+#             */
/*   Updated: 2024/11/27 13:31:24 by nnagel           ###   ########.fr       */
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
	char	*sanitized;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (line);
	sanitized = malloc(sizeof(char) * ft_strlen(line) + 1);
	while (line[i])
	{
		sanitized[j] = line[i];
		i++;
		j++;
	}
	free(line);
	sanitized[j] = '\0';
	return (sanitized);
}

int	validate_map(char **m)
{
	int	x;
	int	y;
	int	p_found;

	y = 0;
	p_found = 0;
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
