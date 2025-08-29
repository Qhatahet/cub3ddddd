/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:04:18 by oalananz          #+#    #+#             */
/*   Updated: 2025/08/12 17:55:23 by oalananz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map->utils->width || y < 0
		|| y >= game->map->utils->size)
		return (1);
	return (game->map->map[y][x] == '1');
}

char	get_map_cell(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map->utils->width || y < 0
		|| y >= game->map->utils->size)
		return ('1');
	return (game->map->map[y][x]);
}

void	my_mlx_pixel_put(t_raycast *raycast, int x, int y, uint32_t color)
{
	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
		mlx_put_pixel(raycast->img, x, y, color);
}

void	draw_floor_ceiling(t_raycast *raycast)
{
	int		x;
	int		y;
	t_game	*game;

	y = 0;
	game = raycast->game;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (y > WINDOW_HEIGHT / 2)
				my_mlx_pixel_put(raycast, x, y, game->map->floor->mixed);
			else
				my_mlx_pixel_put(raycast, x, y, game->map->ceiling->mixed);
			x++;
		}
		y++;
	}
}

int	get_wall_texture(int side, double ray_dir_x, double ray_dir_y)
{
	if (side == 0)
	{
		if (ray_dir_x > 0)
			return (3);
		else
			return (2);
	}
	else
	{
		if (ray_dir_y > 0)
			return (1);
		else
			return (0);
	}
}
