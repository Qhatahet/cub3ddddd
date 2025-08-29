/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_clean_up.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 08:34:48 by qhatahet          #+#    #+#             */
/*   Updated: 2025/08/15 17:44:34 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(t_textures *textures)
{
	if (textures->c)
		free (textures->c);
	if (textures->f)
		free (textures->f);
	if (textures->ea)
		free (textures->ea);
	if (textures->we)
		free (textures->we);
	if (textures->so)
		free (textures->so);
	if (textures->no)
		free (textures->no);
	free(textures);
}

void	clean_map(t_map *map)
{
	if (map->textures)
	{
		free_textures(map->textures);
		map->textures = NULL;
	}
	if (map->ceiling)
		free(map->ceiling);
	if (map->floor)
		free (map->floor);
	if (map->map)
	{
		ft_free_2d (map->map);
		map->map = NULL;
	}
	if (map->fd)
		ft_free_2d (map->fd);
	if (map->utils)
	{
		if (map->utils->flag)
			free(map->utils->flag);
		free(map->utils);
	}
	if (map->map_fd != -1)
		close (map->map_fd);
	free (map);
}

void	clean_game(t_game *game)
{
	if (game)
	{
		if (game->map)
		{
			clean_map(game->map);
			game->map = NULL;
		}
		if (game->map_name)
		{
			free(game->map_name);
			game->map_name = NULL;
		}
		if (game->player)
		{
			free(game->player);
			game->player = NULL;
		}
		free(game);
		game = NULL;
	}
}
