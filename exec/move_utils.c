/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:24:05 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/16 21:28:05 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
