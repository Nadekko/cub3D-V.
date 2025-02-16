/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:08:58 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/16 21:49:44 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static unsigned int	get_pixel(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.line_len)
			+ (x * img.bpp / 8))));
}

//copy the pixel on an img
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img->addr)
		return ;
	if (x >= 0 && y >= 0 && x < img->width && y < img->height)
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *) dst = color;
	}
	else
		printf("Erreur : put_pixel hors limites (%d, %d)\n", x, y);
}

//copy an img on another, ignore transparency
void	put_img_to_img(t_data *data, t_img src, int x, int y)
{
	int	j;
	int	i;

	(void)y;
	i = 0;
	while (i < src.width)
	{
		j = 0;
		while (j < src.height)
		{
			if (get_pixel(src, i, j) != 0xFF000000)
				put_pixel(data->mlx->img[5], (x + i), ((HEIGHT / 7.1) + j),
					get_pixel(src, i, j));
			j++;
		}
		i++;
	}
}

static void	fill_background(t_data *data)
{
	draw_celing(data);
	draw_floor(data);
}

int	load_background(t_data *data)
{
	if (!data->mlx->img[5])
	{
		data->mlx->img[5] = malloc(sizeof(t_img));
		if (!data->mlx->img[5])
			return (1);
	}
	if (!data->mlx->img[5]->img)
	{
		data->mlx->img[5]->img = mlx_new_image(data->mlx->mlx, WIDTH, HEIGHT);
		if (!data->mlx->img[5]->img)
			return (printf("Erreur : mlx_new_image a échoué !\n"), 1);
		data->mlx->img[5]->width = WIDTH;
		data->mlx->img[5]->height = HEIGHT;
		data->mlx->img[5]->addr = mlx_get_data_addr(
				data->mlx->img[5]->img,
				&data->mlx->img[5]->bpp,
				&data->mlx->img[5]->line_len,
				&data->mlx->img[5]->endian);
		if (!data->mlx->img[5]->addr)
			return (printf("Erreur : mlx_get_data_addr a échoué !\n"), 1);
	}
	fill_background(data);
	return (0);
}
