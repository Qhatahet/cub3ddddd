/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 09:14:31 by qhatahet          #+#    #+#             */
/*   Updated: 2025/08/29 18:31:39 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	store_map(t_game *game)
{
	int			i;
	t_map_utils	*utils;

	utils = game->map->utils;
	i = utils->m_start;
	while (game->map->fd[i] && !ft_strchr(game->map->fd[i], '1')
		&& !ft_strchr(game->map->fd[i], '0'))
		i++;
	utils->m_start = i;
	count_map_lines(game);
	allocate_map(game);
	i = 0;
	while (game->map->fd[utils->m_start]
		&& i < utils->m_size)
	{
		game->map->map[i] = ft_strdup(game->map->fd[utils->m_start]);
		if (!game->map->map[i])
		{
			clean_game(game);
			exit(EXIT_FAILURE);
		}
		i++;
		utils->m_start++;
	}
	game->map->map[i] = NULL;
}

void	flood_fill_2(t_game *game, int y, int x)
{
	if (y < 0 || x < 0 || y >= game->map->utils->m_size
		|| x >= game->map->utils->width)
	{
		printf(RED"Error"WH"\nthere is a hole in the wall\n");
		ft_free_2d(game->map->ff_map);
		clean_game(game);
		exit(EXIT_FAILURE);
	}
	if (game->map->ff_map[y][x] == '1' || game->map->ff_map[y][x] == '2')
		return ;
	game->map->ff_map[y][x] = '2';
	flood_fill_2(game, y + 1, x);
	flood_fill_2(game, y - 1, x);
	flood_fill_2(game, y, x + 1);
	flood_fill_2(game, y, x - 1);
}

void	flood_fill(t_game *game, int player_y, int player_x)
{
	int	i;
	int	j;

	flood_fill_2(game, player_y, player_x);
	i = 0;
	while (game->map->ff_map[i])
	{
		j = 0;
		while (game->map->ff_map[i][j])
		{
			if (game->map->ff_map[i][j] == '0')
				flood_fill_2(game, i, j);
			j++;
		}
		i++;
	}
}

static void	ff_map(t_game *game)
{
	int	i;

	i = 0;
	game->map->ff_map = ft_calloc(game->map->utils->m_size + 1, sizeof(char *));
	if (!game->map->ff_map)
	{
		clean_game(game);
		exit(EXIT_FAILURE);
	}
	while (game->map->map[i])
	{
		game->map->ff_map[i] = ft_strtrim(ft_strdup(game->map->map[i]), "\n");
		if (!game->map->ff_map[i])
		{
			clean_game(game);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	game->map->ff_map[i] = NULL;
}

static void	check_store_map(t_game *game)
{
	check_map_lines(game);
	store_map(game);
	validate_map_elements(game);
	store_player_pos(game);
	ff_map(game);
	flood_fill(game, game->player->column * 0.5, game->player->row * 0.5);
	if (game->map->ff_map)
		ft_free_2d(game->map->ff_map);
}

void	init_map(t_game *game)
{
	map_existance(game);
	store_textures(game);
	check_store_map(game);
}
