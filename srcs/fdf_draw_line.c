/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 16:36:19 by heynard           #+#    #+#             */
/*   Updated: 2017/06/05 15:55:57 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int		fdf_color(int z1, int z2, int max)
{
	if (((z1 + z2) / 2) > (max / 2))
		return (WHITE);
	else if (((z1 + z2) / 2) == 0)
		return (GREEN);
	else if (((z1 + z2) / 2) < 0)
		return (BLUE);
	else
		return (BROWN);
}

static void		fdf_draw_line_v(t_env *env, t_point a, int color)
{
	int			error;
	int			i;

	error = env->draw.dx / 2;
	i = 0;
	while (++i <= env->draw.dx)
	{
		a.px += env->draw.xinc;
		error += env->draw.dy;
		if (error >= env->draw.dx)
		{
			error -= env->draw.dx;
			a.py += env->draw.yinc;
		}
		if (a.px < env->width_s && a.px > 0 && a.py < env->height_s && a.py > 0)
			fdf_pixel_put(env, a.px, a.py, color);
	}
}

static void		fdf_draw_line_h(t_env *env, t_point a, int color)
{
	int			error;
	int			i;

	error = env->draw.dy / 2;
	i = 0;
	while (++i <= env->draw.dy)
	{
		a.py += env->draw.yinc;
		error += env->draw.dx;
		if (error >= env->draw.dy)
		{
			error -= env->draw.dy;
			a.px += env->draw.xinc;
		}
		if (a.px < env->width_s && a.px > 0 && a.py < env->height_s && a.py > 0)
			fdf_pixel_put(env, a.px, a.py, color);
	}
}

void			fdf_draw_line(t_env *env, t_point a, t_point b, int color)
{
	env->draw.dx = b.px - a.px;
	env->draw.dy = b.py - a.py;
	env->draw.xinc = (env->draw.dx) > 0 ? 1 : -1;
	env->draw.yinc = (env->draw.dy) > 0 ? 1 : -1;
	env->draw.dx = ft_abs(env->draw.dx);
	env->draw.dy = ft_abs(env->draw.dy);
	color = fdf_color(a.z, b.z, env->max);
	if (a.px < env->width_s && a.px > 0 && a.py < env->height_s && a.py > 0)
		fdf_pixel_put(env, a.px, a.py, color);
	if (env->draw.dx > env->draw.dy)
		fdf_draw_line_v(env, a, color);
	else
		fdf_draw_line_h(env, a, color);
}
