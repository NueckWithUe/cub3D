/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:35:20 by adprzyby          #+#    #+#             */
/*   Updated: 2024/10/04 01:26:26 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_ceiling(t_game *game, int x, int draw_start)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		mlx_put_pixel(game->buffer, x, y, game->textures->ceiling_color);
		y++;
	}
}

void	draw_floor(t_game *game, int x, int draw_end)
{
	int	y;

	if (draw_end < 0 || draw_end >= SCREEN_H - 1)
		return ;
	y = draw_end + 1;
	while (y < SCREEN_H)
	{
		if (x >= 0 && x < SCREEN_W)
			mlx_put_pixel(game->buffer, x, y, game->textures->floor_color);
		y++;
	}
}

void	calculate_cam(t_game *game, int x)
{
	double	camera_x;

	camera_x = (2 * x / (double)SCREEN_W - 1) * game->view->aspect_ratio;
	game->ray->dir_x = game->view->dir_x + game->view->cam_x * camera_x;
	game->ray->dir_y = game->view->dir_y + game->view->cam_y * camera_x;
	game->map->map_x = (int)game->view->pos_x;
	game->map->map_y = (int)game->view->pos_y;
}

void	calculate_delta(t_game *game)
{
	if (game->ray->dir_x == 0)
		game->ray->delta_dist_x = 1e30;
	else
		game->ray->delta_dist_x = fabs(1 / game->ray->dir_x);
	if (game->ray->dir_y == 0)
		game->ray->delta_dist_y = 1e30;
	else
		game->ray->delta_dist_y = fabs(1 / game->ray->dir_y);
}

void	calculate_pos(t_game *game)
{
	if (game->ray->dir_x < 0)
	{
		game->view->step_x = -1;
		game->ray->side_dist_x = (game->view->pos_x - game->map->map_x)
			* game->ray->delta_dist_x;
	}
	else
	{
		game->view->step_x = 1;
		game->ray->side_dist_x = (game->map->map_x + 1.0 - game->view->pos_x)
			* game->ray->delta_dist_x;
	}
	if (game->ray->dir_y < 0)
	{
		game->view->step_y = -1;
		game->ray->side_dist_y = (game->view->pos_y - game->map->map_y)
			* game->ray->delta_dist_y;
	}
	else
	{
		game->view->step_y = 1;
		game->ray->side_dist_y = (game->map->map_y + 1.0 - game->view->pos_y)
			* game->ray->delta_dist_y;
	}
}
