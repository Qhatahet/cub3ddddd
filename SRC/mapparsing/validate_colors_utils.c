/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_colors_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qais <qais@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:10:36 by qhatahet          #+#    #+#             */
/*   Updated: 2025/08/30 03:53:53 by qais             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	count_column(char *str, t_game *game)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	count_colors(game, str);
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count > 2)
	{
		printf(RED"ERROR"WH"\nextra column in the colors\n");
		clean_game(game);
		exit(EXIT_FAILURE);
	}
}

void	count_colors(t_game *game, char *str)
{
	int	i;
	int	count_colors;

	i = 1;
	count_colors = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'
				|| str[i] == '\n' || str[i] == ','))
			i++;
		if (str[i] && str[i] == '+')
			i++;
		while (str[i] && ft_isdigit(str[i]))
			i++;
		count_colors++;
	}
	validate_colors_number(game, count_colors);
}

uint32_t	rgb_to_hex(int r, int g, int b, int a)
{
	return (((r & 0xFF) << 24)
		| ((g & 0xFF) << 16)
		| ((b & 0xFF) << 8)
		| (a & 0xFF));
}

void	mix_colors(t_game *game)
{
	t_colors	*floor;
	t_colors	*ceiling;

	floor = game->map->floor;
	ceiling = game->map->ceiling;
	floor->mixed = rgb_to_hex(game->map->floor->r, game->map->floor->g,
			game->map->floor->b, 255);
	ceiling->mixed = rgb_to_hex(game->map->ceiling->r, game->map->ceiling->g,
			game->map->ceiling->b, 255);
}
