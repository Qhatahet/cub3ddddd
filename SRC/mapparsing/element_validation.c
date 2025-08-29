/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 09:18:56 by qhatahet          #+#    #+#             */
/*   Updated: 2025/08/29 18:21:00 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	else
		return (0);
}

int	check_element(char *str)
{
	if (ft_strchr(str, 'N'))
		return (1);
	else if (ft_strchr(str, 'E'))
		return (1);
	else if (ft_strchr(str, 'W'))
		return (1);
	else if (ft_strchr(str, 'S'))
		return (1);
	else if (ft_strchr(str, 'F'))
		return (1);
	else if (ft_strchr(str, 'C'))
		return (1);
	return (0);
}

void	check_file_elements(t_game *game)
{
	size_t	i;
	size_t	j;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	while (game->map->fd[i])
	{
		while (j < ft_strlen(game->map->fd[i]) && (game->map->fd[i][j] == ' '
			|| game->map->fd[i][j] == '\t'))
			j++;
		if (j < ft_strlen(game->map->fd[i]) && (game->map->fd[i][j] == '1'
			|| game->map->fd[i][j] == '0'))
			break ;
		count += check_element(game->map->fd[i]);
		i++;
	}
	if (count > 6)
	{
		printf(RED"Error"WH"\nextra element in the file\n");
		clean_game(game);
		exit(EXIT_FAILURE);
	}
}

void	validate_element(t_game *game, char c)
{
	if (c != '\t' && c != ' ' && c != '1' && c != '0'
		&& c != 'N' && c != 'S' && c != 'W' && c != 'E'
		&& c != '\n')
	{
		printf(RED"Error"WH"\ninvalid element in map\n");
		clean_game(game);
		exit(EXIT_FAILURE);
	}
}

void	validate_map_elements(t_game *game)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (game->map->map[i])
	{
		j = 0;
		while (game->map->map[i][j])
		{
			validate_element(game, game->map->map[i][j]);
			flag += count_player(game->map->map[i][j]);
			j++;
		}
		i++;
	}
	if (flag != 1)
	{
		printf(RED"Error"WH"\nsomething wrong with the player\n");
		clean_game(game);
		exit(EXIT_FAILURE);
	}
}
