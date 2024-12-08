/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adprzyby <adprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:57:46 by adprzyby          #+#    #+#             */
/*   Updated: 2024/09/26 15:37:42 by adprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	key_binds(void *param)
{
	t_game	*game;
	double	mv_speed;
	double	rot_speed;

	game = (t_game *)param;
	mv_speed = 0.06;
	rot_speed = 0.05;
	put_image(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		case_key_forward(game, mv_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		case_key_back(game, mv_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		case_key_left(game, mv_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		case_key_right(game, mv_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		case_key_rot_left(game, rot_speed, 0.0, 0.0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		case_key_rot_right(game, rot_speed, 0.0, 0.0);
	case_esc(game);
}

void	case_key_rot_left(t_game *game, double rot_speed, double old_dir_x,
		double old_cam_x)
{
	old_dir_x = game->view->dir_x;
	game->view->dir_x = game->view->dir_x * cos(-rot_speed) - game->view->dir_y
		* sin(-rot_speed);
	game->view->dir_y = old_dir_x * sin(-rot_speed) + game->view->dir_y
		* cos(-rot_speed);
	old_cam_x = game->view->cam_x;
	game->view->cam_x = game->view->cam_x * cos(-rot_speed) - game->view->cam_y
		* sin(-rot_speed);
	game->view->cam_y = old_cam_x * sin(-rot_speed) + game->view->cam_y
		* cos(-rot_speed);
}

void	case_key_rot_right(t_game *game, double rot_speed, double old_dir_x,
		double old_cam_x)
{
	old_dir_x = game->view->dir_x;
	game->view->dir_x = game->view->dir_x * cos(rot_speed) - game->view->dir_y
		* sin(rot_speed);
	game->view->dir_y = old_dir_x * sin(rot_speed) + game->view->dir_y
		* cos(rot_speed);
	old_cam_x = game->view->cam_x;
	game->view->cam_x = game->view->cam_x * cos(rot_speed) - game->view->cam_y
		* sin(rot_speed);
	game->view->cam_y = old_cam_x * sin(rot_speed) + game->view->cam_y
		* cos(rot_speed);
}
