/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_min_max.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 13:25:05 by heynard           #+#    #+#             */
/*   Updated: 2017/06/03 14:01:59 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void			fdf_get_min_max(t_env *env)
{
	int			elem;
	int			i;
	int			j;

	j = 0;
	elem = 0;
	env->med = 0;
	while (j < env->height)
	{
		i = 0;
		while (i < env->width)
		{
			env->med += env->tab[j][i].z;
			if (env->tab[j][i].z < env->min)
				env->min = env->tab[j][i].z;
			if (env->tab[j][i].z > env->max)
				env->max = env->tab[j][i].z;
			i++;
			elem++;
		}
		j++;
	}
	env->med /= elem;
}

int				fdf_alt_factor(t_env *env)
{
	return (2);
}
