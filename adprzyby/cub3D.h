/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adprzyby <adprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:25:34 by cpuiu             #+#    #+#             */
/*   Updated: 2024/10/10 14:04:17 by adprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "Libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include "get_next_line/get_next_line.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <errno.h>

# define TEX_HEIGHT 64
# define TEX_WIDTH 64
# define SCREEN_H 720
# define SCREEN_W 1280

typedef struct s_vec2
{
	int				x;
	int				y;
}					t_vec2;

typedef struct s_view
{
	double			cam_x;
	double			cam_y;
	double			dir_x;
	double			dir_y;
	double			pos_x;
	double			pos_y;
	double			buff_dist;
	double			aspect_ratio;
	int				step_x;
	int				step_y;
}					t_view;

typedef struct s_map
{
	char			**map;
	char			**ff_map;
	t_vec2			start_pos;
	char			start_orientation;
	int				map_width;
	int				map_height;
	int				map_x;
	int				map_y;
	int				side;
	int				hit;
}					t_map;

typedef struct s_ray
{
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			dist;
	double			dir_x;
	double			dir_y;
	double			x_zero;
	double			x_max;
	double			y_zero;
	double			y_max;
}					t_ray;

typedef struct s_textures
{
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;
	mlx_texture_t	*tmp;
	uint32_t		*color;
	uint32_t		ceiling_color;
	uint32_t		floor_color;
	double			wall_x;
	int				x_tex;
	int				y_tex;
}					t_textures;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_view			*view;
	t_map			*map;
	t_ray			*ray;
	t_textures		*textures;
	mlx_image_t		*buffer;
	char			*my_error;
}					t_game;

// CONTROLS
void				key_binds(void *param);
void				case_esc(t_game *game);
void				case_key_back(t_game *game, double mv_speed);
void				case_key_forward(t_game *game, double mv_speed);
void				case_key_left(t_game *game, double mv_speed);
void				case_key_right(t_game *game, double mv_speed);
void				case_key_rot_left(t_game *game, double rot_speed,
						double old_dir_x, double old_cam_x);
void				case_key_rot_right(t_game *game, double rot_speed,
						double old_dir_x, double old_cam_x);

//PARSER
void				check_input(t_game *game, int argc, char *argv[]);
void				parser(t_game *game, char **argv);
bool				is_texture(t_game *game, char *line);
bool				is_color(t_game *game, char *line);
bool				is_map(t_game *game, char *line);
bool				is_empty_line(char *line);
bool				is_player_char(char c);
void				check_textures(t_game *game, char *line);
void				check_color(t_game *game, char *line);
void				check_map_part(t_game *game, int fd);
void				check_mapchars(t_game *game, char **map);
void				set_start_pos(t_game *game, t_map *map, int i, int j);
void				ft_replace_char(char **line, char c1, char c2);
void				flood_fill(t_game *game, int x, int y);
void				create_map(t_game *game, char *buf);
char				*load_map(t_game *game, char *line);
char				**copy_map(char **map);

//TERMINATE
void				terminate(t_game *game);
void				free_array(char **str);
void				free_textures(t_game *game);
void				free_up(t_game *game);
void				quit_error(void);

// INIT
void				init_view(t_view *view);
void				init_ray(t_ray *ray);
void				init_map(t_map *map);
void				init_textures(t_textures *textures);
void				init(t_game *game);
void				init_game_struct(t_game *game);
void				spawn_player(t_game *game);
void				spawn_pos_w_e(t_game *game);
void				spawn_pos_n_s(t_game *game);

// RENDER
void				render_structures(t_game *game);
void				draw_ceiling(t_game *game, int x, int draw_start);
void				draw_floor(t_game *game, int x, int draw_end);
void				put_image(t_game *game);
void				draw_walls(t_game *game, int x, int draw_end,
						int wall_height);
void				choose_texture(t_game *game);
void				check_if_side(t_game *game);
void				calculate_cam(t_game *game, int x);
void				calculate_delta(t_game *game);
void				calculate_pos(t_game *game);
void				calculate_hit(t_game *game);
void				calculate_ray(t_game *game);
int					calculate_draw_end(int wall_height);
int					calculate_draw_start(int wall_height);

#endif