/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:49:28 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/14 16:25:02 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	init_raycasting(t_data *data, int i)
{
	data->raycast->camera_x = 2 * i / (double)WIDTH - 1;
	data->raycast->ray_x = data->raycast->dir_x + data->raycast->plane_x
		* data->raycast->camera_x;
	data->raycast->ray_y = data->raycast->dir_y + data->raycast->plane_y
		* data->raycast->camera_x;
	data->raycast->map_x = (int)data->player->pos_x;
	data->raycast->map_y = (int)data->player->pos_y;
	data->raycast->delta_x = (data->raycast->ray_x == 0) ? 1e30 : fabs(1/ data->raycast->ray_x);
	data->raycast->delta_y = (data->raycast->ray_y == 0) ? 1e30 : fabs(1 / data->raycast->ray_y);
	data->raycast->step_x = (data->raycast->ray_x < 0) ? -1 : 1;
	data->raycast->step_y = (data->raycast->ray_y < 0) ? -1 : 1;
	data->raycast->side_x = (data->raycast->ray_x < 0)
		? (data->player->pos_x - data->raycast->map_x) * data->raycast->delta_x
		: (data->raycast->map_x + 1.0 - data->player->pos_x) * data->raycast->delta_x;
	data->raycast->side_y = (data->raycast->ray_y < 0)
		? (data->player->pos_y - data->raycast->map_y) * data->raycast->delta_y
		: (data->raycast->map_y + 1.0 - data->player->pos_y) * data->raycast->delta_y;
}

static int	algo_DDA(t_data *data)
{
	int	hit;
	int	side;


	hit = 0;
	side = 0;
	while (!hit)
	{
		if (data->raycast->side_x < data->raycast->side_y)
		{
			data->raycast->side_x += data->raycast->delta_x;
			data->raycast->map_x += data->raycast->step_x;
			side = 0;
		}
		else
		{
			data->raycast->side_y += data->raycast->delta_y;
			data->raycast->map_y += data->raycast->step_y;
			side = 1;
		}
		if (data->map->map_int[data->raycast->map_y][data->raycast->map_x] == 1)
			hit = 1;
	}
	return (side);
}

static void	compute_wall_dist(t_data *data, int side)
{
	if (side == 0)
		data->raycast->wall_dist = (data->raycast->map_x - data->player->pos_x
				+ (1 - data->raycast->step_x) / 2) / data->raycast->ray_x;
	else
		data->raycast->wall_dist = (data->raycast->map_y - data->player->pos_y
				+ (1 - data->raycast->step_y) / 2) / data->raycast->ray_y;
	data->raycast->line_height = (int)(HEIGHT / data->raycast->wall_dist);
	data->raycast->draw_start = -data->raycast->line_height / 2 + HEIGHT / 2;
	if (data->raycast->draw_start < 0)
		data->raycast->draw_start = 0;
	data->raycast->draw_end = data->raycast->line_height / 2 + HEIGHT / 2;
	if (data->raycast->draw_end >= HEIGHT)
		data->raycast->draw_end = HEIGHT - 1;
}

static void	draw_wall_column(t_data *data, int side, int i)
{
	int	color;

	color = (side == 0) ? 0xaf70d1 : 0x48225d;
	draw_wall_to_image(data, i, data->raycast->draw_start, data->raycast->draw_end, color);
}

void	ft_raycasting(t_data *data)
{
	int	i;
	int	side;

	i = 0;
	while (i < WIDTH)
	{
		init_raycasting(data, i);
		side = algo_DDA(data);
		compute_wall_dist(data, side);
		draw_wall_column(data, side, i);
		i++;
	}
}

// void	ft_raycasting(t_data *data)
// {
// 	int	i;
// 	int	step_x;
// 	int	step_y;
// 	int	hit;
// 	int	side; // 0 = vertical, 1 = horizontal
// 	int	line_height;
// 	int	draw_start;
// 	int	draw_end;
// 	int	color;

// 	i = 0;
// 	while (i < WIDTH)
// 	{
// 		// 1. Calcul de la direction du rayon dans l'espace caméra
// 		data->raycast->camera_x = 2 * i / (double)WIDTH - 1;
// 		data->raycast->ray_x = data->raycast->dir_x + data->raycast->plane_x * data->raycast->camera_x;
// 		data->raycast->ray_y = data->raycast->dir_y + data->raycast->plane_y * data->raycast->camera_x;

// 		// 2. Position actuelle du joueur
// 		data->raycast->map_x = (int)data->player->pos_x;
// 		data->raycast->map_y = (int)data->player->pos_y;

// 		// 3. Distance à la première intersection de grille
// 		data->raycast->delta_x = (data->raycast->ray_x == 0) ? 1e30 : fabs(1 / data->raycast->ray_x);
// 		data->raycast->delta_y = (data->raycast->ray_y == 0) ? 1e30 : fabs(1 / data->raycast->ray_y);

// 		// 4. Détermination des directions de progression
// 		step_x = (data->raycast->ray_x < 0) ? -1 : 1;
// 		data->raycast->side_x = (data->raycast->ray_x < 0)
// 			? (data->player->pos_x - data->raycast->map_x) * data->raycast->delta_x
// 			: (data->raycast->map_x + 1.0 - data->player->pos_x) * data->raycast->delta_x;
// 		step_y = (data->raycast->ray_y < 0) ? -1 : 1;
// 		data->raycast->side_y = (data->raycast->ray_y < 0)
// 			? (data->player->pos_y - data->raycast->map_y) * data->raycast->delta_y
// 			: (data->raycast->map_y + 1.0 - data->player->pos_y) * data->raycast->delta_y;

