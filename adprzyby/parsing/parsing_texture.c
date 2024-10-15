/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adprzyby <adprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:28:13 by sgeiger           #+#    #+#             */
/*   Updated: 2024/10/10 15:17:34 by adprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	count_space(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	return (i);
}

bool	is_texture(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (ft_strlen(line + i) < 4)
		return (false);
	if (!ft_strncmp(line + i, "NO ", 3) && !game->textures->no_texture)
		return (true);
	else if (!ft_strncmp(line + i, "SO ", 3) && !game->textures->so_texture)
		return (true);
	else if (!ft_strncmp(line + i, "WE ", 3) && !game->textures->we_texture)
		return (true);
	else if (!ft_strncmp(line + i, "EA ", 3) && !game->textures->ea_texture)
		return (true);
	else
		return (false);
}

void	create_texture(t_game *game, char *path, mlx_texture_t **texture)
{
	if (!*texture)
	{
		*texture = mlx_load_png(path);
		if (!*texture)
			terminate(game);
	}
	free(path);
	return ;
}

void	check_textures(t_game *game, char *line)
{
	int		fd;
	int		space;
	char	*path;

	space = count_space(line + 2);
	path = ft_substr(line, space + 2, ft_strlen(line) - space - 2);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		free(line);
		terminate(game);
	}
	if (!ft_strncmp(line, "NO ", 3))
		create_texture(game, path, &game->textures->no_texture);
	else if (!ft_strncmp(line, "SO ", 3))
		create_texture(game, path, &game->textures->so_texture);
	else if (!ft_strncmp(line, "EA ", 3))
		create_texture(game, path, &game->textures->ea_texture);
	else if (!ft_strncmp(line, "WE ", 3))
		create_texture(game, path, &game->textures->we_texture);
}
