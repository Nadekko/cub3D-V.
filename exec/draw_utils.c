/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:08:58 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/13 03:22:34 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

unsigned int	get_pixel(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.line_len)
			+ (x * img.bpp / 8))));
}

//copy the pixel on an img, ignore transparency
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

//copy an img on another
void	put_img_to_img(t_data *data, t_img src, int x, int y)
{
	int	j;
	int	i;

	i = 0;
	while (i < src.width)
	{
		j = 0;
		while (j < src.height)
		{
			if (get_pixel(src, i, j) != 0xFF000000)
				put_pixel(data->mlx->img[5], (x + i), (y + j), get_pixel(src, i, j));
			j++;
		}
		i++;
	}
}
