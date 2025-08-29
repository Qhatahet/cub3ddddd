/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:50:26 by oalananz          #+#    #+#             */
/*   Updated: 2025/08/29 19:56:07 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_up(t_raycast *raycast)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (raycast->wall_textures[i])
			mlx_delete_texture(raycast->wall_textures[i]);
		i++;
	}
	mlx_delete_image(raycast->mlx, raycast->img);
	mlx_terminate(raycast->mlx);
	if (raycast)
		free(raycast);
}

void	exit_failure(t_raycast *raycast, char *s)
{
	printf(RED"Error"WH"\nFailed to load %s texture\n", s);
	clean_up(raycast);
	exit(EXIT_FAILURE);
}

void	load_textures(t_raycast *raycast)
{
	t_game	*game;

	game = raycast->game;
	raycast->wall_textures[0] = mlx_load_png(game->map->textures->no);
	if (!raycast->wall_textures[0])
		exit_failure(raycast, "north");
	raycast->wall_textures[1] = mlx_load_png(game->map->textures->so);
	if (!raycast->wall_textures[1])
		exit_failure(raycast, "south");
	raycast->wall_textures[2] = mlx_load_png(game->map->textures->we);
	if (!raycast->wall_textures[2])
		exit_failure(raycast, "west");
	raycast->wall_textures[3] = mlx_load_png(game->map->textures->ea);
	if (!raycast->wall_textures[3])
		exit_failure(raycast, "east");
}

int	initialize_mlx(t_raycast *raycast)
{
	raycast->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "3ddd", false);
	if (!raycast->mlx)
	{
		printf("Error: Failed to initialize MLX42\n");
		free(raycast);
		return (-1);
	}
	raycast->img = mlx_new_image(raycast->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!raycast->img)
	{
		printf("Error: Failed to create image\n");
		mlx_terminate(raycast->mlx);
		free(raycast);
		return (-1);
	}
	if (mlx_image_to_window(raycast->mlx, raycast->img, 0, 0) < 0)
	{
		printf("Error: Failed to display image\n");
		mlx_delete_image(raycast->mlx, raycast->img);
		mlx_terminate(raycast->mlx);
		free(raycast);
		return (-1);
	}
	return (0);
}
