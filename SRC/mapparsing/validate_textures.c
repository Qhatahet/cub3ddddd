/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 08:30:32 by qhatahet          #+#    #+#             */
/*   Updated: 2025/08/15 19:01:26 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_invalid_specifier(char *str, t_game *game)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		else
		{
			printf(RED"ERROR"WH"\ninvalid char\n");
			clean_game(game);
			exit(EXIT_FAILURE);
		}
	}
}

void	check_no(t_game *game)
{
	if (!ft_strncmp(game->map->textures->no, "NO ", 3)
		|| !ft_strncmp(game->map->textures->no, "NO\t", 3))
		return ;
	else
	{
		printf(RED"ERROR"WH"\ntextures specifier should be: NO, WE, SO, EA\n");
		clean_game (game);
		exit(EXIT_FAILURE);
	}
}

void	check_so(t_game *game)
{
	if (!ft_strncmp(game->map->textures->so, "SO ", 3)
		|| !ft_strncmp(game->map->textures->so, "SO\t", 3))
		return ;
	else
	{
		printf(RED"ERROR"WH"\ntextures specifier should be: NO, WE, SO, EA\n");
		clean_game (game);
		exit(EXIT_FAILURE);
	}
}

void	check_ea(t_game *game)
{
	if (!ft_strncmp(game->map->textures->ea, "EA ", 3)
		|| !ft_strncmp(game->map->textures->ea, "EA\t", 3))
		return ;
	else
	{
		printf(RED"ERROR"WH"\ntextures specifier should be: NO, WE, SO, EA\n");
		clean_game (game);
		exit(EXIT_FAILURE);
	}
}

void	check_we(t_game *game)
{
	if (!ft_strncmp(game->map->textures->we, "WE ", 3)
		|| !ft_strncmp(game->map->textures->we, "WE\t", 3))
		return ;
	else
	{
		printf(RED"ERROR"WH"\ntextures specifier should be: NO, WE, SO, EA\n");
		clean_game (game);
		exit(EXIT_FAILURE);
	}
}

void	check_specifier(t_game *game)
{
	check_no(game);
	check_so(game);
	check_we(game);
	check_ea(game);
}

static void	check_path(char *str, t_game *game)
{
	int	i;
	int	word_count;

	(void)game;
	i = 0;
	word_count = 0;
	while (str[i])
	{
		while (str[i] && (str[i] != ' ' && str[i] != '\t'))
			i++;
		word_count++;
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
	}
	if (word_count != 2)
	{
		printf(RED"ERROR"WH"\nwrong texture\n");
		clean_game(game);
		exit(EXIT_FAILURE);
	}
}

void	check_texture_path(t_game *game)
{
	check_path(game->map->textures->no, game);
	check_path(game->map->textures->we, game);
	check_path(game->map->textures->ea, game);
	check_path(game->map->textures->so, game);
}
