/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_term_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 22:03:48 by heynard           #+#    #+#             */
/*   Updated: 2017/05/29 23:08:07 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		fdf_error_arg(void)
{
	ft_printf("fdf: usage: ./fdf \"map.fdf\"\n");
	exit(1);
}

void		fdf_error_file_name(t_env *env, char *name, char *line)
{
	if (line)
		free(line);
	ft_printf("fdf: %s: No such file or directory\n", name);
	fdf_free_env(env);
	exit(1);
}

void		fdf_undifined_error(t_env *env, int fd, char **split, char *line)
{
	if (line)
		free(line);
	perror("fdf: ");
	fdf_free_env(env);
	if (split)
		fdf_free_split(split);
	if (fd > 0)
		if ((close(fd)) < 0)
			fdf_undifined_error(env, 0, NULL, NULL);
	exit(1);
}

void		fdf_error_file(t_env *env, int error, char **split, int fd)
{
	if (error == 1)
		ft_printf("fdf: incorrect file: map size invalid\n");
	if (error == 2)
		ft_printf("fdf: incorrect file: incoherant map size\n");
	if (error == 3)
		ft_printf("fdf: incorrect file: invalid char in map\n");
	if (error == 4)
		ft_printf("fdf: incorrect file: value does not fit in an integer\n");
	fdf_free_env(env);
	if (split)
		fdf_free_split(split);
	if (fd > 0)
		if ((close(fd)) < 0)
			fdf_undifined_error(env, 0, NULL, NULL);
	exit(1);
}
