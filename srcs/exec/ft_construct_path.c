/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_construct_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 23:32:00 by gboucett          #+#    #+#             */
/*   Updated: 2020/08/20 00:13:40 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

static char		*ft_construct_from_name(char **paths, char *command)
{
	DIR				*pwd;
	struct dirent	*entry;
	char			*path[3];

	path[1] = command;
	path[2] = 0;
	while (*paths)
	{
		pwd = opendir(*paths);
		while ((entry = readdir(pwd)))
		{
			if (ft_strlen(entry->d_name) == ft_strlen(command))
				if (ft_strnstr(entry->d_name, command, ft_strlen(command)))
				{
					path[0] = *paths;
					closedir(pwd);
					return (ft_strjoin_arr(path, '/'));
				}
		}
		closedir(pwd);
		paths++;
	}
	errno = 656;
	return (NULL);
}

static int		ft_check_command(char *command)
{
	struct stat		buf;

	if (stat(command, &buf))
		return (0);
	if (S_ISDIR(buf.st_mode))
	{
		errno = EISDIR;
		return (0);
	}
	// if (buf.st_mode & S_IXUSR)
	// 	return (1);
	return (1);
}

char			*ft_construct_cmd(t_env *env, char *command)
{
	char			*result;
	char			*tmp;

	result = NULL;
	if (!ft_strchr(command, '/'))
		result = ft_construct_from_name(env->paths, command);
	else if (ft_check_command(command))
	{
		if (command[0] != '/')
		{
			tmp = getvar(env, "PWD");
			result = ft_strjoin(tmp, "/");
			free(tmp);
			tmp = result;
			result = ft_strjoin(result, command);
			free(tmp);
		}
		else
			result = ft_strdup(command);
	}
	return (result);
}
