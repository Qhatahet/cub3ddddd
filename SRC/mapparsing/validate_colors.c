/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:16:28 by qhatahet          #+#    #+#             */
/*   Updated: 2025/08/29 19:38:57 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_non_numeric(char *str, t_game *game)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) || str[i] == ','
			|| str[i] == ' ' || str[i] == '\t')
			i++;
		else
		{
			printf(RED"ERROR"WH"\nnon numeric element in colors\n");
			clean_game(game);
			exit(EXIT_FAILURE);
		}
	}
}

void	fill_arr(int arr[100])
{
	int	i;

	i = 0;
	while (i < 100)
	{
		arr[i] = -1;
		i++;
	}
}

void	check_all_digits(t_game *game, char *str, char type)
{
	int		i;
	int		j;
	int		y;
	char	*s;
	int		arr[100];

	i = 1;
	y = 0;
	check_non_numeric(str + 1, game);
	fill_arr(arr);
	s = NULL;
	while (str[i])
	{
		while (str[i] && !ft_isdigit(str[i]))
			i++;
		j = i;
		while (str[i] && ft_isdigit(str[i]))
			i++;
		s = ft_substr(str, j, i - j);
		validate_color_length(s, game);
		arr[y] = ft_atoi(s);
		y++;
		free(s);
	}
	store_colors(arr, game, type);
}

void	validate_colors_number(t_game *game, int color_count)
{
	(void)game;
	if (color_count != 3)
	{
		printf(RED"ERROR"WH"\nwrong number of colors\n");
		clean_game(game);
		exit(EXIT_FAILURE);
	}
}

void	validate_color_length(char *s, t_game *game)
{
	(void)game;
	if (!s)
	{
		printf(RED"Error"WH"\nmissing color\n");
		clean_game(game);
		exit(EXIT_FAILURE);
	}
	if ((int)ft_strlen(s) > 3)
	{
		printf(RED"ERROR"WH"\ncolor bigger than 255\n");
		clean_game(game);
		exit(EXIT_FAILURE);
	}
}

void	validate_colors(t_game *game)
{
	game->map->textures->c = ft_strtrim(game->map->textures->c, " \t\n");
	game->map->textures->f = ft_strtrim(game->map->textures->f, " \t\n");
	if ((!ft_strncmp(game->map->textures->f, "F ", 2)
			|| !ft_strncmp(game->map->textures->f, "F\t", 2))
		&& (!ft_strncmp(game->map->textures->c, "C ", 2)
			|| !ft_strncmp(game->map->textures->c, "C\t", 2)))
	{
		check_all_digits(game, game->map->textures->f, 'F');
		check_all_digits(game, game->map->textures->c, 'C');
		count_column(game->map->textures->f, game);
		count_column(game->map->textures->c, game);
	}
	else
	{
		printf(RED"ERROR"WH"\nwrong color format\n");
		clean_game(game);
		exit(EXIT_FAILURE);
	}
}
