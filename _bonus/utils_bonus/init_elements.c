/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:32:00 by ede-cola          #+#    #+#             */
/*   Updated: 2025/03/19 19:52:21 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

int	ft_get_fish(t_data *data, int nb)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = -1;
	if (nb == 0)
		return (0);
	data->fish = ft_calloc(nb, sizeof(t_fish));
	if (!data->fish)
		return (1);
	while (data->map->map_tab[++j])
	{
		k = -1;
		while (data->map->map_tab[j][++k])
		{
			if (data->map->map_tab[j][k] == 'F')
			{
				data->fish[i].x = k;
				data->fish[i].y = j;
				data->fish[i].is_collected = 0;
				data->fish[i].nb = ft_counter(data->map->map_tab, 'F');
				data->fish[i].anim_frame = 0;
				i++;
			}
		}
	}
	return (0);
}

int	ft_get_doors(t_data *data, int nb)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = -1;
	if (nb == 0)
		return (0);
	data->doors = ft_calloc(nb, sizeof(t_doors));
	if (!data->doors)
		return (1);
	while (data->map->map_tab[++j])
	{
		k = -1;
		while (data->map->map_tab[j][++k])
		{
			if (data->map->map_tab[j][k] == 'D')
			{
				data->doors[i].x = k;
				data->doors[i].y = j;
				data->doors[i].is_open = 0;
				data->doors[i].nb = ft_counter(data->map->map_tab, 'D');
				data->doors[i].anim_frame = 0;
				data->doors[i].dist_to_player = 0;
				printf("door[%d] _x = %f, _y = %f\n", i, data->doors[i].x, data->doors[i].y);
				i++;
			}
		}
	}
	return (0);
}

int	ft_clean_init_elements(t_data *data)
{
	int	nb_fish;
	int	nb_doors;

	nb_fish = ft_counter(data->map->map_tab, 'F');
	nb_doors = ft_counter(data->map->map_tab, 'D');
	if (nb_fish == 0 && nb_doors == 0)
		return (0);
	if (ft_get_fish(data, nb_fish) || ft_get_doors(data, nb_doors))
		return (1);
	return (0);
}
