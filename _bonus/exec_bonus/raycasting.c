/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:38:31 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/25 04:56:53 by andjenna         ###   ########.fr       */
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
		data->raycast->draw_end = HEIGHT;
}

void	compute_door_dist(t_data *data)
{
	int		i;
	double	dist_x;
	double	dist_y;

	i = 0;
	while (i < data->doors->nb)
	{
		dist_x = data->doors[i].x - data->player->pos_x;
		dist_y = data->doors[i].y - data->player->pos_y;
		data->doors[i].dist_to_player = sqrt(dist_x * dist_x + dist_y * dist_y);
		i++;
	}
}

void draw_sprites(t_data *data, t_doors *door)
{
	int y;
	int x;
    // Position relative au joueur
    double rel_x = door->x + 0.5 - data->player->pos_x; // Décalage pour centrer
    double rel_y = door->y + 0.5 - data->player->pos_y;

    double inv_det = 1.0 / (data->raycast->plane_x * data->raycast->dir_y - data->raycast->dir_x * data->raycast->plane_y);
    double transform_x = inv_det * (data->raycast->dir_y * rel_x - data->raycast->dir_x * rel_y);
    double transform_y = inv_det * (-data->raycast->plane_y * rel_x + data->raycast->plane_x * rel_y);
    int sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
    int door_height = abs((int)(HEIGHT / door->dist_to_player));
    int door_width = door_height * 1.5;

    int start_y = HEIGHT / 2 - door_height / 2;
    if (start_y < 0) start_y = 0;
    int end_y = start_y + door_height;
    if (end_y >= HEIGHT)
		end_y = HEIGHT;

    int start_x = sprite_screen_x - door_width / 2;
    if (start_x < 0)
		start_x = 0;
    int end_x = start_x + door_width;
    if (end_x >= WIDTH)
		end_x = WIDTH ;
	y = start_y;
    while (y < end_y)
    {
		x = start_x;
        while (x < end_x)
        {
            int tex_x = (x - start_x) * PIXEL / door_width;
            int tex_y = (y - start_y) * PIXEL / door_height;

            unsigned int color;
            if (door->is_open == 1)
                color = get_pixel(*data->mlx->img[DOOR + 3], tex_x, tex_y);
            else
                color = get_pixel(*data->mlx->img[DOOR], tex_x, tex_y);

            if (color != 0xFF000000) // Évite d'afficher les pixels transparents
                put_pixel(data->mlx->img[BACKGROUND], x, y, color);
			x++;
        }
		y++;
    }
}


int ft_should_open_doors(int y, int x, t_data *data)
{
	int		nb_doors;
	int		i;
	float	dist_x;
	float	dist_y;
	float	dist;

	(void)dist;
	nb_doors = data->doors->nb;
	i = 0;
	dist_x = 0;
	dist_y = 0;
	dist = 0;
	while (i < nb_doors)
	{
		dist_x = x - data->player->pos_x;
		dist_y = y - data->player->pos_y;
		dist = sqrt(dist_x * dist_x + dist_y * dist_y);
		if ((dist_x * data->raycast->dir_x + dist_y * data->raycast->dir_y > 0))
			return (1);
		i++;
	}
	return (0);
}
void	draw_doors(t_data *data)
{
	int i;

	i = 0;
	while (i < data->doors->nb)
	{
		if (ft_should_open_doors(data->doors[i].y, data->doors[i].x, data) && data->doors[i].is_open == 1)
			draw_sprites(data, &data->doors[i]);
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
