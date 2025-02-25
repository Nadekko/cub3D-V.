/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:39:19 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/23 06:12:11 by andjenna         ###   ########.fr       */
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

// const float	zoom = 0.3;
// const int	tile_size = (int)(10 * zoom);

void	fill_mini_map(t_data *data)
{
	int		x;
	int		y;
	int		map_x;
	int		map_y;
	float	offset[2];

	clear_mini_map(data->mlx->img[MINI_MAP]);
	offset[0] = data->player->pos_x - ((MINISIZE / 2.0) / TILE_SIZE);
	offset[1] = data->player->pos_y - ((MINISIZE / 2.0) / TILE_SIZE);
	y = -1;
	while (++y < MINISIZE)
	{
		x = -1;
		while (++x < MINISIZE)
		{
			map_x = (int)(offset[0] + (x / (float)TILE_SIZE));
			map_y = (int)(offset[1] + (y / (float)TILE_SIZE));
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
			}
		}
	}
	draw_on_mini_map(data->mlx->img[MINI_MAP], MINISIZE / 2,
		MINISIZE / 2, 10, 0xFF0000);
}

void	load_mini_map(t_data *data)
{
	fill_mini_map(data);
}
