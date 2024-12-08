/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:10 by nnagel            #+#    #+#             */
/*   Updated: 2024/12/08 16:04:28 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static float	get_ang(char direction)
{
	if (direction == 'N')
		return ((3 * M_PI) / 2);
	if (direction == 'S')
		return (M_PI / 2);
	if (direction == 'E')
		return (0);
	if (direction == 'W')
		return (M_PI);
	return (42);
}

static t_player	*get_pos(t_data *data)
{
	int		x;
	int		y;
	char	curr;

	x = 0;
	y = 0;
	while (data->map->con[y][x])
	{
		curr = data->map->con[y][x];
		if ((curr == 'N') || (curr == 'S') || (curr == 'E') || (curr == 'W'))
		{
			data->player->pos_x = (x * CUB_SIZ) + (CUB_SIZ / 2);
			data->player->pos_y = (y * CUB_SIZ) + (CUB_SIZ / 2);
			data->player->angle = get_ang(curr);
			data->player_x = y;
			data->player_y = x;
		}
		x++;
		if (data->map->con[y][x] == '\n')
		{
			y++;
			x = 0;
		}
	}
	return (data->player);
}


// char	**map_copy_it(t_data *d)
// {
// 	char	**copy;
// 	int		i;

// 	copy = ft_malloc((mlx->parse->cols + 1)*sizeof(char *));
// 	i = 0;
// 	while (i < mlx->parse->cols)
// 	{
// 		copy[i] = ft_strdup(mlx->parse->map[i]);
// 		i++;
// 	}
// 	copy[i] = NULL;
// 	return (copy);
// }

// size_t	ft_strlen1(char *s)
// {
// 	size_t	c;

// 	c = 0;
// 	while (s[c] != '\0')
// 		c++;
// 	return (c);
// }

void find_proportions(t_data *d)
{
	int this_line_len;
	int i;

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
	if (x < 0 || x >= d->map_height || y < 0\
		|| y >= (int)ft_strlen(map_copy[x]))
		printf("Error: player isn't locked inside the map\n"); //should be clean exit
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

void ff_go(t_data *data)
{
	char	**map_copy;

	find_proportions(data);
	map_copy = map_copy_it(data);
	flood_fill(data, data->player_x, data->player_y, map_copy);
	ft_free_array(map_copy);
}

// void leaks()
// {
// 	system("leaks cub3D");
// }

int	main(int argc, char **argv)
{
	// atexit(leaks);
	t_data	*data;

	if (argc != 2)
		return (ft_print_error("Too few/much arguments"), 1);
	if (!ft_error_handling(argv))
		return (1);
	data = init_data();
	if (!data)
		return (1);
	if (data->error > 0)
		return (free_data(data), 1);
	data->map = get_map(argv, data);
	if (!validate_map(data->map->con))
	{
		data = ft_free(data);
		return (1);
	}
	data->player = get_pos(data);
	ff_go(data);
	mlx_loop_hook(data->mlx, &ft_keypress, (void *)data);
	mlx_loop(data->mlx);
	data = ft_free(data);
	return (0);
}
