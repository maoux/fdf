/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 18:02:56 by heynard           #+#    #+#             */
/*   Updated: 2017/06/05 16:40:01 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int		fdf_calc(t_env *env, int n, int iso)
{
	if (n == 1)
	{
		return ((env->width_s / 2 - ((env->width - 1) -
				(env->height - 1)) / 2 * iso / 2));
	}
	if (n == 2)
	{
		return ((env->height_s / 2 - ((env->width - 1) +
				(env->height - 1)) / 2 * iso / 2));
	}
	if (n == 3)
		return (((env->tmpx - env->tmpy) * ((iso / 2))));
	if (n == 4)
		return (((env->tmpx + env->tmpy) * (iso / 2)));
	return (0);
}

static void		fdf_project_point(t_env *env)
{
	int			tile_w;
	int			tile_h;
	int			iso;
	int			i;
	int			j;

	j = -1;
	tile_w = (env->width_s - env->scale) / (env->width - 1);
	tile_h = (env->height_s - env->scale / 2) / (env->height - 1);
	tile_w = tile_w < 4 ? 4 : tile_w;
	tile_h = tile_h < 4 ? 4 : tile_h;
	iso = (tile_w + tile_h) / 2;
	while (++j < env->height)
	{
		i = 0;
		while (i < env->width)
		{
			env->tmpx = env->tab[j][i].x;
			env->tmpy = env->tab[j][i].y;
			env->tab[j][i].px = fdf_calc(env, 1, iso) + fdf_calc(env, 3, iso);
			env->tab[j][i].py = fdf_calc(env, 2, iso) + fdf_calc(env, 4, iso)
								- (env->tab[j][i].z * fdf_alt_factor(env));
			i++;
		}
	}
}

static void		fdf_draw_iso(t_env *env, int i, int j)
{
	fdf_draw_line(env, env->tab[j][i], env->tab[j][i + 1], 0);
	fdf_draw_line(env, env->tab[j][i], env->tab[j + 1][i], 0);
	fdf_draw_line(env, env->tab[j + 1][i], env->tab[j + 1][i + 1], 0);
	fdf_draw_line(env, env->tab[j][i + 1], env->tab[j + 1][i + 1], 0);
}

int				fdf_heightofmap(int fd, char *line)
{
	int			height;

	height = 0;
	while (get_next_line(fd, &line))
	{
		height++;
		free(line);
	}
	return (height);
}

void			fdf_draw_tab(t_env *env)
{
	int			i;
	int			j;

	env->image = mlx_new_image(env->mlx_ptr, env->width_s, env->height_s);
	fdf_project_point(env);
	if (env->image)
	{
		j = 0;
		while (j < env->height - 1)
		{
			i = 0;
			while (i < env->width - 1)
			{
				fdf_draw_iso(env, i, j);
				i++;
			}
			j++;
		}
		mlx_put_image_to_window(env->mlx_ptr, env->mlx_win, env->image, 0, 0);
	}
}
