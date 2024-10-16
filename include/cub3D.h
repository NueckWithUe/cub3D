/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:13:03 by nnagel            #+#    #+#             */
/*   Updated: 2024/10/16 15:02:04 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

# include "libft.h"
# include "get_next_line.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# define WIDTH 1280
# define HEIGHT 720
# define FOV 1
# define DR 0.0174533
// # define M_PI 3.14159265358979323846
# define TEX_HEIGHT 64
# define TEX_WIDTH 64

typedef struct s_ray
{
	float	r_x;
	float	r_y;
	float	o_x;
	float	o_y;
	float	angle;
}	t_ray;

typedef struct s_map
{
	int		height;
	char	**con;
}	t_map;

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	d_x;
	float	d_y;
	float	angle;
}	t_player;

typedef struct s_data
{
	mlx_t			*mlx;
	t_player		*player;
	mlx_texture_t	*tNorth;
	mlx_texture_t	*tSouth;
	mlx_texture_t	*tEast;
	mlx_texture_t	*tWest;
	mlx_image_t		*iNorth;
	mlx_image_t		*iSouth;
	mlx_image_t		*iEast;
	mlx_image_t		*iWest;
	t_map			*map;
	t_ray			*ray;
}	t_data;

int		ft_error_handling(char **argv);
int		ft_check_extension(char *s);
int		ft_print_error(char *errmsg);
t_data	*init_data(void);
t_map	*get_map(char **argv, t_data *data);
int		ft_check_void(t_map *map);
void	raycaster(void *param);
void	ft_keypress(mlx_key_data_t keydata, void *param);
float	horizontal_line_check(t_data *data);
float	vertical_line_check(t_data *data);
void	convert_ray(t_data *d, float dist, float tmp);

#endif