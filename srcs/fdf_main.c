/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 22:02:15 by heynard           #+#    #+#             */
/*   Updated: 2017/06/08 18:05:04 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static t_env	*fdf_init_env(void)
{
	t_env		*env;

	if ((env = malloc(sizeof(t_env))) == NULL)
		fdf_undifined_error(env, 0, NULL, NULL);
	if ((env->mlx_ptr = mlx_init()) == NULL)
		fdf_undifined_error(env, 0, NULL, NULL);
	env->tab = NULL;
	env->image = NULL;
	env->mlx_win = NULL;
	env->param_to_free = NULL;
	env->width_s = 1600;
	env->height_s = 1200;
	env->min = 0;
	env->max = 0;
	env->height = 0;
	env->width = -1;
	env->scale = 400;
	env->j = 0;
	return (env);
}

static void		fdf_init_window(t_env *e, const char *name)
{
	e->mlx_win = mlx_new_window(e->mlx_ptr, e->width_s,
								e->height_s, (char *)name);
	if (e->mlx_win == NULL)
		fdf_undifined_error(e, 0, NULL, NULL);
}

static void		print_tab(t_env *env)
{
	int			j;
	int			i;

	j = 0;
	while (j < env->height)
	{
		i = 0;
		while (i < env->width)
		{
			ft_printf("%d;%d;%d ", env->tab[j][i].x,
						env->tab[j][i].y, env->tab[j][i].z);
			i++;
		}
		ft_putchar('\n');
		j++;
	}
}

void			fdf_my_open(t_env *env, int *fd, char *file_name)
{
	if ((*fd = open(file_name, O_RDONLY)) < 0)
		fdf_error_file_name(env, file_name, NULL);
}

int				main(int ac, char **av)
{
	t_env		*env;

	if (ac != 2)
		fdf_error_arg();
	env = fdf_init_env();
	fdf_parse_map(env, av[1]);
	fdf_get_min_max(env);
	fdf_init_window(env, "FDF");
	fdf_draw_tab(env);
	mlx_hook(env->mlx_win, 2, 1L << 0, fdf_key_event, env);
	mlx_loop(env->mlx_ptr);
	return (0);
}
