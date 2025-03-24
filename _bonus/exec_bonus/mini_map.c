/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:39:19 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/27 05:54:57 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

void	draw_on_mini_map(t_img *img, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if ((x + i) >= 0 && (x + i) < MINISIZE
				&& (y + j) >= 0 && (y + j) < MINISIZE)
				put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	clear_mini_map(t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINISIZE)
	{
		x = 0;
		while (x < MINISIZE)
		{
			put_pixel(img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	fill_mini_map(t_data *data)
{
	int		x;
	int		y;
	int		map_x;
	int		map_y;
	double	offset[2];

	clear_mini_map(data->mlx->img[MINI_MAP]);
	offset[0] = data->player->pos_x - ((MINISIZE / 2.0) / 30);
	offset[1] = data->player->pos_y - ((MINISIZE / 2.0) / 30);
	y = -1;
	while (++y < MINISIZE)
	{
		x = -1;
		while (++x < MINISIZE)
		{
			map_x = (int)(offset[0] + (x / (double)30));
			map_y = (int)(offset[1] + (y / (double)30));
			if (map_x >= 0 && map_x < data->map->width
				&& map_y >= 0 && map_y < data->map->height)
			{
				if (data->map->map_tab[map_y][map_x] == '1')
					draw_on_mini_map(data->mlx->img[MINI_MAP], x, y,
						TILE_SIZE, 0xbb8fce);
				else if (data->map->map_tab[map_y][map_x] == '0'
					|| ft_strchr("NSWE", data->map->map_tab[map_y][map_x]))
					draw_on_mini_map(data->mlx->img[MINI_MAP], x, y,
						TILE_SIZE, 0xabb2b9);
				else if (data->map->map_int[map_y][map_x] == 4
					|| ft_strchr("NSWE", data->map->map_tab[map_y][map_x]))
					draw_on_mini_map(data->mlx->img[MINI_MAP], x, y,
						TILE_SIZE, 0xaf70d1);
			}
		}
	}
	draw_on_mini_map(data->mlx->img[MINI_MAP], MINISIZE / 2, MINISIZE / 2, TILE_SIZE, 0xFF0000);
}

void	load_mini_map(t_data *data)
{
	fill_mini_map(data);
}
