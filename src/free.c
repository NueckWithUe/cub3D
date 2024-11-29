/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:42:19 by nnagel            #+#    #+#             */
/*   Updated: 2024/11/29 12:32:56 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	*ft_free(t_data *data)
{
	int	i;

	i = 0;
	while (data->map->con[i])
	{
		free(data->map->con[i]);
		i++;
	}
	free(data->map->con);
	free(data->map);
	free(data->player);
	free(data->ray);
	mlx_delete_texture(data->tnorth);
	mlx_delete_texture(data->tsouth);
	mlx_delete_texture(data->teast);
	mlx_delete_texture(data->twest);
	mlx_delete_image(data->mlx, data->ibuffer);
	mlx_terminate(data->mlx);
	free(data);
	return (NULL);
}

void	*free_data(t_data *data)
{
	if (data->error == 2)
	{
		free(data->player);
	}
	if (data->error == 3)
	{
		free(data->ray);
		free(data->player);
	}
	free(data);
	return (NULL);
}