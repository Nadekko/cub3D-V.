/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:10:59 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/16 21:29:39 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	draw_player_to_image(t_data *data)
{
	put_img_to_img(data, *data->mlx->img[4], 0, 0);
}

void	draw_wall_to_image(t_data *data, int x, int draw_start, int draw_end)
{
	int	y;
	int	color;

	//ici on devra faire appel au converstisseur rgb pour color;
	if (data->raycast->side == 0)
		color = 0xaf70d1;
	else
		color = 0x48225d;
	y = draw_start;
	while (y < draw_end)
	{
		put_pixel(data->mlx->img[5], x, y, color);
		y++;
	}
}

void	draw_celing(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	//appel a rgb converter;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT / 2)
		{
			put_pixel(data->mlx->img[5], x, y, 0x85C1E9);
			y++;
		}
		x++;
	}
}

void	draw_floor(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	//appel a rgb converter;
	while (x < WIDTH)
	{
		y = HEIGHT / 2;
		while (y < HEIGHT)
		{
			put_pixel(data->mlx->img[5], x, y, 0x22455d);
			y++;
		}
		x++;
	}
}
