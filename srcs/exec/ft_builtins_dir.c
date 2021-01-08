/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 03:35:08 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/07 22:29:09 by gboucett         ###   ########.fr       */
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

void		ft_cd(t_command *command)
{
	char	*cwd;
	char	*target;

	target = ft_get_target(command->args[1]);
	cwd = getcwd(NULL, 0);
	if (chdir(target))
	{
		g_exit_code = 1;
		if (target)
			ft_print_error_builtins("cd", target, 1);
		return ;
	}
	ft_modify_var(ft_strdup("OLDPWD"), cwd);
	cwd = getcwd(NULL, 0);
	ft_modify_var(ft_strdup("PWD"), cwd);
	g_exit_code = 0;
}

void		ft_pwd(t_command *command)
{
	(void)command;
	ft_printf("%s\n", ft_getvar("PWD"));
	g_exit_code = 0;
}
