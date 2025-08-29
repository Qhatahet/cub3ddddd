/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:11:32 by oalananz          #+#    #+#             */
/*   Updated: 2025/08/14 15:45:25 by oalananz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixels(t_draw *draw, mlx_texture_t *tex, t_raycast *raycast, int x)
{
	int	y;

	y = draw->draw_start;
	while (y < draw->draw_end)
	{
		draw->tex_y = (int)draw->tex_pos;
		draw->tex_pos += draw->step;
		if (draw->tex_y < 0)
			draw->tex_y = 0;
		else if (draw->tex_y >= (int)tex->height)
			draw->tex_y = tex->height - 1;
		draw->index = (draw->tex_y * tex->width + draw->tex_x)
			* tex->bytes_per_pixel;
		my_mlx_pixel_put(raycast, x, y, color_validation(tex, draw));
		y++;
	}
}

void	init_values(t_draw *draw, t_raycast *raycast, int x)
{
	draw->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	draw->ray_dir_x = raycast->dir_x + raycast->plane_x * draw->camera_x;
	draw->ray_dir_y = raycast->dir_y + raycast->plane_y * draw->camera_x;
	draw->map_x = (int)raycast->pos_x;
	draw->map_y = (int)raycast->pos_y;
	draw->delta_dist_x = fabs(1 / draw->ray_dir_x);
	draw->delta_dist_y = fabs(1 / draw->ray_dir_y);
}

mlx_texture_t	*somethings(t_draw *draw, t_raycast *raycast)
{
	mlx_texture_t	*tex;

	tex = raycast->wall_textures[draw->tex_num];
	if (draw->side == 0)
		draw->wall_x = raycast->pos_y + draw->perp_wall_dist * draw->ray_dir_y;
	else
		draw->wall_x = raycast->pos_x + draw->perp_wall_dist * draw->ray_dir_x;
	draw->wall_x -= floor(draw->wall_x);
	draw->tex_x = (int)(draw->wall_x * (double)tex->width);
	if (draw->side == 0 && draw->ray_dir_x > 0)
		draw->tex_x = tex->width - draw->tex_x - 1;
	if (draw->side == 1 && draw->ray_dir_y < 0)
		draw->tex_x = tex->width - draw->tex_x - 1;
	draw->step = 1.0 * tex->height / draw->line_height;
	draw->tex_pos = (draw->draw_start - WINDOW_HEIGHT / 2 + draw->line_height
			/ 2) * draw->step;
	return (tex);
}

void	draw_calculations(t_draw *draw, t_raycast *raycast)
{
	if (draw->side == 0)
		draw->perp_wall_dist = (draw->map_x - raycast->pos_x + (1
					- draw->step_x) / 2) / draw->ray_dir_x;
	else
		draw->perp_wall_dist = (draw->map_y - raycast->pos_y + (1
					- draw->step_y) / 2) / draw->ray_dir_y;
	draw->line_height = (int)(WINDOW_HEIGHT / draw->perp_wall_dist);
	draw->draw_start = -draw->line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw->draw_end >= WINDOW_HEIGHT)
		draw->draw_end = WINDOW_HEIGHT - 1;
	draw->tex_num = get_wall_texture(draw->side, draw->ray_dir_x,
			draw->ray_dir_y);
}

void	draw_walls(t_raycast *raycast)
{
	int				x;
	mlx_texture_t	*tex;
	t_draw			*draw;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		tex = NULL;
		draw = ft_calloc(1, sizeof(t_draw));
		if (!draw)
			return ;
		init_values(draw, raycast, x);
		check_somethings1(draw, raycast);
		check_somethings2(draw, raycast);
		draw_calculations(draw, raycast);
		tex = somethings(draw, raycast);
		draw_pixels(draw, tex, raycast, x);
		x++;
		if (draw)
		{
			free(draw);
			draw = NULL;
		}
	}
}
