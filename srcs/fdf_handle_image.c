/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_handle_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 21:29:23 by heynard           #+#    #+#             */
/*   Updated: 2017/05/29 00:13:55 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void			fdf_pixel_put(t_env *env, int x, int y, int color)
{
	char		*data;
	int			endian;
	int			bpp;
	int			s_l;
	int			i;

	if (env->image)
	{
		data = mlx_get_data_addr(env->image, &bpp, &s_l, &endian);
		i = 0;
		while (i != bpp / 8)
		{
			data[(y * s_l) + (x * (bpp / 8)) + i++] = color % 256;
			color /= 256;
			data[(y * s_l) + (x * (bpp / 8)) + i++] = color % 256;
			color /= 256;
			data[(y * s_l) + (x * (bpp / 8)) + i++] = color % 256;
			data[(y * s_l) + (x * (bpp / 8)) + i++] = 0;
		}
	}
}
