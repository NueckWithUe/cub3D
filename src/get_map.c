/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:30 by nnagel            #+#    #+#             */
/*   Updated: 2024/11/29 11:21:09 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static char	*get_path(char *line)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	path = malloc(sizeof(char) * ft_strlen(line) + 1);
	while (line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			path[j] = '\0';
			break ;
		}
		path[j] = line[i];
		i++;
		j++;
	}
	return (path);
}

static uint32_t	set_color(char *path)
{
	char		**split;
	uint32_t	color;
	int			i;

	i = 0;
	color = 0;
	split = ft_split(path, ',');
	while (split[i])
	{
		color += ft_atoi(split[i]);
		color = color << 8;
		i++;
	}
	color += 255;
	ft_free_array(split);
	return (color);
}

static t_data	*get_conf(char *line, t_data *data)
{
	char	*path;

	if (line[0] == '\n')
	{
		free(line);
		return (data);
	}
	path = get_path(line);
	if (!ft_strncmp(line, "NO ", 3))
		data->tnorth = mlx_load_png(path);
	else if (!ft_strncmp(line, "SO ", 3))
		data->tsouth = mlx_load_png(path);
	else if (!ft_strncmp(line, "EA ", 3))
		data->teast = mlx_load_png(path);
	else if (!ft_strncmp(line, "WE ", 3))
		data->twest = mlx_load_png(path);
	else if (!ft_strncmp(line, "C ", 2))
		data->color_top = set_color(path);
	else if (!ft_strncmp(line, "F ", 2))
		data->color_floor = set_color(path);
	free(path);
	free(line);
	if (!data->tnorth || !data->tsouth || !data->teast || !data->twest)
		exit(1);
	return (data);
}

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
		if (line[0] == '\n' || line[0] == 'N' || line[0] == 'S'
			|| line[0] == 'E' || line[0] == 'W'
			|| line[0] == 'F' || line[0] == 'C')
			height--;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (height);
}

t_map	*get_map(char **argv, t_data *data)
{
	t_map	*m;
	char	*line;
	int		fd;
	int		y;

	m = malloc(sizeof(t_map));
	y = 0;
	m->height = get_height(argv);
	m->con = ft_calloc(m->height + 1, sizeof(char *));
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	line = sanitize_line(line);
	while (line[0] == '\n' || line[0] == 'N' || line[0] == 'S'
		|| line[0] == 'E' || line[0] == 'W' || line[0] == 'F' || line[0] == 67)
	{
		data = get_conf(line, data);
		line = get_next_line(fd);
		line = sanitize_line(line);
	}
	m->con[y++] = line;
	while (y < m->height)
		m->con[y++] = get_next_line(fd);
	close(fd);
	return (m);
}
