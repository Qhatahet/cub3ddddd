/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:45:06 by oalananz          #+#    #+#             */
/*   Updated: 2025/08/14 15:45:31 by oalananz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_somethings1(t_draw *draw, t_raycast *raycast)
{
	if (draw->ray_dir_x < 0)
	{
		draw->step_x = -1;
		draw->side_dist_x = (raycast->pos_x - draw->map_x) * draw->delta_dist_x;
	}
	else
	{
		draw->step_x = 1;
		draw->side_dist_x = (draw->map_x + 1.0 - raycast->pos_x)
			* draw->delta_dist_x;
	}
	if (draw->ray_dir_y < 0)
	{
		draw->step_y = -1;
		draw->side_dist_y = (raycast->pos_y - draw->map_y) * draw->delta_dist_y;
	}
	else
	{
		draw->step_y = 1;
		draw->side_dist_y = (draw->map_y + 1.0 - raycast->pos_y)
			* draw->delta_dist_y;
	}
}

void	check_somethings2(t_draw *draw, t_raycast *raycast)
{
	while (draw->hit == 0)
	{
		if (draw->side_dist_x < draw->side_dist_y)
		{
			draw->side_dist_x += draw->delta_dist_x;
			draw->map_x += draw->step_x;
			draw->side = 0;
		}
		else
		{
			draw->side_dist_y += draw->delta_dist_y;
			draw->map_y += draw->step_y;
			draw->side = 1;
		}
		if (is_wall(raycast->game, draw->map_x, draw->map_y))
			draw->hit = 1;
	}
}

uint32_t	color_validation(mlx_texture_t *tex, t_draw *draw)
{
	return (tex->pixels[draw->index + 0] << 24
		| tex->pixels[draw->index + 1] << 16
		| tex->pixels[draw->index + 2] << 8
		| tex->pixels[draw->index + 3]);
}
