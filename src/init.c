#include "../include/cub3D.h"

static t_player *init_player(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	player->pos_x = 0;
	player->pos_y = 0;
	return (player);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->player = init_player();
	if (!data->player)
		return (NULL);
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 0);
	if (!data->mlx)
		return (NULL);
	return (data);
}