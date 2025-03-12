/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:41:48 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/12 18:33:56 by andjenna         ###   ########.fr       */
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
		return (0);
	}
	load_background(data);
	ft_raycasting(data);
	put_img_to_img(data, *data->mlx->img[PLAYER + data->anim_frame], 0, 0);
	data->anim_frame++;
	usleep(10000);
	return (0);
}


/* CHECK LA OU LE PLAYER REGARDE ET SI LA DOORS EST PROCHE, VERIRFIER LE KEYBUTTON POUR LE CLICK DROIT*/
int	animation_doors(t_data *data)
{
	if (!data->doors->is_open)
		return (0);
	if (data->anim_frame > 4)
	{
		data->doors->is_open = 0;
		data->anim_frame = 0;
		return (0);
	}
	load_background(data);
	ft_raycasting(data);
	put_img_to_img(data, *data->mlx->img[DOOR + data->anim_frame], 0, 0);
	data->anim_frame++;
	usleep(10000);
	return (0);
}

int	is_near_player(t_data *data, int x, int y)
{
	int	pos_x;
	int	pos_y;

	pos_x = floor(data->player->pos_x);
	pos_y = floor(data->player->pos_y);
	printf("pos_x = %d\n", pos_x);
	printf("pos_y = %d\n", pos_y);
	if (x == pos_x && y == pos_y)
		return (1);
	return (0);
}

int	mouse_press(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	int nb_doors = data->doors->nb;
	if (button == 1)
	{
		data->anim_frame = 1;
		data->anim_running = 1;
		printf("paws animation\n");
		printf("player_x = %f\n", data->player->pos_x);
		printf("player_y = %f\n", data->player->pos_y);
		int i = 0;
		while (i < nb_doors)
		{
			if (is_near_player(data, data->doors[i].x, data->doors[i].y))
			{
				data->doors[i].is_open = 1;
				printf("door[%d] is open\n", i);
			}
			i++;
		}
	}
	if (button == XK_Pointer_Button2)
	{
		printf("door animation\n");
		data->anim_frame = 1;
		data->anim_running = 1;
	}
	return (0);
}
