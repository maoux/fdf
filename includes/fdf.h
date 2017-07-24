/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 21:19:46 by heynard           #+#    #+#             */
/*   Updated: 2017/06/05 16:15:39 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define KEY_ESC	53

# define KEY_UP		126
# define KEY_DOWN	125

# define KEY_S		1
# define KEY_W		13

# define BLUE		0x0041FF
# define BROWN		0xAD4F09
# define GREEN		0x25FF50
# define WHITE		0xFFFFFF

# include "../libft/includes/libft.h"
# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

typedef struct	s_point
{
	int			px;
	int			py;
	int			x;
	int			y;
	int			z;
}				t_point;

typedef struct	s_draw
{
	int			error;
	int			xinc;
	int			yinc;
	int			dx;
	int			dy;
}				t_draw;

/*
** structure d'environnement englobant toutes les variables utiles
** tout au long de l'execution
*/

typedef struct	s_env
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		*image;
	t_draw		draw;
	int			width_s;
	int			height_s;
	int			width;
	int			height;
	int			scale;
	t_point		**tab;
	int			j;
	int			tmpx;
	int			tmpy;
	int			min;
	int			max;
	int			med;
	void		*param_to_free;
}				t_env;

/*
** fonctions de gestion de la fenetre et des images
*/

void			fdf_pixel_put(t_env *env, int x, int y, int color);
void			fdf_draw_line(t_env *env, t_point a, t_point b, int color);

/*
** fonctions d'affichage sur le terminal
*/

void			fdf_undifined_error(t_env *env, int fd,
									char **split, char *line);
void			fdf_error_file(t_env *env, int error, char **split, int fd);
void			fdf_error_file_name(t_env *env, char *name, char *line);
void			fdf_error_arg();

/*
** fonctions evenement mlx
*/

int				fdf_key_event(int keycode, void *param);
int				fdf_key_release_event(int keycode, void *param);

/*
** fonctions principales fdf
*/

void			fdf_my_open(t_env *env, int *fd, char *file_name);
void			fdf_parse_map(t_env *env, char *file_name);
void			fdf_get_min_max(t_env *env);
void			fdf_free_tab(t_point **tab, int end);
void			fdf_free_env(t_env *env);
void			fdf_free_split(char **split);
void			fdf_draw_tab(t_env *env);
int				fdf_alt_factor(t_env *env);
int				fdf_heightofmap(int fd, char *line);
void			fdf_free_split(char **split);

#endif
