/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 03:35:08 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/09 00:51:22 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

static char	*ft_get_target(char *arg)
{
	char	*target;

	target = arg;
	if (!arg || !ft_strcmp(arg, "--"))
	{
		target = ft_getvar("HOME");
		if (!target)
			ft_print_error_builtins("cd", "HOME not set", 0);
	}
	else if (!ft_strcmp(arg, "-"))
	{
		target = ft_getvar("OLDPWD");
		if (!target)
			ft_print_error_builtins("cd", "OLDPWD not set", 0);
	}
	return (target);
}

static int	ft_check_cwd(char *cwd)
{
	if (!cwd)
	{
		ft_print_error_builtins("cd", "getcwd", 1);
		g_exit_code = 1;
		return (0);
	}
	return (1);
}

void		ft_cd(t_command *command)
{
	char	*cwd;
	char	*target;

	target = ft_get_target(command->args[1]);
	cwd = getcwd(NULL, 0);
	if (!ft_check_cwd(cwd))
		return ;
	if (chdir(target))
	{
		g_exit_code = 1;
		free(cwd);
		if (target)
			ft_print_error_builtins("cd", target, 1);
		return ;
	}
	ft_modify_var(ft_strdup("OLDPWD"), cwd);
	cwd = getcwd(NULL, 0);
	if (!ft_check_cwd(cwd))
		return ;
	ft_modify_var(ft_strdup("PWD"), cwd);
	g_exit_code = 0;
}

void		ft_pwd(t_command *command)
{
	char	*pwd;

	(void)command;
	pwd = ft_getvar("PWD");
	if (pwd)
		ft_printf("%s\n", pwd);
	else
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			g_exit_code = 1;
			ft_print_error_builtins("pwd", "getcwd", 1);
			return ;
		}
		ft_printf("%s\n", pwd);
		free(pwd);
	}
	g_exit_code = 0;
}
