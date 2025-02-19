/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:24:05 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/19 18:08:05 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	key_release(int keycode, t_data *data)
{
	if (keycode == KEY_Z || keycode == KEY_W)
		data->move.z = 0;
	if (keycode == KEY_Q || keycode == KEY_A)
		data->move.q = 0;
	if (keycode == KEY_S)
		data->move.s = 0;
	if (keycode == KEY_D)
		data->move.d = 0;
	// if (keycode == LEFT)
	// 	data->move.l = 0;
	// if (keycode == RIGHT)
	// 	data->move.r = 0;
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	int		i, j;
	(void)y;
	mlx_mouse_get_pos(data->mlx->mlx, data->mlx->win, &i, &j);
	if (x < i)
	{
		rotate_right(data);
		// data->move.r = 1;
		// data->move.l = 0;
	}
	else if (x > i)
	{
		rotate_left(data);
		// data->move.l = 1;
		// data->move.r = 0;
	}
	// data->player->mouse_x = x;
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
	// if (keycode == LEFT)
	// 	data->move.l = 1;
	// if (keycode == RIGHT)
	// 	data->move.r = 1;
	return (0);
}
