/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:21:16 by oalananz          #+#    #+#             */
/*   Updated: 2025/08/14 18:46:41 by oalananz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_mouse(t_raycast *raycast, double rot_speed, double delta_x)
{
	double	old_plane_x;
	double	old_dir_x;
	double	angle;

	angle = delta_x * rot_speed;
	old_dir_x = raycast->dir_x;
	raycast->dir_x = raycast->dir_x * cos(angle) - raycast->dir_y * sin(angle);
	raycast->dir_y = old_dir_x * sin(angle) + raycast->dir_y * cos(angle);
	old_plane_x = raycast->plane_x;
	raycast->plane_x = raycast->plane_x * cos(angle)
		- raycast->plane_y * sin(angle);
	raycast->plane_y = old_plane_x * sin(angle) + raycast->plane_y * cos(angle);
}

void	mouse_move_callback(double xpos, double ypos, void *param)
{
	static double	last_x = -1;
	double			rot_speed;
	double			delta_x;
	t_raycast		*raycast;

	(void)ypos;
	rot_speed = 0.01;
	raycast = (t_raycast *)param;
	if (last_x < 0)
		last_x = xpos;
	delta_x = xpos - last_x;
	last_x = xpos;
	if (fabs(delta_x) > 0.1)
		rotate_mouse(raycast, rot_speed, delta_x);
}
