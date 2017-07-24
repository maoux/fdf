/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_free_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 22:40:44 by heynard           #+#    #+#             */
/*   Updated: 2017/06/03 14:04:05 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void			fdf_free_split(char **split)
{
	int			i;

	i = 0;
	if (split && *split)
	{
		while (split[i] != NULL)
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}

void			fdf_free_tab(t_point **tab, int end)
{
	int			i;

	i = 0;
	if (tab)
	{
		while (i < end)
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void			fdf_free_env(t_env *env)
{
	int			i;

	if (env)
	{
		if (env->tab)
			fdf_free_tab(env->tab, env->j);
		if (env->image)
			mlx_destroy_image(env->mlx_ptr, env->image);
		if (env->mlx_ptr)
			free(env->mlx_ptr);
		if (env->mlx_win)
			free(env->mlx_win);
		if (env->param_to_free)
			free(env->param_to_free);
		free(env);
	}
}
