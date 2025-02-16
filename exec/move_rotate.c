/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:33:26 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/16 21:33:27 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	rotate_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->raycast->dir_x;
	data->raycast->dir_x = data->raycast->dir_x * cos(-ROT_SPEED)
		- data->raycast->dir_y * sin(-ROT_SPEED);
	data->raycast->dir_y = old_dir_x * sin(-ROT_SPEED)
		+ data->raycast->dir_y * cos(-ROT_SPEED);
	old_plane_x = data->raycast->plane_x;
	data->raycast->plane_x = data->raycast->plane_x * cos(-ROT_SPEED)
		- data->raycast->plane_y * sin(-ROT_SPEED);
	data->raycast->plane_y = old_plane_x * sin(-ROT_SPEED)
		+ data->raycast->plane_y * cos(-ROT_SPEED);
}

static void	rotate_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->raycast->dir_x;
	data->raycast->dir_x = data->raycast->dir_x * cos(ROT_SPEED)
		- data->raycast->dir_y * sin(ROT_SPEED);
	data->raycast->dir_y = old_dir_x * sin(ROT_SPEED)
		+ data->raycast->dir_y * cos(ROT_SPEED);
	old_plane_x = data->raycast->plane_x;
	data->raycast->plane_x = data->raycast->plane_x * cos(ROT_SPEED)
		- data->raycast->plane_y * sin(ROT_SPEED);
	data->raycast->plane_y = old_plane_x * sin(ROT_SPEED)
		+ data->raycast->plane_y * cos(ROT_SPEED);
}

int	ft_rotate(t_data *data)
{
	if (data->move.l == 1)
		rotate_left(data);
	if (data->move.r == 1)
		rotate_right(data);
	return (0);
}
