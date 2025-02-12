/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:04:59 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/12 16:36:38 by ede-cola         ###   ########.fr       */
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
	{
		ft_free_data(data);
		exit(0);
	}
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
		printf("LEFT\n");
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
		printf("RIGHT\n");
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
	ft_raycasting(data);
	return (0);
}

int	ft_play(t_data *data)
{
	ft_rotate(data);
	ft_move(data);
	draw_player(data);
	return (0);
}
// int	press_key(unsigned int keycode, t_data *data)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = data->player->pos_x;
// 	new_y = data->player->pos_y;
// 	direction_key(keycode, data);
// 	if (keycode == KEY_ESC)
// 	{
// 		ft_free_data(data);
// 		exit(0);
// 	}
// 	if (keycode == KEY_W || keycode == KEY_Z)
// 	{
// 		new_x += data->raycast->dir_x * MOVE_SPEED;
// 		new_y += data->raycast->dir_y * MOVE_SPEED;
// 	}
// 	if (keycode == KEY_S)
// 	{
// 		new_x -= data->raycast->dir_x * MOVE_SPEED;
// 		new_y -= data->raycast->dir_y * MOVE_SPEED;
// 	}
// 	if (keycode == KEY_A || keycode == KEY_Q)
// 	{
// 		new_x -= data->raycast->plane_x * MOVE_SPEED;
// 		new_y -= data->raycast->plane_y * MOVE_SPEED;
// 	}
// 	if (keycode == KEY_D)
// 	{
// 		new_x += data->raycast->plane_x * MOVE_SPEED;
// 		new_y += data->raycast->plane_y * MOVE_SPEED;
// 	}
// 	printf("Dir: (%f, %f)\n", data->raycast->dir_x, data->raycast->dir_y);
// 	printf("Plane: (%f, %f)\n", data->raycast->plane_x, data->raycast->plane_y);
// 	printf("New pos: (%f, %f)\n", new_x, new_y);
// 	if (is_valid_move(new_x, new_y, data))
// 	{
// 		printf("new_x = %f\n", new_x);
// 		printf("new_y = %f\n", new_y);
// 		data->player->pos_x = new_x;
// 		data->player->pos_y = new_y;
// 	}
// 	else
// 		printf("Mouvement bloqué !\n");
// 	// mlx_clear_window(data->mlx->mlx, data->mlx->win);
// 	draw_ray(data);
// 	draw_player(data);
// 	return (0);
// }