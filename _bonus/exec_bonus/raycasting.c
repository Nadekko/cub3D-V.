/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:38:31 by andjenna          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/19 12:54:23 by ede-cola         ###   ########.fr       */
=======
/*   Updated: 2025/03/19 20:27:13 by andjenna         ###   ########.fr       */
>>>>>>> f7c01c49c05c6ae2baa352826ff58e345c4ccac1
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

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
		if (data->map->map_int[data->raycast->map_y][data->raycast->map_x] == 1
				|| data->map->map_int[data->raycast->map_y][data->raycast->map_x] == 4)
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

void compute_door_dist(t_data *data)
{
	int i;
	double dist_x;
	double dist_y;

	i = 0;
	while (i < data->doors->nb)
	{
		dist_x = data->doors[i].x - data->player->pos_x;
		dist_y = data->doors[i].y - data->player->pos_y;
		data->doors[i].dist_to_player = sqrt(dist_x * dist_x + dist_y * dist_y);
		i++;
	}
}

void draw_sprites(t_data *data, t_img *img, int x, int door_height)
{
	int y_start;
	int y_end;
	int tex_y;
	int color;

	y_start = HEIGHT / 2 - door_height / 2;
	if (y_start < 0)
		y_start = 0;
	y_end = HEIGHT / 2 + door_height / 2;
	if (y_end >= HEIGHT)
		y_end = HEIGHT - 1;
	int y = y_start;
	while (y < y_end)
	{
		tex_y = (y - y_start) * PIXEL / door_height;
		color = get_pixel(*img, PIXEL / 2, tex_y);
		if (color != 0)
			put_pixel(data->mlx->img[BACKGROUND], x, y_start, color);
		y++;
	}
}
void draw_doors(t_data *data)
{
	int i;
	int door_height;
	int x;
	// int y;

	i = 0;
	x = 0;
	// y = 0;
	door_height = 0;
	while (i < data->doors->nb)
	{
		if (data->doors[i].is_open)
		{
			door_height = (int)(HEIGHT / data->doors[i].dist_to_player);
			x = (int)(data->doors[i].x * TILE_SIZE);
			// y = (int)(data->doors[i].y * TILE_SIZE);
			if (data->doors[i].anim_frame <= 1)
				draw_sprites(data, data->mlx->img[DOOR + data->doors[i].anim_frame], x, door_height);
		}
		i++;
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
		put_texture(data, i);
		i++;
	}
	compute_door_dist(data);
	draw_doors(data);
}
