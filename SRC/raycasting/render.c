/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:49:24 by oalananz          #+#    #+#             */
/*   Updated: 2025/08/30 21:55:22 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_loop(void *param)
{
	t_raycast	*raycast;

	raycast = (t_raycast *)param;
	draw_floor_ceiling(raycast);
	draw_walls(raycast);
}

void	set_direction_norm(t_raycast *raycast)
{
	if (raycast->game->player->c == 'W')
	{
		raycast->dir_x = -1.0;
		raycast->dir_y = 0.0;
		raycast->plane_x = 0.0;
		raycast->plane_y = -0.66;
	}
	else
	{
		raycast->dir_x = 0.0;
		raycast->dir_y = -1.0;
		raycast->plane_x = 0.66;
		raycast->plane_y = 0.0;
	}
}

void	set_direction(t_raycast *raycast)
{
	if (raycast->game->player->c == 'N')
	{
		raycast->dir_x = 0.0;
		raycast->dir_y = -1.0;
		raycast->plane_x = 0.66;
		raycast->plane_y = 0.0;
	}
	else if (raycast->game->player->c == 'S')
	{
		raycast->dir_x = 0.0;
		raycast->dir_y = 1.0;
		raycast->plane_x = -0.66;
		raycast->plane_y = 0.0;
	}
	else if (raycast->game->player->c == 'E')
	{
		raycast->dir_x = 1.0;
		raycast->dir_y = 0.0;
		raycast->plane_x = 0.0;
		raycast->plane_y = 0.66;
	}
	else
		set_direction_norm(raycast);
}

void	raycast_init(t_raycast *raycast)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		raycast->wall_textures[i] = NULL;
		i++;
	}
}

int	render(t_game *game)
{
	t_raycast	*raycast;

	if (!game || !game->map || !game->player)
	{
		printf("Error: Invalid game data\n");
		return (-1);
	}
	raycast = ft_calloc(1, sizeof(t_raycast));
	if (!raycast)
		return (-1);
	raycast_init(raycast);
	raycast->game = game;
	if (initialize_mlx(raycast) == -1)
		return (-1);
	raycast->pos_x = (double)game->player->column + 0.5;
	raycast->pos_y = (double)game->player->row + 0.5;
	set_direction(raycast);
	mlx_loop_hook(raycast->mlx, game_loop, raycast);
	mlx_loop_hook(raycast->mlx, key_callback, raycast);
	mlx_set_cursor_mode(raycast->mlx, MLX_MOUSE_HIDDEN);
	mlx_cursor_hook(raycast->mlx, mouse_move_callback, raycast);
	mlx_loop(raycast->mlx);
	clean_up(raycast);
	return (0);
}
