/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qais <qais@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:45:40 by qhatahet          #+#    #+#             */
/*   Updated: 2025/09/01 01:50:46 by qais             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_map_extention(char *map)
{
	char	*str;
	int		flag;

	str = ft_strrchr(map, '.');
	flag = 0;
	if (str)
	{
		if (!ft_strcmp(str, ".cub"))
			flag = 0;
		else
		{
			printf(RED"ERROR"WH"\nUSAGE: ./cub3d map.cub\n");
			flag = 1;
		}
	}
	else
	{
		printf(RED"ERROR"WH"\nUSAGE: ./cub3d map.cub\n");
		flag = 1;
	}
	return (flag);
}

void	init_game_protection(t_game *game)
{
	if (!game->map->utils)
	{
		clean_game(game);
		exit(EXIT_FAILURE);
	}
	if (!game->map->ceiling)
	{
		clean_game(game);
		exit(EXIT_FAILURE);
	}
	if (!game->map->floor)
	{
		clean_game(game);
		exit(EXIT_FAILURE);
	}
}

void	init_utils_flag(t_game *game)
{
	game->map->utils->flag->c = 0;
	game->map->utils->flag->f = 0;
	game->map->utils->flag->e = 0;
	game->map->utils->flag->w = 0;
	game->map->utils->flag->s = 0;
	game->map->utils->flag->n = 0;
}

void	init_game(t_game *game)
{
	game->map = ft_calloc (1, sizeof(t_map));
	game->map->utils = ft_calloc(1, sizeof(t_map_utils));
	game->map->ceiling = ft_calloc(1, sizeof(t_colors));
	game->map->floor = ft_calloc(1, sizeof(t_colors));
	init_game_protection(game);
	game->map->utils->flag = ft_calloc(1, sizeof(t_flag));
	if (!game->map->utils->flag)
	{
		clean_game(game);
		exit(EXIT_FAILURE);
	}
	init_utils_flag(game);
	game->player = ft_calloc(1, sizeof(t_player));
	if (!game->player)
	{
		clean_game(game);
		exit(EXIT_FAILURE);
	}
	init_map(game);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		printf(RED"ERROR"WH"\nUSAGE: ./cub3d map.cub\n");
		return (1);
	}
	if (check_map_extention(argv[1]))
		return (1);
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (1);
	game->map_name = ft_strdup(argv[1]);
	if (!game->map_name)
	{
		clean_game(game);
		return (1);
	}
	init_game(game);
	render(game);
	// clean_game(game);
	return (0);
}

