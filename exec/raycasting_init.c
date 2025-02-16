/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 22:28:29 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/16 22:28:49 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	set_delta(t_data *data)
{
	if (data->raycast->ray_y == 0)
		data->raycast->delta_x = 1e30;
	else
		data->raycast->delta_x = fabs(1 / data->raycast->ray_x);
	if (data->raycast->ray_x == 0)
		data->raycast->delta_y = 1e30;
	else
		data->raycast->delta_y = fabs(1 / data->raycast->ray_y);
}

static void	set_step_and_side(t_data *data)
{
	if (data->raycast->ray_x < 0)
	{
		data->raycast->step_x = -1;
		data->raycast->side_x = (data->player->pos_x - data->raycast->map_x)
			* data->raycast->delta_x;
	}
	else
	{
		data->raycast->step_x = 1;
		data->raycast->side_x = (data->raycast->map_x + 1.0
				- data->player->pos_x) * data->raycast->delta_x;
	}
	if (data->raycast->ray_y < 0)
	{
		data->raycast->step_y = -1;
		data->raycast->side_y = (data->player->pos_y - data->raycast->map_y)
			* data->raycast->delta_y;
	}
	else
	{
		data->raycast->step_y = 1;
		data->raycast->side_y = (data->raycast->map_y + 1.0
				- data->player->pos_y) * data->raycast->delta_y;
	}
}

void	init_raycasting(t_data *data, int i)
{
	data->raycast->camera_x = 2 * i / (double)WIDTH - 1;
	data->raycast->ray_x = data->raycast->dir_x + data->raycast->plane_x
		* data->raycast->camera_x;
	data->raycast->ray_y = data->raycast->dir_y + data->raycast->plane_y
		* data->raycast->camera_x;
	data->raycast->map_x = (int)data->player->pos_x;
	data->raycast->map_y = (int)data->player->pos_y;
	set_delta(data);
	set_step_and_side(data);
}
