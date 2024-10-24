/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:12:30 by nnagel            #+#    #+#             */
/*   Updated: 2024/10/23 14:54:50 by nnagel           ###   ########.fr       */
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

static t_data	*get_conf(char *line, t_data *data)
{
	char	*path;

	path = get_path(line);
	if (!ft_strncmp(line, "NO ", 3))
		data->tnorth = mlx_load_png(path);
	else if (!ft_strncmp(line, "SO ", 3))
		data->tsouth = mlx_load_png(path);
	else if (!ft_strncmp(line, "EA ", 3))
		data->teast = mlx_load_png(path);
	else if (!ft_strncmp(line, "WE ", 3))
		data->twest = mlx_load_png(path);
	free(path);
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
		if (line[0] == '\n' || line[0] == 'N' || line[0] == 'S' || line[0] == 'E' || line[0] == 'W' || line[0] == 'F' || line[0] == 'C')
			height--;
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

// static char	*sanitize_line(char *line)
// {
// 	char	*sanitized;
// 	int		i;
// 	int		j;

// 	sanitized = malloc(sizeof(char) * ft_strlen(line) + 1);
// 	i = 0;
// 	j = 0;
// 	while (line[i] == ' ')
// 		i++;
// 	while (line[i] != ' ')
// 	{
// 		sanitized[j] = line[i];
// 		j++;
// 		i++;
// 	}
// 	sanitized[j] = ' ';
// 	while (line[i] == ' ')
// 		i++;
// 	while (line[i] != '\n')
// 	{
// 		sanitized[j] = line[i];
// 		i++;
// 		j++;
// 	}
// 	free(line);
// 	sanitized[j] = '\0';
// 	return (sanitized);
// }

t_map	*get_map(char **argv, t_data *data)
{
	t_map	*m;
	char	*line;
	int		fd;
	int		y;

	m = malloc(sizeof(t_map));
	y = 0;
	m->height = get_height(argv);
	m->con = malloc(sizeof(char *) * m->height + 1);
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	// line = sanitize_line(line);
	while (line[0] == '\n' || line[0] == 'N' || line[0] == 'S' || line[0] == 'E' || line[0] == 'W' || line[0] == 'F' || line[0] == 'C')
	{
		if (line[0] != '\n')
			data = get_conf(line, data);
		line = get_next_line(fd);
		// line = sanitize_line(line);
	}
	m->con[y++] = line;
	while (y <= m->height)
	{
		m->con[y] = get_next_line(fd);
		y++;
	}
	m->len = ft_strlen(m->con[0]) - 1;
	close(fd);
	return (m);
}
