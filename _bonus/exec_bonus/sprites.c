/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:41:48 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/14 17:28:47 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"
#include <X11/keysym.h>

int animation_paws(t_data *data)
{
	if (!data->anim_running)
		return (0);
	if (data->anim_frame > 9)
	{
		data->anim_running = 0;
		data->anim_frame = 0;
		return (0);
	}
	load_background(data);
	ft_raycasting(data);
	put_img_to_img(data, *data->mlx->img[PLAYER + data->anim_frame], 0, 0);
	data->anim_frame++;
	usleep(10000);
	return (0);
}

int	animation_doors(t_data *data, int x, int y)
{
	int		i;

	i = 0;
	
	return (0);
}

int	is_near_player(t_data *data)
{
	int		nb_doors;
	int		i;
	float	dist_x;
	float	dist_y;
	float	dist;

	nb_doors = data->doors->nb;
	i = 0;
	dist_x = 0;
	dist_y = 0;
	dist = 0;
	while (i < nb_doors)
	{
		dist_x = data->doors[i].x - data->player->pos_x;
		dist_y = data->doors[i].y - data->player->pos_y;
		dist = sqrt(dist_x * dist_x + dist_y * dist_y);
		if (dist <= 1.5 && (dist_x * data->raycast->dir_x + dist_y * data->raycast->dir_y > 0))
		{
			printf("door is near\n");
			data->doors[i].is_open = 1;
			data->map->map_int[(int)data->doors[i].y][(int)data->doors[i].x] = 5;
			return (1);
		}
		i++;
	}
	return (0);
}

int	mouse_press(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		data->anim_frame = 1;
		data->anim_running = 1;
	}
	if (button == 3)
	{
		is_near_player(data);
		data->anim_frame = 1;
		data->anim_running = 1;
	}
	return (0);
}
