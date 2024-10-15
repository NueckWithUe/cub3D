/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:37:49 by sgeiger           #+#    #+#             */
/*   Updated: 2024/09/26 17:00:36 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_input(t_game *game, int argc, char **argv)
{
	size_t	len;

	if (argc != 2)
	{
		game->my_error = "Input has to be: \"./cub3d <map.cub>\"";
		terminate(game);
	}
	len = ft_strlen(argv[1]);
	if (len <= 4 || ft_strcmp(argv[1] + len - 4, ".cub") != 0)
	{
		game->my_error = "Input file has to be \".cub\"";
		terminate(game);
	}
}

bool	is_empty_line(char *line)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(line);
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (i == len)
		return (true);
	return (false);
}

void	check_tex_or_color(t_game *game, char *line)
{
	char	*new_line;

	if (is_empty_line(line))
	{
		free(line);
		return ;
	}
	new_line = ft_strtrim(line, " \t\r\n");
	free(line);
	line = NULL;
	if (!new_line)
		terminate(game);
	if (is_texture(game, new_line))
		check_textures(game, new_line);
	else if (is_color(game, new_line))
		check_color(game, new_line);
	else
	{
		game->my_error = "Invalid file content";
		free(new_line);
		terminate(game);
	}
	free(new_line);
}

bool	are_values_set(t_textures *tex)
{
	if (!tex->no_texture || !tex->so_texture
		|| !tex->we_texture || !tex->ea_texture)
	{
		return (false);
	}
	if (tex->floor_color == 0 || tex->ceiling_color == 0)
		return (false);
	return (true);
}

void	parser(t_game *game, char **argv)
{
	char	*line;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		terminate(game);
	while (!are_values_set(game->textures))
	{
		line = get_next_line(fd);
		if (!line)
		{
			game->my_error = "Incomplete file content";
			terminate(game);
		}
		check_tex_or_color(game, line);
	}
	check_map_part(game, fd);
}
