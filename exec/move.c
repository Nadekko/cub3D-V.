/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:04:59 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/14 20:58:25 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int     key_release(int keycode, t_data *data)
{
	if (keycode == KEY_Z || keycode == KEY_W)
		data->move.z = 0;
	if (keycode == KEY_Q || keycode == KEY_A)
		data->move.q = 0;
	if (keycode == KEY_S)
		data->move.s = 0;
	if (keycode == KEY_D)
		data->move.d = 0;
	if (keycode == LEFT)
		data->move.l = 0;
	if (keycode == RIGHT)
		data->move.r = 0;
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		ft_free_exit(data);
	if (keycode == KEY_Z || keycode == KEY_W)
		data->move.z = 1;
	if (keycode == KEY_Q || keycode == KEY_A)
		data->move.q = 1;
	if (keycode == KEY_S)
		data->move.s = 1;
	if (keycode == KEY_D)
		data->move.d = 1;
	if (keycode == LEFT)
		data->move.l = 1;
	if (keycode == RIGHT)
		data->move.r = 1;
	return (0);
}

int	ft_rotate(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	if (data->move.l == 1)
	{
		old_dir_x = data->raycast->dir_x;
		data->raycast->dir_x = data->raycast->dir_x * cos(-ROT_SPEED)
			- data->raycast->dir_y * sin(-ROT_SPEED);
		data->raycast->dir_y = old_dir_x * sin(-ROT_SPEED)
			+ data->raycast->dir_y * cos(-ROT_SPEED);
		old_plane_x = data->raycast->plane_x;
		data->raycast->plane_x = data->raycast->plane_x * cos(-ROT_SPEED)
			- data->raycast->plane_y * sin(-ROT_SPEED);
		data->raycast->plane_y = old_plane_x * sin(-ROT_SPEED)
			+ data->raycast->plane_y * cos(-ROT_SPEED);
	}
	if (data->move.r == 1)
	{
		old_dir_x = data->raycast->dir_x;
		data->raycast->dir_x = data->raycast->dir_x * cos(ROT_SPEED)
			- data->raycast->dir_y * sin(ROT_SPEED);
		data->raycast->dir_y = old_dir_x * sin(ROT_SPEED) + data->raycast->dir_y
			* cos(ROT_SPEED);
		old_plane_x = data->raycast->plane_x;
		data->raycast->plane_x = data->raycast->plane_x * cos(ROT_SPEED)
			- data->raycast->plane_y * sin(ROT_SPEED);
		data->raycast->plane_y = old_plane_x * sin(ROT_SPEED)
			+ data->raycast->plane_y * cos(ROT_SPEED);
	}
	return (0);
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

int	ft_move(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x;
	new_y = data->player->pos_y;
	if (data->move.z == 1)
	{
		new_x += data->raycast->dir_x * MOVE_SPEED;
		new_y += data->raycast->dir_y * MOVE_SPEED;
	}
	if (data->move.s == 1)
	{
		new_x -= data->raycast->dir_x * MOVE_SPEED;
		new_y -= data->raycast->dir_y * MOVE_SPEED;
	}
	if (data->move.q == 1)
	{
		new_x -= data->raycast->plane_x * MOVE_SPEED;
		new_y -= data->raycast->plane_y * MOVE_SPEED;
	}
	if (data->move.d == 1)
	{
		new_x += data->raycast->plane_x * MOVE_SPEED;
		new_y += data->raycast->plane_y * MOVE_SPEED;
	}
	if (is_valid_move(new_x, new_y, data))
	{
		data->player->pos_x = new_x;
		data->player->pos_y = new_y;
	}
	else
		printf("COLLISION\n");
	return (0);
}

void	fill_background(t_data *data)
{
	draw_celing(data);
	draw_floor(data);
}

int	laod_background(t_data *data)
{
	// Vérifier si l'image existe déjà pour éviter une recréation inutile
	if (!data->mlx->img[5])
	{
		data->mlx->img[5] = malloc(sizeof(t_img));
		if (!data->mlx->img[5])
			return (1);
	}
	if (!data->mlx->img[5]->img)
	{
		printf("Création image...\n");
		data->mlx->img[5]->img = mlx_new_image(data->mlx->mlx, WIDTH, HEIGHT);
		if (!data->mlx->img[5]->img)
		{
			printf("Erreur : mlx_new_image a échoué !\n");
			return (1);
		}
		data->mlx->img[5]->width = WIDTH;
		data->mlx->img[5]->height = HEIGHT;
		printf("Image dimensions: %d x %d\n", data->mlx->img[5]->width, data->mlx->img[5]->height);
		data->mlx->img[5]->addr = mlx_get_data_addr(
			data->mlx->img[5]->img,
			&data->mlx->img[5]->bpp,
			&data->mlx->img[5]->line_len,
			&data->mlx->img[5]->endian
		);

		if (!data->mlx->img[5]->addr)
		{
			printf("Erreur : mlx_get_data_addr a échoué !\n");
			return (1);
		}
		printf("Image créée avec succès : %p | Addr: %p\n", data->mlx->img[5]->img, data->mlx->img[5]->addr);
	}
	fill_background(data);
	return (0);
}

int	ft_play(t_data *data)
{
	laod_background(data);
	ft_raycasting(data);
	ft_rotate(data);
	draw_player_to_image(data);
	ft_move(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img[5]->img, 0, 0);
	return (0);
}
