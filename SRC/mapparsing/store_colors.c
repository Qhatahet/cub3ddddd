/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:49:59 by qhatahet          #+#    #+#             */
/*   Updated: 2025/08/29 19:33:52 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	store_floor(int arr[3], t_game *game)
{
	int	flag;

	(void)game;
	flag = 0;
	if (arr[0] && arr[0] <= 255)
		game->map->floor->r = arr[0];
	else
		flag = 1;
	if (arr[1] && arr[1] <= 255)
		game->map->floor->g = arr[1];
	else
		flag = 1;
	//printf("%i\n", arr[2]);
	if (arr[2] <= 255)
		game->map->floor->b = arr[2];
	else
		flag = 1;
	if (flag)
	{
		printf(RED"ERROR"WH"\ncolor bigger than 255\n");
		clean_game(game);
		exit(EXIT_FAILURE);
	}
}

static void	store_ceiling(int arr[3], t_game *game)
{
	int	flag;

	(void)game;
	flag = 0;
	if (arr[0] <= 255)
		game->map->ceiling->r = arr[0];
	else
		flag = 1;
	if (arr[1] <= 255)
		game->map->ceiling->g = arr[1];
	else
		flag = 1;
	if (arr[2] <= 255)
		game->map->ceiling->b = arr[2];
	else
		flag = 1;
	if (flag)
	{
		printf(RED"ERROR"WH"\ncolor bigger than 255\n");
		clean_game(game);
		exit(EXIT_FAILURE);
	}
}

void	store_colors(int arr[3], t_game *game, char type)
{
	if (type == 'C')
		store_ceiling(arr, game);
	else if (type == 'F')
		store_floor(arr, game);
}
