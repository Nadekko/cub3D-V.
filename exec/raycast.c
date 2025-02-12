/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:49:28 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/12 15:04:55 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_get_player_dir(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < ft_tab_len(data->map->map_tab))
	{
		j = 0;
		while (j < ft_strlen(data->map->map_tab[i]))
		{
			if (data->map->map_tab[i][j] == 'N')
			{
				data->raycast->dir_x = 0;
				data->raycast->dir_y = -1;
			}
			else if (data->map->map_tab[i][j] == 'S')
			{
				data->raycast->dir_x = 0;
				data->raycast->dir_y = 1;
			}
			else if (data->map->map_tab[i][j] == 'E')
			{
				data->raycast->dir_x = 1;
				data->raycast->dir_y = 0;
			}
			else if (data->map->map_tab[i][j] == 'W')
			{
				data->raycast->dir_x = -1;
				data->raycast->dir_y = 0;
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_get_player_pos(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < ft_tab_len(data->map->map_tab))
	{
		j = 0;
		while (j < ft_strlen(data->map->map_tab[i]))
		{
			if (data->map->map_int[i][j] == 3)
			{
				data->player->pos_y = (double)i;
				data->player->pos_x = (double)j;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

unsigned int	get_pixel(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.line_len)
			+ (x * img.bpp / 8))));
}

//copy the pixel on an img, ignore transparency
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < img->width && y < img->height)
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *) dst = color;
	}
}

//copy an img on another
void	put_img_to_img(t_data *data, t_img src, int x, int y)
{
	int	j;
	int	i;

	i = 0;
	(void)y;
	while (i < src.width)
	{
		j = 0;
		while (j < src.height)
		{
			if (get_pixel(src, i, j) != 0xFF000000)
				mlx_pixel_put(data->mlx->mlx, data->mlx->win, (x + i), ((HEIGHT / 7) + j), get_pixel(src, i, j));
			j++;
		}
		i++;
	}
}

void	draw_player(t_data *data)
{
	put_img_to_img(data, *data->mlx->img[4], 0, 0);
}

void	draw_wall(t_data *data, int x, int draw_start, int draw_end, int color)
{
	int	y;

	y = draw_start;
	while (y < draw_end)
	{
		mlx_pixel_put(data->mlx->mlx, data->mlx->win, x, y, color);
		y++;
	}
}

void	draw_ray2(t_data *data, double ray_x, double ray_y, double dir_x,
		double dir_y)
{
	int	map_x;
	int	map_y;

	while (1)
	{
		map_x = (int)ray_x;
		map_y = (int)ray_y;
		if (map_x < 0 || map_x >= data->map->width || map_y < 0
			|| map_y >= data->map->height)
			break ;
		if (data->map->map_int[map_y][map_x] == 1)
			break ;
		mlx_pixel_put(data->mlx->mlx, data->mlx->win, (ray_x * PIXEL) + (PIXEL
				/ (PIXEL / 2)), (ray_y * PIXEL) + (PIXEL / (PIXEL / 2)),
			0x00FF00);
		ray_x += dir_x * ROT_SPEED;
		ray_y += dir_y * ROT_SPEED;
	}
}

void	draw_ceiling_and_floor(t_data *data, int color_ceiling, int color_floor)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_pixel_put(data->mlx->mlx, data->mlx->win, x, y, color_ceiling); // Plafond
			else
				mlx_pixel_put(data->mlx->mlx, data->mlx->win, x, y, color_floor); // Sol
			x++;
		}
		y++;
	}
}

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
	draw_ceiling_and_floor(data, 0x85c1e9, 0x22455d);
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
		draw_wall(data, i, draw_start, draw_end, color);
		i++;
	}
	draw_player(data);
}

int	is_valid_move(double new_x, double new_y, t_data *data)
{
	int	map_x;
	int	map_y;

	if (new_x < 0 || new_x >= data->map->width || new_y < 0
		|| new_y >= data->map->height)
		return (0);
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (data->map->map_int[map_y][map_x] == 1)
		return (0);
	return (1);
}