/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 23:28:49 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/23 02:04:12 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

static void	draw_celing(t_data *data)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	color = rgb_to_int(data->texture_c->red,
			data->texture_c->green, data->texture_c->blue);
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT / 2)
		{
			put_pixel(data->mlx->img[5], x, y, color);
			y++;
		}
		x++;
	}
}

static void	draw_floor(t_data *data)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	color = rgb_to_int(data->texture_f->red,
			data->texture_f->green, data->texture_f->blue);
	while (x < WIDTH)
	{
		y = HEIGHT / 2;
		while (y < HEIGHT)
		{
			put_pixel(data->mlx->img[5], x, y, color);
			y++;
		}
		x++;
	}
}

static void	fill_background(t_data *data)
{
	draw_celing(data);
	draw_floor(data);
}

int	load_background(t_data *data)
{
	// if (!data->mlx->img[BACKGROUND])
	// {
	// 	data->mlx->img[BACKGROUND] = malloc(sizeof(t_img));
	// 	if (!data->mlx->img[BACKGROUND])
	// 		return (1);
	// }
	// if (!data->mlx->img[BACKGROUND]->img)
	// {
	// 	printf("UECHHH\n\n");
	// 	data->mlx->img[BACKGROUND]->img = mlx_new_image(data->mlx->mlx, WIDTH, HEIGHT);
	// 	if (!data->mlx->img[BACKGROUND]->img)
	// 		return (printf("Erreur : mlx_new_image a échoué !\n"),
	// 			free(data->mlx->img[BACKGROUND]), 1);
	// 	data->mlx->img[BACKGROUND]->width = WIDTH;
	// 	data->mlx->img[BACKGROUND]->height = HEIGHT;
	// 	data->mlx->img[BACKGROUND]->addr = mlx_get_data_addr(
	// 			data->mlx->img[BACKGROUND]->img,
	// 			&data->mlx->img[BACKGROUND]->bpp,
	// 			&data->mlx->img[BACKGROUND]->line_len,
	// 			&data->mlx->img[BACKGROUND]->endian);
	// 	if (!data->mlx->img[BACKGROUND]->addr)
	// 		return (printf("Erreur : mlx_get_data_addr a échoué !\n"), 1);
	// }
	fill_background(data);
	return (0);
}
