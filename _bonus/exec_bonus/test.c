void	compute_door_dist(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->doors->nb)
	{
		data->doors[i].dist_to_player = sqrt(pow(data->doors[i].x - data->player->pos_x, 2)
				+ pow(data->doors[i].y - data->player->pos_y, 2));
		i++;
	}
}

void    ft_clean_init_sprites(t_data *data)
{
    int i;

    i = 0;
    data->sprite = ft_calloc(4, sizeof(t_sprite));
    if (!data->sprite)
        return ;
    while (i < 4)
    {
        data->sprite[i].sprite_x = 0;
        data->sprite[i].sprite_y = 0;
        data->sprite[i].inv_det = 0;
        data->sprite[i].transform_x = 0;
        data->sprite[i].transform_y = 0;
        data->sprite[i].sprite_screen_x = 0;
        data->sprite[i].sprite_height = 0;
        data->sprite[i].sprite_width = 0;
        data->sprite[i].start_y = 0;
        data->sprite[i].end_y = 0;
		data->sprite[i].start_x = 0;
		data->sprite[i].end_x = 0;
        i++;
    }
}

void    ft_init_sprites(t_data *data, int i)
{
    data->sprite[i].sprite_x = data->doors[i].x - data->player->pos_x;
    data->sprite[i].sprite_y = data->doors[i].y - data->player->pos_y;
    data->sprite[i].inv_det = 1.0 / (data->raycast->plane_x * data->raycast->dir_y
            - data->raycast->dir_x * data->raycast->plane_y);
    data->sprite[i].transform_x = data->sprite[i].inv_det * (data->raycast->dir_y
            * data->sprite[i].sprite_x - data->raycast->dir_x * data->sprite[i].sprite_y);
    data->sprite[i].transform_y = data->sprite[i].inv_det * (-data->raycast->plane_y
            * data->sprite[i].sprite_x + data->raycast->plane_x * data->sprite[i].sprite_y);

    data->sprite[i].sprite_screen_x = (int)((WIDTH / 2) * (1 + data->sprite[i].transform_x
                / data->sprite[i].transform_y));

    data->sprite[i].sprite_height = abs((int)(HEIGHT / data->sprite[i].transform_y));
    data->sprite[i].start_y = -data->sprite[i].sprite_height / 2 + HEIGHT / 2;
    if (data->sprite[i].start_y < 0)
        data->sprite[i].start_y = 0;
    data->sprite[i].end_y = data->sprite[i].sprite_height / 2 + HEIGHT / 2;
	if (data->sprite[i].end_y >= HEIGHT)
		data->sprite[i].end_y = HEIGHT - 1;
	data->sprite[i].sprite_width = abs((int)(HEIGHT / data->sprite[i].transform_y));
	data->sprite[i].start_x = -data->sprite[i].sprite_width / 2 + data->sprite[i].sprite_screen_x;
	if (data->sprite[i].start_x < 0)
		data->sprite[i].start_x = 0;
	data->sprite[i].end_x = data->sprite[i].sprite_width / 2 + data->sprite[i].sprite_screen_x;
	if (data->sprite[i].end_x >= WIDTH)
		data->sprite[i].end_x = WIDTH - 1;

}

void	draw_sprites(t_data *data)
{
	int	i;
	int	stripe;
	int	y;
	int	tex_x;
	int	tex_y;
	unsigned int	color;

	i = 0;
	ft_clean_init_sprites(data);
	compute_door_dist(data);
	while (i < 4)
	{
		ft_init_sprites(data, i); // Met à jour la position et la transformation du sprite

		// Boucle sur chaque colonne du sprite
		stripe = data->sprite[i].start_x;
		while (stripe < data->sprite[i].end_x)
		{
			tex_x = (int)(256 * (stripe - (-data->sprite[i].sprite_width / 2
						+ data->sprite[i].sprite_screen_x)) * PIXEL
					/ data->sprite[i].sprite_width) / 256;

			// Vérifications pour éviter les bugs d'affichage
			if (data->sprite[i].transform_y > 0 && stripe > 0
				&& stripe < WIDTH && data->sprite[i].transform_y < data->doors[i].dist_to_player)
			{
				y = data->sprite[i].start_y;
				while (y < data->sprite[i].end_y)
				{
					int d = (y) * 256 - HEIGHT * 128 + data->sprite[i].sprite_height * 128;
					tex_y = ((d * PIXEL) / data->sprite[i].sprite_height) / 256;

					// Récupération de la couleur du sprite
					color = get_pixel(*data->mlx->img[DOOR + i], tex_x, tex_y);

					// Vérification que le pixel n'est pas noir (transparent)
					if ((color & 0x00FFFFFF) != 0)
						put_pixel(data->mlx->img[BACKGROUND], stripe, y, color);
					y++;
				}
			}
			stripe++;
		}
		i++;
	}
}

void	ft_raycasting(t_data *data)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		init_raycasting(data, i);
		algo_dda(data);
		compute_wall_dist(data);
		put_texture(data, i);
		i++;
	}
	draw_sprites(data);
}
