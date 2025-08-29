/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:44:05 by qhatahet          #+#    #+#             */
/*   Updated: 2025/08/15 16:16:59 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
#include "../libft/libft.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
}	t_textures;

typedef struct s_colors
{
	int	r;
	int	g;
	int	b;
	uint32_t mixed;
}	t_colors;

typedef struct s_player
{
	float		row;
	float		column;
	char	c;
}		t_player;

typedef struct s_flag
{
	int	n;
	int	s;
	int	e;
	int	w;
	int	c;
	int	f;	
}		t_flag;

typedef struct s_map_utils
{
	int		width;
	int		size;
	int		m_start;
	int		m_size;
	t_flag	*flag;
}		t_map_utils;

typedef struct s_map
{
	char		**map;
	char		**fd;
	char		**ff_map;
	int			map_fd;
	int			colors[4];
	t_map_utils	*utils;
	t_colors	*floor;
	t_colors	*ceiling;
	t_textures	*textures;		
}				t_map;

typedef struct s_game
{
	t_map		*map;
	char		*map_name;
	t_player	*player;
}		t_game;

typedef struct s_draw
{
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	int map_x;
	int map_y;
	double delta_dist_x;
	double delta_dist_y;
	double perp_wall_dist;
    int step_x;
	int step_y;
    double side_dist_x;
	double side_dist_y;
    int hit;
	int side;
	int line_height;
	int draw_start;
	int draw_end;
	int tex_num;
	int tex_x;
	int tex_y;
	int index;
	double tex_pos;
	double step;
	double wall_x;
	
}	t_draw;

typedef struct s_raycast
{
    void *mlx;
    mlx_image_t *img;
    double pos_x;
	double pos_y;
    double dir_x;
	double dir_y;
    double plane_x;
	double plane_y;
	mlx_texture_t *wall_textures[4];	
    t_game *game;
} t_raycast;


void	count_colors(t_game *game, char *str);
int is_wall(t_game *game, int x, int y);
char get_map_cell(t_game *game, int x, int y);
void my_mlx_pixel_put(t_raycast *raycast, int x, int y, uint32_t color);
void draw_floor_ceiling(t_raycast *raycast);
int get_wall_texture(int side, double ray_dir_x, double ray_dir_y);
void draw_walls(t_raycast *raycast);
void key_callback( void *param);
void mouse_move_callback(double xpos, double ypos, void *param);
int render(t_game *game);
void	clean_game(t_game *game);
void clean_up(t_raycast *raycast);
void	check_somethings1(t_draw *draw, t_raycast *raycast);
void	check_somethings2(t_draw *draw, t_raycast *raycast);
uint32_t	color_validation(mlx_texture_t *tex, t_draw *draw);
int	initialize_mlx(t_raycast *raycast);
void	load_textures(t_raycast *raycast);
void	clean_up(t_raycast *raycast);
void	mix_colors(t_game *game);
void	count_colors(t_game *game, char *str);
void	validate_colors(t_game *game);
void	check_all_digits(t_game *game, char *str, char type);
void	check_non_numeric(char *str, t_game *game);
void	store_colors(int arr[3], t_game *game, char type);
void	clean_game(t_game *game);
void	validate_color_length(char *s, t_game *game);
void	count_column(char *str, t_game *game);
void	validate_colors_number(t_game *game, int color_count);
void	count_colors(t_game *game, char *str);
void	count_column(char *str, t_game *game);
void	store_textures(t_game *game);
void	count_file_lines(t_game *game);
void	read_file(t_game *game);
void	count_content(char **arr, t_game *game);
int		check_if_stored(t_textures *textures);
char	*textures_path(char *str);
void	check_invalid_specifier(char *str, t_game *game);
void	check_specifier(t_game *game);
void	check_texture_path(t_game *game);
void	allocate_map(t_game *game);
void	count_map_lines(t_game *game);
void	check_map_lines(t_game *game);
int		check_element(char *str);
void	check_file_elements(t_game *game);
void	map_existance(t_game *game);
void	validate_map_elements(t_game *game);
void	store_player_pos(t_game *game);
void	init_map(t_game *game);


# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WH "\033[0;37m"
# define RESET "\033[0m"

#endif