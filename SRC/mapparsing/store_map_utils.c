/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qais <qais@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 09:15:41 by qhatahet          #+#    #+#             */
/*   Updated: 2025/09/17 02:02:58 by qais             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_player_pos(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map->map[i])
	{
		j = 0;
		while (game->map->map[i][j])
		{
			if (game->map->map[i][j] == 'N' || game->map->map[i][j] == 'S'
				|| game->map->map[i][j] == 'E' || game->map->map[i][j] == 'W')
			{
				game->player->row = i;
				game->player->column = j;
				game->player->c = game->map->map[i][j];
				return ;
			}
			j++;
		}
		i++;
	}
}

void	count_map_lines(t_game *game)
{
	int	i;

	i = game->map->utils->m_start;
	while (game->map->fd[i]
		&& (ft_strchr(game->map->fd[i], '1')
			|| ft_strchr(game->map->fd[i], '0')))
	{
		i++;
		game->map->utils->m_size++;
	}
}

void	allocate_map(t_game *game)
{
	game->map->map = ft_calloc(game->map->utils->m_size + 1, sizeof(char *));
	if (!game->map->map)
	{
		clean_game(game);
		exit(EXIT_FAILURE);
	}
}
