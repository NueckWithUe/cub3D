/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 08:55:27 by nnagel            #+#    #+#             */
/*   Updated: 2024/11/29 10:12:27 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	check_newline(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == '\n')
		{
			return (0);
		}
		i++;
	}
	return (1);
}
