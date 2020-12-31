/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_construct_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 03:23:51 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/31 13:03:47 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

static int	ft_search_in_dir(DIR *dir, const char *filename)
{
	struct dirent	*entry;

	errno = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_type == DT_REG && !ft_strcmp(entry->d_name, filename))
			break ;
		errno = 0;
		entry = readdir(dir);
	}
	if (errno)
		return (-1);
	return (entry && entry->d_type == DT_REG);
}

static char	*ft_find_file(const char *filename)
{
	char			**paths;
	DIR				*dir;

	paths = g_env->paths;
	while (*paths)
	{
		dir = opendir(*paths++);
		if (!dir)
			continue ;
		if (ft_search_in_dir(dir, filename) == 1)
			break ;
		closedir(dir);
		dir = NULL;
	}
	if (dir)
	{
		closedir(dir);
		return (*(paths - 1));
	}
	return (NULL);
}

char	*ft_construct_path(char *name)
{
	char	*folder;
	char	*parts[3];

	if (ft_strchr(name, '/'))
		return (ft_strdup(name));
	folder = ft_find_file(name);
	if (!folder)
		return (NULL);
	parts[0] = folder;
	parts[1] = name;
	parts[2] = NULL;
	return (ft_strjoin_arr(parts, '/'));
}
