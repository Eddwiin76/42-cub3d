/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 14:56:46 by tpierre           #+#    #+#             */
/*   Updated: 2020/10/13 16:44:26 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef CUB3D_H
#	define CUB3D_H

#	include "../mlx/mlx.h"
#	include "../libft/libft.h"
#	include "key.h"
#	include <stdlib.h>
#	include <unistd.h>
#	include <fcntl.h>
#	include <math.h>

typedef	enum	e_error
{
	SUCCESS,
	ERROR_TOO_MANY_ARG,
	ERROR_TOO_FEW_ARG,
	ERROR_EXT_FILE,
	ERROR_SAVE_FLAG,
	ERROR_ARG,
	ERROR_MALLOC,
	ERROR_INPUT,
	ERROR_RES,
	ERROR_COLOR,
	ERROR_MAP,
	ERROR_NO_MAP,
	ERROR_MAP_CHAR,
	ERROR_OPEN_FILE,
	ERROR_READ_FILE,
	ERROR_TEXTURE_PATH,
	ERROR_TEXTURE_DUPLICATE,
	ERROR_TEXTURE_EXT,
	ERROR_TEXTURE_LOAD,
	ERROR_RESOLUTION_DUPLICATE,
	ERROR_SPRITE_PATH,
	ERROR_SPRITE_DUPLICATE,
	ERROR_SPRITE_EXT,
	ERROR_NO_R,
	ERROR_NO_NO,
	ERROR_NO_SO,
	ERROR_NO_WE,
	ERROR_NO_EA,
	ERROR_NO_SPRITE,
	ERROR_NO_FLOOR,
	ERROR_FLOOR_DUPLICATE,
	ERROR_NO_CEIL,
	ERROR_CEIL_DUPLICATE,
	ERROR_MAP_NOT_LAST,
	ERROR_UNKNOW_PARAM,
	ERROR_IMG,
	ERROR_MLX,
	ERROR_TOO_MANY_PLAYER,
	ERROR_NO_PLAYER,
	ERROR_PLAYER_IS_AROUND,
	ERROR_MAP_NOT_CLOSE,
	PIXEL_ERROR,
}				t_error;

typedef struct	s_rgb
{
	unsigned int	rgb;
}				t_rgb;

typedef struct	s_img
{
	void	*img_ptr;
	int		*img_data;
	int		bpp;
	int		sl;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct	s_screen
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		windowcreated;
	int		x;
	int		y;
}				t_screen;

typedef struct	s_move
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	strafl;
	int	strafr;
}				t_move;

typedef struct	s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef struct	s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		x;
}				t_ray;

typedef struct	s_texture
{
	t_img	*texture_img;
	double	wall_x;
	double	step;
	double	tex_pos;
	int		tex_x;
	int		tex_y;
	int		color;
	int		y;
}				t_texture;

typedef struct	s_sprite
{
	double	x;
	double	y;
	int		texture;
	double	distance;
}				t_sprite;

typedef struct	s_ray_sprite
{
	t_img	*sp_img;
	double	transform_x;
	double	transform_y;
	int		sp_screen_x;
	int		sp_height;
	int		sp_width;
	int		draw_start_y;
	int		draw_start_x;
	int		draw_end_y;
	int		draw_end_x;
	int		tex_x;
	int		tex_y;
}				t_ray_sprite;

typedef struct	s_validity
{
	int	if_resolution;
	int	if_texture_no;
	int	if_texture_so;
	int	if_texture_we;
	int	if_texture_ea;
	int	if_texture_sprite;
	int	if_sprite;
	int	if_colors_floor;
	int	if_colors_ceil;
	int	if_map_started;
	int	if_map;
}				t_validity;

typedef struct	s_arg
{
	char	*screen;
	char	*line_no;
	char	*line_so;
	char	*line_we;
	char	*line_ea;
	char	*line_s;
	char	*floor;
	char	*ceil;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;

	char	**map;
	int		mapx;
	int		mapy;
	int		ismap;
}				t_arg;

typedef struct	s_player
{
	t_pos	pos;
	double	dir_x;
	double	dir_y;
	char	orientation;
	double	plane_x;
	double	plane_y;
}				t_player;

typedef struct	s_env
{
	t_screen	screen;
	t_img		*img;
	t_img		texture_no;
	t_img		texture_so;
	t_img		texture_we;
	t_img		texture_ea;
	t_img		sprite_env;
	int			fd;
	char		*filename;
	int			save;
	t_arg		arg;
	t_validity	validity;
	t_rgb		floor;
	t_rgb		ceil;
	t_player	player;
	t_move		move;
	t_ray		ray;
	int			error;
	int			**buffer;
	t_sprite	*sprite;
	double		*z_buffer;
}				t_env;

void			ft_save(t_env *tab);
int				ft_run(t_env *tab);
int				ft_key_press(int key, t_env *tab);
int				ft_key_release(int key, t_env *tab);
void			ft_error(t_env *tab, int error);
void			ft_error_arg(int error);
int				ft_exit(t_env *tab);
void			ft_free_arg(t_arg *arg);
void			ft_free_screen(t_screen *screen);
void			ft_free_img(t_env *tab);
void			ft_display(t_env *tab);
void			ft_read(t_env *tab);
int				ft_get_data(t_env *tab, char *line, int *i);
int				ft_get_map(t_env *tab, char *line);
int				ft_parse_path2(t_env *tab, char *line, int *i);
int				ft_parse_path(t_env *tab, char *line, int *i);
void			ft_get_screen(t_env *tab, t_screen *screen, char *line);
void			ft_get_color(t_env *tab, t_rgb *rgb, char *line);
void			ft_check_path2(t_env *tab, char **orientation, char *line);
void			ft_check_player(t_env *tab, char **map, t_player *player);
void			ft_check_player2(t_env *tab);
t_img			*ft_new_image(t_env *env, int width, int height);
void			ft_init(t_env *tab);
void			ft_event(t_env *tab);
void			ft_check_map(t_env *tab, char **map);
void			ft_display_wall(t_env *tab);
void			ft_display_sprite(t_env *tab);
void			ft_check_map_char(t_env *tab, char **map, int if_two);
void			ft_check_map_around(t_env *tab, char **map);
void			ft_draw(t_env *tab);
void			ft_move_up_down(t_env *tab);
void			ft_move_left_rigth(t_env *tab);
void			ft_rotate(t_env *tab, double degree);
void			ft_check_path_s(t_env *tab, char **orientation,
					char *line);
void			ft_free_texture(t_env *tab);

#	define SPEED 0.07
#	define PINK 9961608
#	endif