// 		// 5. Algorithme de DDA
// 		hit = 0;
// 		while (!hit)
// 		{
// 			if (data->raycast->side_x < data->raycast->side_y)
// 			{
// 				data->raycast->side_x += data->raycast->delta_x;
// 				data->raycast->map_x += step_x;
// 				side = 0; // Mur vertical
// 			}
// 			else
// 			{
// 				data->raycast->side_y += data->raycast->delta_y;
// 				data->raycast->map_y += step_y;
// 				side = 1; // Mur horizontal
// 			}
// 			if (data->map->map_int[data->raycast->map_y][data->raycast->map_x] == 1)
// 				hit = 1;
// 		}

// 		// 6. Calcul de la distance au mur touché
// 		if (side == 0)
// 			data->raycast->wall_dist = (data->raycast->map_x - data->player->pos_x + (1 - step_x) / 2) / data->raycast->ray_x;
// 		else
// 			data->raycast->wall_dist = (data->raycast->map_y - data->player->pos_y + (1 - step_y) / 2) / data->raycast->ray_y;

// 		// 7. Calcul des bornes de dessin du mur
// 		line_height = (int)(HEIGHT / data->raycast->wall_dist);
// 		draw_start = -line_height / 2 + HEIGHT / 2;
// 		if (draw_start < 0)
// 			draw_start = 0;
// 		draw_end = line_height / 2 + HEIGHT / 2;
// 		if (draw_end >= HEIGHT)
// 			draw_end = HEIGHT - 1;

// 		// 8. Définition de la couleur du mur selon son orientation
// 		color = (side == 0) ? 0xaf70d1 : 0x48225d; // Vertical = clair, Horizontal = foncé

// 		// 9. Dessiner le mur sur l'image de background
// 		draw_wall_to_image(data, i, draw_start, draw_end, color);

// 		i++;
// 	}
// }

// void	ft_raycasting(t_data *data)
// {
// 	int	i;
// 	int	step_x;
// 	int	step_y;
// 	int	hit;
// 	int	line_height;
// 	int	draw_start;
// 	int	draw_end;
// 	int	color;

// 	i = 0;
// 	while (i < WIDTH)
// 	{
// 		// 1. Calcul de la direction du rayon dans l'espace caméra
// 		data->raycast->camera_x = 2 * i / (double)WIDTH - 1;
// 		data->raycast->ray_x = data->raycast->dir_x + data->raycast->plane_x
// 			* data->raycast->camera_x;
// 		data->raycast->ray_y = data->raycast->dir_y + data->raycast->plane_y
// 			* data->raycast->camera_x;
// 		// 2. Position actuelle du joueur
// 		data->raycast->map_x = (int)data->player->pos_x;
// 		data->raycast->map_y = (int)data->player->pos_y;
// 		// 3. Distance à la première intersection de grille
// 		data->raycast->delta_x = (data->raycast->ray_x == 0) ? 1e30 : fabs(1
// 				/ data->raycast->ray_x);
// 		data->raycast->delta_y = (data->raycast->ray_y == 0) ? 1e30 : fabs(1
// 				/ data->raycast->ray_y);
// 		// 4. Détermination des directions de progression
// 		step_x = (data->raycast->ray_x < 0) ? -1 : 1;
// 		data->raycast->side_x = (data->raycast->ray_x < 0) ? (data->player->pos_x
// 				- data->raycast->map_x)
// 			* data->raycast->delta_x : (data->raycast->map_x + 1.0
// 				- data->player->pos_x) * data->raycast->delta_x;
// 		step_y = (data->raycast->ray_y < 0) ? -1 : 1;
// 		data->raycast->side_y = (data->raycast->ray_y < 0) ? (data->player->pos_y
// 				- data->raycast->map_y)
// 			* data->raycast->delta_y : (data->raycast->map_y + 1.0
// 				- data->player->pos_y) * data->raycast->delta_y;
// 		// 5. Algorithme de DDA
// 		hit = 0;
// 		while (!hit)
// 		{
// 			if (data->raycast->side_x < data->raycast->side_y)
// 			{
// 				data->raycast->side_x += data->raycast->delta_x;
// 				data->raycast->map_x += step_x;
// 			}
// 			else
// 			{
// 				data->raycast->side_y += data->raycast->delta_y;
// 				data->raycast->map_y += step_y;
// 			}
// 			if (data->map->map_int[data->raycast->map_y][data->raycast->map_x] == 1)
// 				hit = 1;
// 		}
// 		if (data->raycast->side_x < data->raycast->side_y)
// 			data->raycast->wall_dist = (data->raycast->map_x
// 					- data->player->pos_x + (1 - step_x) / 2)
// 				/ data->raycast->ray_x;
// 		else
// 			data->raycast->wall_dist = (data->raycast->map_y
// 					- data->player->pos_y + (1 - step_y) / 2)
// 				/ data->raycast->ray_y;
// 		line_height = (int)(HEIGHT / data->raycast->wall_dist);
// 		draw_start = -line_height / 2 + HEIGHT / 2;
// 		if (draw_start < 0)
// 			draw_start = 0;
// 		draw_end = line_height / 2 + HEIGHT / 2;
// 		if (draw_end >= HEIGHT)
// 			draw_end = HEIGHT - 1;
// 		color = (data->raycast->side_x < data->raycast->side_y) ? 0xaf70d1 : 0x48225d;
// 		draw_wall_to_image(data, i, draw_start, draw_end, color);
// 		i++;
// 	}
// }
