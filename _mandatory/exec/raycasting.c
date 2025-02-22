/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:38:31 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/22 18:15:48 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

static void	algo_dda(t_data *data)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (data->raycast->side_x < data->raycast->side_y)
		{
			data->raycast->side_x += data->raycast->delta_x;
			data->raycast->map_x += data->raycast->step_x;
			data->raycast->side = 0;
		}
		else
		{
			data->raycast->side_y += data->raycast->delta_y;
			data->raycast->map_y += data->raycast->step_y;
			data->raycast->side = 1;
		}
		if (data->map->map_int[data->raycast->map_y][data->raycast->map_x] == 1)
			hit = 1;
	}
}

static void	compute_wall_dist(t_data *data)
{
	if (data->raycast->side == 0)
		data->raycast->wall_dist = (data->raycast->map_x
				- data->player->pos_x + (1 - data->raycast->step_x) / 2)
			/ data->raycast->ray_x;
	else
		data->raycast->wall_dist = (data->raycast->map_y
				- data->player->pos_y + (1 - data->raycast->step_y) / 2)
			/ data->raycast->ray_y;
	data->raycast->line_height = (int)(HEIGHT / data->raycast->wall_dist);
	data->raycast->draw_start = -data->raycast->line_height / 2 + HEIGHT / 2;
	if (data->raycast->draw_start < 0)
		data->raycast->draw_start = 0;
	data->raycast->draw_end = data->raycast->line_height / 2 + HEIGHT / 2;
	if (data->raycast->draw_end >= HEIGHT)
		data->raycast->draw_end = HEIGHT;
}

void	set_texture(t_data *data, int i)
{
	double wall_x;

	if (data->raycast->side == 0)
	{
		if (data->raycast->ray_x > 0)
			data->raycast->texture = NO_TEXTURE;
		else
			data->raycast->texture = SO_TEXTURE;
	}
	else
	{
		if (data->raycast->ray_y > 0)
			data->raycast->texture = EA_TEXTURE;
		else
			data->raycast->texture = WE_TEXTURE;
	}
	if (data->raycast->side == 0)
		wall_x = data->player->pos_y + data->raycast->wall_dist * data->raycast->ray_y;
	else
		wall_x = data->player->pos_x + data->raycast->wall_dist * data->raycast->ray_x;
	wall_x -= floor(wall_x);
	int	tex_x = (int)(wall_x * (double)PIXEL);
	if ((data->raycast->side == 0 && data->raycast->ray_x > 0) || (data->raycast->side == 1 && data->raycast->ray_y < 0))
		tex_x = PIXEL - tex_x - 1;
	int y = data->raycast->draw_start;
	int	color = 0;
	int	tex_y = 0;
	double step = (double)PIXEL / data->raycast->line_height;
	double tex_p = (data->raycast->draw_start - HEIGHT / 2 + data->raycast->line_height / 2) * step;
	while (y < data->raycast->draw_end)
	{
		tex_y = (int)tex_p % PIXEL;
		tex_p += step;
		color = get_pixel(*data->mlx->img[data->raycast->texture], tex_x, tex_y);
		put_pixel(data->mlx->img[5], i, y, color);
		y++;
	}
}

void	ft_raycasting(t_data *data)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		init_raycasting(data, i);
		algo_dda(data);
		compute_wall_dist(data);
		set_texture(data, i);
		i++;
	}
}
