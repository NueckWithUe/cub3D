/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adprzyby <adprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:44:28 by adprzyby          #+#    #+#             */
/*   Updated: 2024/10/10 15:20:50 by adprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	render_structures(t_game *game)
{
	int	wall_height;
	int	draw_start;
	int	draw_end;
	int	x;

	x = 0;
	while (x < SCREEN_W)
	{
		calculate_cam(game, x);
		calculate_delta(game);
		game->map->hit = 0;
		calculate_pos(game);
		calculate_hit(game);
		calculate_ray(game);
		wall_height = (int)(SCREEN_H / game->ray->dist);
		draw_start = calculate_draw_start(wall_height);
		draw_end = calculate_draw_end(wall_height);
		draw_ceiling(game, x, draw_start);
		draw_walls(game, x, draw_end, wall_height);
		draw_floor(game, x, draw_end);
		x++;
	}
}

void	put_image(t_game *game)
{
	mlx_delete_image(game->mlx, game->buffer);
	game->buffer = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	render_structures(game);
	mlx_image_to_window(game->mlx, game->buffer, 0, 0);
}

void	draw_walls(t_game *game, int x, int draw_end,
		int wall_height)
{
	uint32_t	new_color;
	int			y;

	y = calculate_draw_start(wall_height);
	choose_texture(game);
	check_if_side(game);
	while (y < draw_end)
	{
		game->textures->y_tex = (((y * 256 - SCREEN_H * 128 + wall_height * 128)
					* TEX_HEIGHT) / wall_height) / 256;
		if (game->textures->y_tex >= 0 && game->textures->y_tex < TEX_HEIGHT
			&& game->textures->x_tex >= 0 && game->textures->x_tex < TEX_WIDTH)
		{
			game->textures->color = (uint32_t *)(game->textures->tmp->pixels
					+ (game->textures->y_tex * TEX_WIDTH
						+ game->textures->x_tex) * sizeof(uint32_t));
			new_color = ((*game->textures->color & 0xFF000000) >> 24)
				| ((*game->textures->color & 0x00FF0000) >> 8)
				| ((*game->textures->color & 0x0000FF00) << 8)
				| ((*game->textures->color & 0x000000FF) << 24);
			mlx_put_pixel(game->buffer, x, y, new_color);
		}
		y++;
	}
}

void	choose_texture(t_game *game)
{
	if (game->map->side == 0 && game->ray->dir_x > 0)
		game->textures->tmp = game->textures->ea_texture;
	else if (game->map->side == 0 && game->ray->dir_x < 0)
		game->textures->tmp = game->textures->we_texture;
	else if (game->map->side == 1 && game->ray->dir_y > 0)
		game->textures->tmp = game->textures->so_texture;
	else
		game->textures->tmp = game->textures->no_texture;
}

void	check_if_side(t_game *game)
{
	if (game->map->side == 0)
		game->textures->wall_x = game->view->pos_y + game->ray->dist
			* game->ray->dir_y;
	else
		game->textures->wall_x = game->view->pos_x + game->ray->dist
			* game->ray->dir_x;
	game->textures->wall_x -= floor(game->textures->wall_x);
	game->textures->x_tex = (int)(game->textures->wall_x * (double)TEX_WIDTH);
	if (game->map->side == 0 && game->ray->dir_x > 0)
		game->textures->x_tex = TEX_WIDTH - game->textures->x_tex - 1;
	if (game->map->side == 1 && game->ray->dir_y < 0)
		game->textures->x_tex = TEX_WIDTH - game->textures->x_tex - 1;
}
