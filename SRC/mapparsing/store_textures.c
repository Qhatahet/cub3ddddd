/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:20:47 by qhatahet          #+#    #+#             */
/*   Updated: 2025/08/29 17:55:33 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_textures(t_game *game)
{
	game->map->textures = ft_calloc(1, sizeof(t_textures));
	game->map->textures->ea = NULL;
	game->map->textures->no = NULL;
	game->map->textures->we = NULL;
	game->map->textures->so = NULL;
	game->map->textures->c = NULL;
	game->map->textures->f = NULL;
}

void	clean_textures(t_game *game)
{
	t_textures	*textures;

	textures = game->map->textures;
	textures->no = ft_strtrim(textures->no, " \t\n");
	textures->ea = ft_strtrim(textures->ea, " \t\n");
	textures->we = ft_strtrim(textures->we, " \t\n");
	textures->so = ft_strtrim(textures->so, " \t\n");
	check_specifier(game);
	check_texture_path(game);
	if ((ft_strchr(textures->so, ' ') && ft_strchr(textures->ea, ' ')
			&& ft_strchr(textures->no, ' ') && ft_strchr(textures->we, ' '))
		|| (ft_strchr(textures->so, '\t') && ft_strchr(textures->ea, '\t')
			&& ft_strchr(textures->no, '\t') && ft_strchr(textures->we, '\t')))
	{
		textures->so = textures_path(textures->so);
		textures->no = textures_path(textures->no);
		textures->ea = textures_path(textures->ea);
		textures->we = textures_path(textures->we);
	}
	else
	{
		printf("there is no texture specifier\n");
		clean_game (game);
		exit(EXIT_FAILURE);
	}
}

void	split_texture_protection(t_game *game)
{
	if (!game->map->textures->no)
	{
		clean_game(game);
		exit(EXIT_FAILURE);
	}
	if (!game->map->textures->so)
	{
		clean_game(game);
		exit(EXIT_FAILURE);
	}
	if (!game->map->textures->we)
	{
		clean_game(game);
		exit(EXIT_FAILURE);
	}
	if (!game->map->textures->ea)
	{
		clean_game(game);
		exit(EXIT_FAILURE);
	}
}

void	split_textures_extention(t_game *game, int i)
{
	if (ft_strchr(game->map->fd[i], 'N'))
		game->map->textures->no = ft_strdup(game->map->fd[i]);
	else if (ft_strchr(game->map->fd[i], 'S'))
		game->map->textures->so = ft_strdup(game->map->fd[i]);
	else if (ft_strchr(game->map->fd[i], 'W'))
		game->map->textures->we = ft_strdup(game->map->fd[i]);
	else if (ft_strchr(game->map->fd[i], 'E'))
		game->map->textures->ea = ft_strdup(game->map->fd[i]);
	else if (ft_strchr(game->map->fd[i], 'C'))
		game->map->textures->c = ft_strdup(game->map->fd[i]);
	else if (ft_strchr(game->map->fd[i], 'F'))
		game->map->textures->f = ft_strdup(game->map->fd[i]);
	else
		check_invalid_specifier(game->map->fd[i], game);
}

void	split_textrues(t_game *game)
{
	int	i;

	i = 0;
	while (game->map->fd[i])
	{
		split_textures_extention(game, i);
		if (check_if_stored(game->map->textures))
			break ;
		i++;
	}
	split_texture_protection(game);
	game->map->utils->m_start = i + 1;
}

int	check_flag(t_game *game)
{
	if (game->map->utils->flag->c > 1)
		return (1);
	if (game->map->utils->flag->f > 1)
		return (1);
	if (game->map->utils->flag->w > 1)
		return (1);
	if (game->map->utils->flag->e > 1)
		return (1);
	if (game->map->utils->flag->s > 1)
		return (1);
	if (game->map->utils->flag->n > 1)
		return (1);
	return (0);
}

void	check_duplicate(t_game *game)
{
	int		i;

	i = 0;
	while (game->map->fd[i])
	{
		if (ft_strnstr(game->map->fd[i], "NO", ft_strlen(game->map->fd[i])))
			game->map->utils->flag->n += 1;
		if (ft_strnstr(game->map->fd[i], "SO", ft_strlen(game->map->fd[i])))
			game->map->utils->flag->s += 1;
		if (ft_strnstr(game->map->fd[i], "WE", ft_strlen(game->map->fd[i])))
			game->map->utils->flag->w += 1;
		if (ft_strnstr(game->map->fd[i], "EA", ft_strlen(game->map->fd[i])))
			game->map->utils->flag->e += 1;
		if (ft_strnstr(game->map->fd[i], "C", ft_strlen(game->map->fd[i])))
			game->map->utils->flag->c += 1;
		if (ft_strnstr(game->map->fd[i], "F", ft_strlen(game->map->fd[i])))
			game->map->utils->flag->f += 1;
		i++;
	}
	if (check_flag(game))
	{
		printf(RED"Error"WH"duplicate in textures");
		clean_game(game);
		exit(EXIT_FAILURE);
	}
}

//void	check_empty_file(t_game *game)
//{
//	int	i;
//	int	fd;
//	char *line;

//	i = 0;
//	fd = open(game->map_name, O_RDONLY);
//	line = get_next_line(fd);
//	while (line)
//	{
//		if (ft_strlen(line) && )
//		free(line);
//		line = get_next_line(fd);
//	}
//}

void	store_textures(t_game *game)
{
	init_textures(game);
	count_file_lines(game);
	//check_empty_file(game);
	read_file(game);
	check_duplicate(game);
	split_textrues(game);
	clean_textures(game);
	validate_colors(game);
	mix_colors(game);
	printf("%s\n", game->map->textures->ea);
	printf("%s\n", game->map->textures->we);
	printf("%s\n", game->map->textures->so);
	printf("%s\n", game->map->textures->no);
	printf("%i %i %i\n", game->map->floor->r, game->map->floor->g, game->map->floor->b);
	printf("%i %i %i\n", game->map->ceiling->r, game->map->ceiling->g, game->map->ceiling->b);
}
