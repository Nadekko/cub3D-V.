/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_event_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:33:13 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/22 20:50:06 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

static int	ft_play(t_data *data)
{
	load_background(data);
	ft_raycasting(data);
	draw_player_to_image(data);
	ft_move(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img[5]->img, 0, 0);
	return (0);
}

void	rotate_player(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->raycast->dir_x;
	old_plane_x = data->raycast->plane_x;
	data->raycast->dir_x = data->raycast->dir_x * cos(angle)
		- data->raycast->dir_y * sin(angle);
	data->raycast->dir_y = old_dir_x * sin(angle)
		+ data->raycast->dir_y * cos(angle);
	data->raycast->plane_x = data->raycast->plane_x * cos(angle)
		- data->raycast->plane_y * sin(angle);
	data->raycast->plane_y = old_plane_x * sin(angle)
		+ data->raycast->plane_y * cos(angle);
}

int	mouse_move(int x,int y, t_data *data)
{
	int		last_x;
	
	(void)y;
	last_x = WIDTH / 2;
	if (x > last_x)
		rotate_player(data, ROT_SPEED);
	else if (x < last_x)
		rotate_player(data, -ROT_SPEED);
	last_x = WIDTH / 2;
	mlx_mouse_move(data->mlx->mlx, data->mlx->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}

// cette fonction permet de cacher le curseur de la souris mais elle leak
// mlx_mouse_hide(data->mlx->mlx, data->mlx->win);
void	ft_display_game(t_data *data)
{
	mlx_hook(data->mlx->win, 17, 1L << 17, ft_free_exit, data);
	mlx_hook(data->mlx->win, 2, 1L << 0, key_press, data);
	mlx_loop_hook(data->mlx->mlx, &ft_play, data);
	mlx_hook(data->mlx->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx->win, 6, 1L << 6, mouse_move, data);
	mlx_mouse_move(data->mlx->mlx, data->mlx->win, WIDTH / 2, HEIGHT / 2);
	mlx_loop(data->mlx->mlx);
}
