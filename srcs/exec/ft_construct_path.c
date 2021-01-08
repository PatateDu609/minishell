/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_construct_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 03:23:51 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/08 03:28:52 by gboucett         ###   ########.fr       */
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
	if (!paths)
		return (NULL);
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

int			ft_check_executable_file(char *path, int to_free)
{
	struct stat	st;

	errno = 0;
	if (stat(path, &st) != 0)
		errno = ENOENT;
	if (!errno && !S_ISREG(st.st_mode))
		errno = EISDIR;
	if (!errno && !(st.st_mode & S_IXUSR))
		errno = EACCES;
	if (errno && to_free)
		free(path);
	if (errno)
		g_exit_code = 127;
	return (!errno);
}

char		*ft_construct_path(char *name)
{
	char		*folder;
	char		*parts[3];
	char		*result;

	if (ft_strchr(name, '/'))
	{
		if (ft_check_executable_file(name, 0))
			return (ft_strdup(name));
		return (NULL);
	}
	folder = ft_find_file(name);
	if (!folder)
	{
		errno = ENOENT;
		g_exit_code = 127;
		return (NULL);
	}
	parts[0] = folder;
	parts[1] = name;
	parts[2] = NULL;
	result = ft_strjoin_arr(parts, '/');
	if (!ft_check_executable_file(result, 1))
		return (NULL);
	return (result);
}
