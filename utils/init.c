/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:52:07 by ede-cola          #+#    #+#             */
/*   Updated: 2025/02/17 00:14:35 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_clean_init_data(t_data *data)
{
	data->map = NULL;
	data->mlx = NULL;
	data->raycast = NULL;
	data->player = NULL;
	data->texture_c = NULL;
	data->texture_f = NULL;
	data->texture_n = NULL;
	data->texture_s = NULL;
	data->texture_w = NULL;
	data->texture_e = NULL;
	return (0);
}

int	ft_clean_init_player(t_data *data)
{
	data->player = ft_calloc(1, sizeof(t_player));
	if (!data->player)
		return (1);
	data->player->pos_x = 0;
	data->player->pos_y = 0;
	data->player->next_x = 0;
	data->player->next_y = 0;
	return (0);
}

void	ft_clean_init_move(t_data *data)
{
	data->move.z = 0;
	data->move.q = 0;
	data->move.s = 0;
	data->move.d = 0;
	data->move.l = 0;
	data->move.r = 0;
}

int	mlx_start(t_data *data)
{
	data->mlx = ft_calloc(1, sizeof(t_mlx));
	if (!data->mlx)
		return (1);
	data->mlx->mlx = mlx_init();
	if (!data->mlx->mlx)
		return (1);
	data->mlx->win = NULL;
	return (0);
}

int	mlx_window_init(t_data *data)
{
	data->mlx->win = mlx_new_window(data->mlx->mlx, WIDTH, HEIGHT, "cub3D");
	if (!data->mlx->win)
		return (1);
	return (0);
}

// int ft_clean_init_mlx(t_data *data)
// {
// 	data->mlx = NULL;
// 	data->mlx->mlx = NULL;
// 	data->mlx->win = NULL;
// 	return (0);
// }
// t_size	*ft_screen_size(void *mlx)
// {
// 	t_size	*size;
// 	size = ft_calloc(1, sizeof(t_size));
// 	if (!size)
// 		return (NULL);
// 	mlx_get_screen_size(mlx, &size->screen_width, &size->screen_height);
// 	return (size);
// }