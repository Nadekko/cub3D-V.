/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:04:59 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/25 16:11:59 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

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
	return (0);
}

static int	is_valid_move(double new_x, double new_y, t_data *data)
{
	double hitbox_size;
	int collision;
	int collision_x;
	int collision_y;
	
	hitbox_size = 0.1;

	collision = (data->map->map_int[(int)(new_y + hitbox_size)][(int)(new_x + hitbox_size)] == 1 ||
					data->map->map_int[(int)(new_y - hitbox_size)][(int)(new_x - hitbox_size)] == 1 ||
					data->map->map_int[(int)(new_y + hitbox_size)][(int)(new_x + hitbox_size)] == 4 ||
					data->map->map_int[(int)(new_y - hitbox_size)][(int)(new_x - hitbox_size)] == 4);

	collision_x = (data->map->map_int[(int)(new_y)][(int)(new_x + hitbox_size)] == 1 ||
					   data->map->map_int[(int)(new_y)][(int)(new_x - hitbox_size)] == 1 ||
					   data->map->map_int[(int)(new_y)][(int)(new_x + hitbox_size)] == 4 ||
					   data->map->map_int[(int)(new_y)][(int)(new_x - hitbox_size)] == 4);
	collision_y = (data->map->map_int[(int)(new_y + hitbox_size)][(int)(new_x)] == 1 ||
					   data->map->map_int[(int)(new_y - hitbox_size)][(int)(new_x)] == 1 ||
					   data->map->map_int[(int)(new_y + hitbox_size)][(int)(new_x)] == 1 ||
					   data->map->map_int[(int)(new_y - hitbox_size)][(int)(new_x)] == 1);
	if (collision)
	{
		if (!collision_x && (data->map->map_int[(int)(new_y)][(int)(new_x)] != 1 ||
				data->map->map_int[(int)(new_y)][(int)(new_x)] != 4))
			return (2);
		if (!collision_y && (data->map->map_int[(int)(new_y)][(int)(new_x)] != 1 ||
				data->map->map_int[(int)(new_y)][(int)(new_x)] != 4))
			return (3);
		return (0);
	}
	return (1);
}

static void	get_new_position(t_data *data, double *new_x, double *new_y)
{
	*new_x = data->player->pos_x;
	*new_y = data->player->pos_y;
	if (data->move.z == 1)
	{
		*new_x += data->raycast->dir_x * MOVE_SPEED;
		*new_y += data->raycast->dir_y * MOVE_SPEED;
	}
	if (data->move.s == 1)
	{
		*new_x -= data->raycast->dir_x * MOVE_SPEED;
		*new_y -= data->raycast->dir_y * MOVE_SPEED;
	}
	if (data->move.q == 1)
	{
		*new_x -= data->raycast->plane_x * MOVE_SPEED;
		*new_y -= data->raycast->plane_y * MOVE_SPEED;
	}
	if (data->move.d == 1)
	{
		*new_x += data->raycast->plane_x * MOVE_SPEED;
		*new_y += data->raycast->plane_y * MOVE_SPEED;
	}
}

int	ft_move(t_data *data)
{
	double	new_x;
	double	new_y;

	get_new_position(data, &new_x, &new_y);
	int move_status = is_valid_move(new_x, new_y, data);
	if (move_status == 1)
	{
		data->player->pos_x = new_x;
		data->player->pos_y = new_y;
	}
	else if (move_status == 2)
		data->player->pos_x = new_x;
	else if (move_status == 3)
		data->player->pos_y = new_y;
	
	return (0);
}

