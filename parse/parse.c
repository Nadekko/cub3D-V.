/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:59:06 by ede-cola          #+#    #+#             */
/*   Updated: 2025/02/17 12:57:14 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	ft_set_rgb_values(t_data *data, char *value, char zone, int i)
{
	if (i == 0)
	{
		if (zone == 'F')
			data->texture_f->red = ft_atoi(value);
		else if (zone == 'C')
			data->texture_c->red = ft_atoi(value);
	}
	else if (i == 1)
	{
		if (zone == 'F')
			data->texture_f->green = ft_atoi(value);
		else if (zone == 'C')
			data->texture_c->green = ft_atoi(value);
	}
	else if (i == 2)
	{
		if (zone == 'F')
			data->texture_f->blue = ft_atoi(value);
		else if (zone == 'C')
			data->texture_c->blue = ft_atoi(value);
	}
}

int	ft_get_rgb_values(char zone, char *texture, t_data *data)
{
	char	**tab;
	int		i;

	tab = ft_split(texture, ',');
	if (ft_tab_len(tab) > 3 || ft_tab_len(tab) < 3)
		return (ft_free_tab(tab), 1);
	i = 0;
	while (tab[i])
	{
		ft_set_rgb_values(data, tab[i], zone, i);
		i++;
	}
	ft_free_tab(tab);
	return (0);
}

int	ft_set_textures_struct(t_data *data, char *file, char zone)
{
	char	*tmp;

	if (zone == 'F')
	{
		data->texture_f = ft_calloc(1, sizeof(t_color));
		if (!data->texture_f)
			return (1);
		tmp = ft_get_textures_path(file, "F");
		if (ft_get_rgb_values('F', tmp, data))
			return (free(tmp), 1);
		free(tmp);
	}
	else if (zone == 'C')
	{
		data->texture_c = ft_calloc(1, sizeof(t_color));
		if (!data->texture_c)
			return (1);
		tmp = ft_get_textures_path(file, "C");
		if (ft_get_rgb_values('C', tmp, data))
			return (free(tmp), 1);
		free(tmp);
	}
	return (0);
}

int	ft_get_textures(char **file, t_data *data, int i, int j)
{
	if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'N'
		&& data->texture_n == NULL)
		data->texture_n = ft_get_textures_path(file[i], "NO");
	else if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'S'
		&& data->texture_s == NULL)
		data->texture_s = ft_get_textures_path(file[i], "SO");
	else if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'W'
		&& data->texture_w == NULL)
		data->texture_w = ft_get_textures_path(file[i], "WE");
	else if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'E'
		&& data->texture_e == NULL)
		data->texture_e = ft_get_textures_path(file[i], "EA");
	else if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'F'
		&& data->texture_f == NULL)
	{
		if (ft_set_textures_struct(data, file[i], 'F'))
			return (1);
	}
	else if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'C'
		&& data->texture_c == NULL)
	{
		if (ft_set_textures_struct(data, file[i], 'C'))
			return (1);
	}
	return (0);
}

void	ft_skip_whitespaces(char **file, int *i, int *j)
{
	(*j)++;
	if (!file[*i][*j] && file[*i])
	{
		(*i)++;
		*j = 0;
	}
}
