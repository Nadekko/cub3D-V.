/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:41:48 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/06 17:06:51 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"


int animation_paws(t_data *data)
{
	if (!data->anim_running)
		return (0);
	if (data->anim_frame > 9)
	{
		data->anim_running = 0;
		return (0);
	}
	load_background(data);
	ft_raycasting(data);
	put_img_to_img(data, *data->mlx->img[PLAYER + data->anim_frame], 0, 0);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img[BACKGROUND]->img, 0, 0);
	data->anim_frame++;
	usleep(10000);
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
	return (0);
}
