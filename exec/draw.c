/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:10:59 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/13 03:23:44 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	draw_wall_to_image(t_data *data, int x, int draw_start, int draw_end, int color)
{
	int	y;

	y = draw_start;
	while (y < draw_end)
	{
		put_pixel(data->mlx->img[5], x, y, color);
		y++;
	}
}

void	draw_player_to_image(t_data *data)
{
	put_img_to_img(data, *data->mlx->img[4], 0, 0);
}

void	draw_celing(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT / 2)
		{
			// mlx_pixel_put(data->mlx->mlx, data->mlx->win, x, y, 0x87CEEB);
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
