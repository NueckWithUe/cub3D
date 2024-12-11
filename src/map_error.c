/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 08:55:27 by nnagel            #+#    #+#             */
/*   Updated: 2024/12/11 14:40:47 by nnagel           ###   ########.fr       */
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

void	check_map(int height)
{
	if (height == 0)
	{
		ft_print_error("No map");
		exit(1);
	}
	else if (height == 2)
	{
		ft_print_error("Map too small");
		exit(1);
	}
}

void	check_path(t_data *data, char *line, char *path)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
		data->tnorth = mlx_load_png(path);
		if (!data->tnorth)
			exit(1);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		data->tsouth = mlx_load_png(path);
		if (!data->tsouth)
			exit(1);
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		data->teast = mlx_load_png(path);
		if (!data->teast)
			exit(1);
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		data->twest = mlx_load_png(path);
		if (!data->twest)
			exit(1);
	}
}
