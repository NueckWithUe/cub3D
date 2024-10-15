/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:52:08 by sgeiger           #+#    #+#             */
/*   Updated: 2024/10/09 02:43:32 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	quit_error(void)
{
	size_t		len;
	const char	*str;

	str = mlx_strerror(mlx_errno);
	len = ft_strlen(str);
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, str, len);
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	free_textures(t_game *game)
{
	if (game->textures->no_texture)
		mlx_delete_texture(game->textures->no_texture);
	if (game->textures->so_texture)
		mlx_delete_texture(game->textures->so_texture);
	if (game->textures->ea_texture)
		mlx_delete_texture(game->textures->ea_texture);
	if (game->textures->we_texture)
		mlx_delete_texture(game->textures->we_texture);
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_up(t_game *game)
{
	if (game->map->map)
		free_array(game->map->map);
	if (game->map->ff_map)
		free_array(game->map->ff_map);
	if (game->view)
		free(game->view);
	if (game->map)
		free(game->map);
	if (game->ray)
		free(game->ray);
	if (game->textures)
	{
		free_textures(game);
		free(game->textures);
	}
	free(game);
}

void	terminate(t_game *game)
{
	size_t		len;
	const char	*str;

	len = 0;
	str = NULL;
	if (game->my_error != NULL)
	{
		write(STDERR_FILENO, "Error: ", 7);
		write(STDERR_FILENO, game->my_error, ft_strlen(game->my_error));
		write(STDERR_FILENO, "\n", 1);
	}
	else if (mlx_errno != 0)
	{
		str = mlx_strerror(mlx_errno);
		len = ft_strlen(str);
		write(STDERR_FILENO, "Error: ", 7);
		write(STDERR_FILENO, str, len);
		write(STDERR_FILENO, "\n", 1);
	}
	else if (errno != 0)
		perror("Error");
	if (game->mlx)
		mlx_terminate(game->mlx);
	free_up(game);
	exit(EXIT_FAILURE);
}
