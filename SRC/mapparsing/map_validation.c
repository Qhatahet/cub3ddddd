/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qais <qais@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 09:20:23 by qhatahet          #+#    #+#             */
/*   Updated: 2025/08/30 02:36:28 by qais             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_existance(t_game *game)
{
	game->map->map_fd = open(game->map_name, O_RDONLY);
	if (game->map->map_fd == -1)
	{
		printf(RED"ERROR\n"RESET"no such map\n");
		clean_game(game);
		exit(EXIT_FAILURE);
	}
}

static void	validate_line(char *str, int *flag)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] && (str[i] == '1' || str[i] == '0'
			|| str[i] == '\t' || str[i] == ' ' || str[i] == '\n'))
	{
		if (str[i] == '1' || str[i] == '0')
		{
			(*flag) = 1;
			return ;
		}
		else
		{
			(*flag) = -1;
		}
		i++;
	}
	if (str[i])
		(*flag) = 0;
}

static void	is_empty(t_game *game, int *i, int *flag)
{
	if ((*flag) == 1)
		return ;
	while (game->map->fd[(*i)] && (*flag) == -1)
	{
		(*i)++;
		validate_line(game->map->fd[(*i)], flag);
		if ((*flag) == 1)
		{
			printf(RED"Error"WH"\nsomething wrong in the map\n");
			clean_game(game);
			exit(EXIT_FAILURE);
		}
	}
}

void	check_map_lines(t_game *game)
{
	int	i;
	int	flag;

	i = game->map->utils->m_start;
	flag = -1;
	while (game->map->fd[i])
	{
		validate_line(game->map->fd[i], &flag);
		if (flag == 1)
		{
			i++;
			validate_line(game->map->fd[i], &flag);
			is_empty(game, &i, &flag);
		}
		if (flag == 0)
		{
			printf(RED"Error"WH"\nextra exlement in file\n");
			clean_game(game);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
