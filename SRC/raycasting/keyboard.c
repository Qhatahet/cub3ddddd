/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:20:51 by oalananz          #+#    #+#             */
/*   Updated: 2025/08/14 15:57:08 by oalananz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_left_right(t_raycast *raycast, double move_speed)
{
	double	perp_x;
	double	perp_y;

	if (mlx_is_key_down(raycast->mlx, MLX_KEY_D))
	{
		perp_x = -raycast->dir_y;
		perp_y = raycast->dir_x;
		if (!is_wall(raycast->game, (int)(raycast->pos_x + perp_x * move_speed),
			(int)raycast->pos_y))
			raycast->pos_x += perp_x * move_speed;
		if (!is_wall(raycast->game, (int)raycast->pos_x, (int)(raycast->pos_y
				+ perp_y * move_speed)))
			raycast->pos_y += perp_y * move_speed;
	}
	if (mlx_is_key_down(raycast->mlx, MLX_KEY_A))
	{
		perp_x = raycast->dir_y;
		perp_y = -raycast->dir_x;
		if (!is_wall(raycast->game, (int)(raycast->pos_x + perp_x * move_speed),
			(int)raycast->pos_y))
			raycast->pos_x += perp_x * move_speed;
		if (!is_wall(raycast->game, (int)raycast->pos_x, (int)(raycast->pos_y
				+ perp_y * move_speed)))
			raycast->pos_y += perp_y * move_speed;
	}
}

void	move_player(t_raycast *raycast, double move_speed)
{
	if (mlx_is_key_down(raycast->mlx, MLX_KEY_W))
	{
		if (!is_wall(raycast->game, (int)(raycast->pos_x + raycast->dir_x
				* move_speed), (int)raycast->pos_y))
			raycast->pos_x += raycast->dir_x * move_speed;
		if (!is_wall(raycast->game, (int)raycast->pos_x, (int)(raycast->pos_y
				+ raycast->dir_y * move_speed)))
			raycast->pos_y += raycast->dir_y * move_speed;
	}
	if (mlx_is_key_down(raycast->mlx, MLX_KEY_S))
	{
		if (!is_wall(raycast->game, (int)(raycast->pos_x - raycast->dir_x
				* move_speed), (int)raycast->pos_y))
			raycast->pos_x -= raycast->dir_x * move_speed;
		if (!is_wall(raycast->game, (int)raycast->pos_x, (int)(raycast->pos_y
				- raycast->dir_y * move_speed)))
			raycast->pos_y -= raycast->dir_y * move_speed;
	}
	move_left_right(raycast, move_speed);
}

void	rotate_left(t_raycast *raycast, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	if (mlx_is_key_down(raycast->mlx, MLX_KEY_LEFT))
	{
		old_dir_x = raycast->dir_x;
		raycast->dir_x = raycast->dir_x * cos(-rot_speed) - raycast->dir_y
			* sin(-rot_speed);
		raycast->dir_y = old_dir_x * sin(-rot_speed) + raycast->dir_y
			* cos(-rot_speed);
		old_plane_x = raycast->plane_x;
		raycast->plane_x = raycast->plane_x * cos(-rot_speed) - raycast->plane_y
			* sin(-rot_speed);
		raycast->plane_y = old_plane_x * sin(-rot_speed) + raycast->plane_y
			* cos(-rot_speed);
	}
}

void	rotate_player(t_raycast *raycast, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	if (mlx_is_key_down(raycast->mlx, MLX_KEY_RIGHT))
	{
		old_dir_x = raycast->dir_x;
		raycast->dir_x = raycast->dir_x * cos(rot_speed) - raycast->dir_y
			* sin(rot_speed);
		raycast->dir_y = old_dir_x * sin(rot_speed) + raycast->dir_y
			* cos(rot_speed);
		old_plane_x = raycast->plane_x;
		raycast->plane_x = raycast->plane_x * cos(rot_speed) - raycast->plane_y
			* sin(rot_speed);
		raycast->plane_y = old_plane_x * sin(rot_speed) + raycast->plane_y
			* cos(rot_speed);
	}
	rotate_left(raycast, rot_speed);
}

void	key_callback(void *param)
{
	t_raycast	*raycast;
	double		move_speed;
	double		rot_speed;

	raycast = (t_raycast *)param;
	move_speed = 0.08;
	rot_speed = 0.03;
	move_player(raycast, move_speed);
	rotate_player(raycast, rot_speed);
	if (mlx_is_key_down(raycast->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(raycast->mlx);
}
