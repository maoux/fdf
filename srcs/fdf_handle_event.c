/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_handle_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 21:47:41 by heynard           #+#    #+#             */
/*   Updated: 2017/06/03 14:03:20 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int			fdf_key_event(int keycode, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (keycode == KEY_ESC)
	{
		fdf_free_env(env);
		exit(1);
	}
	if (keycode == KEY_W || keycode == KEY_UP)
	{
		if (env->scale - 10 > 0)
			env->scale -= 10;
		else
			return (0);
		mlx_destroy_image(env->mlx_ptr, env->image);
		fdf_draw_tab(env);
	}
	if (keycode == KEY_S || keycode == KEY_DOWN)
	{
		env->scale += 10;
		mlx_destroy_image(env->mlx_ptr, env->image);
		fdf_draw_tab(env);
	}
	return (0);
}
