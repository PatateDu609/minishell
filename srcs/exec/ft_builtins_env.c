/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 04:31:34 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 19:48:10 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"
#include "ft_parser.h"

static void	ft_export_var(char *arg)
{
	char	*result;

	if (ft_strchr(arg, '='))
		ft_add_var(arg);
	result = ft_strjoin(arg, "=");
	ft_add_var(arg);
	free(result);
}

void		ft_export(t_command *command)
{
	char	**args;

	args = command->args + 1;
	g_exit_code = 0;
	if (!*args)
	{
		args = ft_sort_env();
		ft_merge_env(args);
		ft_print_splitted(g_env->merged);
		free(args);
		ft_merge_env(NULL);
		return ;
	}
	while (*args)
	{
		if (ft_check_shell_name(*args))
			ft_export_var(*args);
		else
		{
			g_exit_code = 1;
			ft_print_error_env("export", *args);
		}
		args++;
	}
}

void		ft_unset(t_command *command)
{
	char	**args;

	args = command->args + 1;
	g_exit_code = 0;
	while (*args)
	{
		if (ft_check_shell_name(*args))
			ft_delete_var(*args);
		else
		{
			g_exit_code = 1;
			ft_print_error_env("unset", *args);
		}
		args++;
	}
}

void		ft_env(t_command *command)
{
	(void)command;
	ft_print_splitted(g_env->merged);
	g_exit_code = 0;
}
