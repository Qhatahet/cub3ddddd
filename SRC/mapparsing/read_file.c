/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qais <qais@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 09:31:21 by qhatahet          #+#    #+#             */
/*   Updated: 2025/09/17 02:04:54 by qais             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	recorrect_width(t_game *game)
{
	if (game->map->utils->width < 8)
		game->map->utils->width = sizeof(char *);
}

void	count_file_lines(t_game *game)
{
	char		*line;
	int			fd;
	t_map_utils	*utils;

	utils = game->map->utils;
	fd = open (game->map_name, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
	{
		printf(RED"Error"WH"\nempty file\n");
		close(fd);
		clean_game(game);
		exit(EXIT_FAILURE);
	}
	utils->width = ft_strlen(line);
	while (line != NULL)
	{
		utils->size++;
		if (utils->width < (int)ft_strlen(line))
			utils->width = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void	read_file(t_game *game)
{
	t_map_utils	*utils;
	char		*line;
	int			i;

	i = 0;
	recorrect_width(game);
	utils = game->map->utils;
	game->map->fd = ft_calloc(utils->size + 1, utils->width);
	if (!game->map->fd)
		exit(EXIT_FAILURE);
	line = get_next_line(game->map->map_fd);
	while (line != NULL)
	{
		game->map->fd[i] = ft_strdup(line);
		if (!game->map->fd[i])
			exit(EXIT_FAILURE);
		i++;
		free(line);
		line = get_next_line(game->map->map_fd);
	}
	game->map->fd[i] = NULL;
	check_file_elements(game);
}
