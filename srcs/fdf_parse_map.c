/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 14:32:25 by heynard           #+#    #+#             */
/*   Updated: 2017/06/08 18:11:35 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static size_t	fdf_count(char **split)
{
	int			i;

	i = 0;
	if (split)
	{
		while (split[i] != NULL)
			i++;
	}
	return (i);
}

static int		fdf_atoi(t_env *env, const char *str, char **split, int fd)
{
	int			neg;
	intmax_t	ret;
	int			i;

	i = 0;
	neg = 1;
	ret = 0;
	while (*(str + i) == ' ' ||
			*(str + i) == '\t')
		i++;
	if (*(str + i) == '-')
		neg = -1;
	if (*(str + i) == '-' || *(str + i) == '+')
		i++;
	while (ft_isdigit(*(str + i)))
	{
		ret = ret * 10 + (*(str + i) - '0');
		i++;
	}
	if (*(str + i) != '\0')
		fdf_error_file(env, 3, split, fd);
	if (ret > 2147483647 || ret < -2147483648)
		fdf_error_file(env, 4, split, fd);
	return ((int)(ret * neg));
}

static void		fdf_handle_line(int fd, t_env *env, char *line, t_point **tab)
{
	char		**split;
	t_point		tmp;
	size_t		line_size;
	int			i;

	split = ft_strsplit(line, ' ');
	i = -1;
	line_size = fdf_count(split);
	if (env->width == -1 && line_size != 0)
		env->width = line_size;
	else if (env->width != line_size)
		fdf_error_file(env, 2, split, fd);
	if ((tab[env->j] = malloc(sizeof(t_point) * line_size)) == NULL)
		fdf_undifined_error(env, fd, split, line);
	while (split[++i] != NULL)
	{
		tmp.x = i;
		tmp.y = env->j;
		tmp.z = fdf_atoi(env, split[i], split, fd);
		tab[env->j][i] = tmp;
	}
	env->j++;
	fdf_free_split(split);
}

static void		fdf_read_file(int fd, char *line, t_env *env, t_point **tab)
{
	while (get_next_line(fd, &line))
	{
		fdf_handle_line(fd, env, line, tab);
		free(line);
		line = NULL;
	}
}

void			fdf_parse_map(t_env *env, char *file_name)
{
	char		*line;
	t_point		**tab;
	int			fd;

	line = NULL;
	fdf_my_open(env, &fd, file_name);
	env->height = fdf_heightofmap(fd, line);
	env->param_to_free = (void *)line;
	if (close(fd) < 0)
		fdf_undifined_error(env, 0, NULL, line);
	if (env->height <= 0)
		fdf_error_file(env, 1, NULL, 0);
	if ((tab = malloc(sizeof(t_point *) * env->height)) == NULL)
		fdf_undifined_error(env, 0, NULL, line);
	env->tab = tab;
	fdf_my_open(env, &fd, file_name);
	fdf_read_file(fd, line, env, tab);
	if (close(fd) < 0)
		fdf_undifined_error(env, 0, NULL, line);
	free(line);
	if (env->height <= 1 || env->width <= 1)
		fdf_error_file(env, 1, NULL, 0);
}
