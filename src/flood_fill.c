/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:03:02 by nnagel            #+#    #+#             */
/*   Updated: 2024/12/11 14:37:07 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	find_proportions(t_data *d)
{
	int	this_line_len;
	int	i;

	d->map_width = 0;
	this_line_len = 0;
	i = 0;
	while (d->map->con[i])
	{
		this_line_len = ft_strlen(d->map->con[i]);
		if (this_line_len > d->map_width)
			d->map_width = this_line_len;
		i++;
	}
	d->map_height = i;
}

void	flood_fill(t_data *d, int x, int y, char **map_copy)
{
	if (x < 0 || x >= d->map_height || y < 0
		|| y >= (int)ft_strlen(map_copy[x]))
	{
		ft_print_error("Player isn't locked inside the map");
		exit(1);
	}
	else if (map_copy[x][y] == '1' || map_copy[x][y] == '*')
		return ;
	map_copy[x][y] = '*';
	flood_fill(d, x - 1, y, map_copy);
	flood_fill(d, x + 1, y, map_copy);
	flood_fill(d, x, y - 1, map_copy);
	flood_fill(d, x, y + 1, map_copy);
}

char	**map_copy_it(t_data *d)
{
	char	**copy;
	int		i;

	copy = malloc((d->map_height + 1) * sizeof(char *));
	i = 0;
	while (i < d->map_height)
	{
		copy[i] = ft_strdup(d->map->con[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	ff_go(t_data *data)
{
	char	**map_copy;

	find_proportions(data);
	map_copy = map_copy_it(data);
	flood_fill(data, data->player_x, data->player_y, map_copy);
	ft_free_array(map_copy);
}
