/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 23:28:49 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/06 14:55:28 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

static void	draw_celing(t_data *data)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	color = rgb_to_int(data->texture_c->red,
			data->texture_c->green, data->texture_c->blue);
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT / 2)
		{
			put_pixel(data->mlx->img[BACKGROUND], x, y, color);
			y++;
		}
		x++;
	}
}

static void	draw_floor(t_data *data)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	color = rgb_to_int(data->texture_f->red,
			data->texture_f->green, data->texture_f->blue);
	while (x < WIDTH)
	{
		y = HEIGHT / 2;
		while (y < HEIGHT)
		{
			put_pixel(data->mlx->img[BACKGROUND], x, y, color);
			y++;
		}
		x++;
	}
}

int	load_background(t_data *data)
{
	draw_celing(data);
	draw_floor(data);
	return (0);
}
