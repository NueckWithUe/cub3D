/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:28:11 by sgeiger           #+#    #+#             */
/*   Updated: 2024/10/10 20:34:50 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

bool	is_color(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (ft_strlen(line + i) < 7)
		return (false);
	if (!ft_strncmp(line + i, "F ", 2) && game->textures->floor_color == 0)
		return (true);
	else if (!ft_strncmp(line + i, "C ", 2)
		&& game->textures->ceiling_color == 0)
	{
		return (true);
	}
	return (false);
}

int	add_color(t_textures *tex, int nbr, char c)
{
	static int	rgb[3] = {-1, -1, -1};
	static int	i = 0;

	if (i == 0)
		rgb[0] = nbr;
	else if (i == 1)
		rgb[1] = nbr;
	else if (i == 2)
	{
		rgb[2] = nbr;
		if (c == 'F')
			tex->floor_color = (rgb[0] << 24) | (rgb[1] << 16)
				| (rgb[2] << 8) | 255;
		else if (c == 'C')
			tex->ceiling_color = (rgb[0] << 24) | (rgb[1] << 16)
				| (rgb[2] << 8) | 255;
		i = 0;
		rgb[0] = -1;
		rgb[1] = -1;
		rgb[2] = -1;
		return (1);
	}
	i++;
	return (0);
}

int	check_number(t_game *game, char *line, int i, int start)
{
	char	*str_nbr;
	int		status;

	if (start == i)
	{
		free(line);
		game->my_error = "Color does not match pattern: 'C/F r,g,b'";
		terminate(game);
	}
	str_nbr = ft_substr(line, start, i - start);
	if (!str_nbr)
		terminate(game);
	if (ft_strlen(str_nbr) > 3 || ft_atoi(str_nbr) > 255)
	{
		free(str_nbr);
		free(line);
		game->my_error = "Number has to be between 0 and 255";
		terminate(game);
	}
	status = add_color(game->textures, ft_atoi(str_nbr), line[0]);
	free (str_nbr);
	return (status);
}

void	check_color(t_game *game, char *line)
{
	int		status;
	size_t	i;
	size_t	start;

	i = 2;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		start = i;
		while (ft_isdigit(line[i]))
			i++;
		status = check_number(game, line, i, start);
		if (status == 1 && line[i] == '\0')
			return ;
		while (ft_isspace(line[i]))
			i++;
		if ((status == 1 && line[i] != '\0') || (line[i] && line[i] != ','))
		{
			game->my_error = "Color does not match pattern: 'C/F r,g,b'";
			free(line);
			terminate(game);
		}
		i++;
	}
}
