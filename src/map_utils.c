/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:29:54 by nnagel            #+#    #+#             */
/*   Updated: 2024/11/27 12:30:18 by nnagel           ###   ########.fr       */
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
