/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_textures_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 08:27:52 by qhatahet          #+#    #+#             */
/*   Updated: 2025/08/13 08:29:49 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*textures_path(char *str)
{
	int		i;
	int		j;
	char	*trimmed;

	i = 2;
	j = 0;
	trimmed = malloc (ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		else
		{
			trimmed[j] = str[i];
			i++;
			j++;
		}
	}
	trimmed[j] = '\0';
	free(str);
	return (trimmed);
}

int	check_if_stored(t_textures *textures)
{
	if (!textures->ea)
		return (0);
	if (!textures->we)
		return (0);
	if (!textures->so)
		return (0);
	if (!textures->no)
		return (0);
	if (!textures->c)
		return (0);
	if (!textures->f)
		return (0);
	return (1);
}

void	count_content(char **arr, t_game *game)
{
	int	i;

	(void)game;
	i = 0;
	while (arr[i])
		i++;
	if (i != 2)
	{
		printf("something wrong with the textures\n");
		clean_game(game);
		exit(EXIT_FAILURE);
	}
	ft_free_2d(arr);
	arr = NULL;
}
