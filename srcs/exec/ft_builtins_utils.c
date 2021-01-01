/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 03:03:57 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/01 05:31:41 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

int	ft_get_builtin_id(char *name)
{
	if (!ft_strcmp(name, "echo"))
		return (BUILTIN_ECHO);
	if (!ft_strcmp(name, "cd"))
		return (BUILTIN_CD);
	if (!ft_strcmp(name, "pwd"))
		return (BUILTIN_PWD);
	if (!ft_strcmp(name, "export"))
		return (BUILTIN_EXPORT);
	if (!ft_strcmp(name, "env"))
		return (BUILTIN_ENV);
	if (!ft_strcmp(name, "unset"))
		return (BUILTIN_UNSET);
	if (!ft_strcmp(name, "exit"))
		return (BUILTIN_EXIT);
	return (BUILTIN_DEFAULT);
}

size_t	ft_get_echo_start(char **args)
{
	char	*found;
	size_t	i;

	i = 1;
	args++;
	while (*args)
	{
		found = ft_strnstr(*args, "-n", ft_strlen(*args));
		if (found && found == *args++)
			i++;
		else
			break ;
	}
	return (i);
}

void	ft_init_builtin(t_list *lst)
{
	t_builtin_func	builtins[7];
	int				id;

	builtins[BUILTIN_ECHO] = ft_echo;
	builtins[BUILTIN_CD] = ft_cd;
	builtins[BUILTIN_PWD] = ft_pwd;
	builtins[BUILTIN_ENV] = ft_env;
	builtins[BUILTIN_UNSET] = ft_unset;
	builtins[BUILTIN_EXPORT] = ft_export;
	builtins[BUILTIN_EXIT] = ft_exit;
	id = ft_get_builtin_id(((t_command *)lst->content)->args[0]);
	if (id == BUILTIN_DEFAULT)
		return ;
	ft_execute_builtin(lst, builtins[id]);
}

int	ft_check_shell_name(char *name)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(name[i]) && name[i] != '_')
		return (0);
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
