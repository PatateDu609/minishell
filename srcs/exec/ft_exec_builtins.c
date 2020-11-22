/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 03:05:52 by gboucett          #+#    #+#             */
/*   Updated: 2020/11/22 03:58:12 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

static int	is_builtin(char *name)
{
	if (!ft_strcmp(name, "echo"))
		return (BUILTIN_ECHO);
	else if (!ft_strcmp(name, "cd"))
		return (BUILTIN_CD);
	else if (!ft_strcmp(name, "pwd"))
		return (BUILTIN_PWD);
	else if (!ft_strcmp(name, "env"))
		return (BUILTIN_ENV);
	else if (!ft_strcmp(name, "export"))
		return (BUILTIN_EXPORT);
	else if (!ft_strcmp(name, "unset"))
		return (BUILTIN_UNSET);
	else if (!ft_strcmp(name, "exit"))
		return (BUILTIN_EXIT);
	else
		return (BUILTIN_DEFAULT);
}

int			exec_builtin(t_env *env, t_command *cmd, t_redirect *redirects)
{
	int		id;
	void	*tfree;

	tfree = NULL;
	if ((id = is_builtin(cmd->name)) == BUILTIN_DEFAULT)
		return (0);
	else if (id == BUILTIN_ENV)
		ft_print_env(env->env);
	else if (id == BUILTIN_EXPORT)
		ft_export(env, cmd->args);
	else if (id == BUILTIN_UNSET)
		ft_unset(env, cmd->args);
	else if (id == BUILTIN_ECHO)
		ft_echo(cmd->args, redirects);
	else if (id == BUILTIN_PWD)
		ft_printf("%s\n", (tfree = getcwd(NULL, 0)));
	else if (id == BUILTIN_CD)
		ft_cd(env, cmd->args);
	else if (id == BUILTIN_EXIT)
	{
		free_env(env);
		ft_exit();
	}
	free(tfree);
	g_exit_code = 0;
	return (1);
}
