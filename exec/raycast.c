/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:49:28 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/13 03:24:17 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	ft_raycasting(t_data *data)
{
	int	i;
	int	step_x;
	int	step_y;
	int	hit;
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;

	i = 0;
	while (i < WIDTH)
	{
		// 1. Calcul de la direction du rayon dans l'espace caméra
		data->raycast->camera_x = 2 * i / (double)WIDTH - 1;
		data->raycast->ray_x = data->raycast->dir_x + data->raycast->plane_x
			* data->raycast->camera_x;
		data->raycast->ray_y = data->raycast->dir_y + data->raycast->plane_y
			* data->raycast->camera_x;
		// 2. Position actuelle du joueur
		data->raycast->map_x = (int)data->player->pos_x;
		data->raycast->map_y = (int)data->player->pos_y;
		// 3. Distance à la première intersection de grille
		data->raycast->delta_x = (data->raycast->ray_x == 0) ? 1e30 : fabs(1
				/ data->raycast->ray_x);
		data->raycast->delta_y = (data->raycast->ray_y == 0) ? 1e30 : fabs(1
				/ data->raycast->ray_y);
		// 4. Détermination des directions de progression
		step_x = (data->raycast->ray_x < 0) ? -1 : 1;
		data->raycast->side_x = (data->raycast->ray_x < 0) ? (data->player->pos_x
				- data->raycast->map_x)
			* data->raycast->delta_x : (data->raycast->map_x + 1.0
				- data->player->pos_x) * data->raycast->delta_x;
		step_y = (data->raycast->ray_y < 0) ? -1 : 1;
		data->raycast->side_y = (data->raycast->ray_y < 0) ? (data->player->pos_y
				- data->raycast->map_y)
			* data->raycast->delta_y : (data->raycast->map_y + 1.0
				- data->player->pos_y) * data->raycast->delta_y;
		// 5. Algorithme de DDA
		hit = 0;
		while (!hit)
		{
			if (data->raycast->side_x < data->raycast->side_y)
			{
				data->raycast->side_x += data->raycast->delta_x;
				data->raycast->map_x += step_x;
			}
			else
			{
				data->raycast->side_y += data->raycast->delta_y;
				data->raycast->map_y += step_y;
			}
			if (data->map->map_int[data->raycast->map_y][data->raycast->map_x] == 1)
				hit = 1;
		}
		if (data->raycast->side_x < data->raycast->side_y)
			data->raycast->wall_dist = (data->raycast->map_x
					- data->player->pos_x + (1 - step_x) / 2)
				/ data->raycast->ray_x;
		else
			data->raycast->wall_dist = (data->raycast->map_y
					- data->player->pos_y + (1 - step_y) / 2)
				/ data->raycast->ray_y;
		line_height = (int)(HEIGHT / data->raycast->wall_dist);
		draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		color = (data->raycast->side_x < data->raycast->side_y) ? 0xaf70d1 : 0x48225d;
		draw_wall_to_image(data, i, draw_start, draw_end, color);
		i++;
	}
}
