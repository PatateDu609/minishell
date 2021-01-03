/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 02:51:10 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/03 20:48:49 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

static void	ft_execute_cmd(t_list *lst)
{
	int			status;
	int			pipe_open;
	t_command	*command;

	command = (t_command *)lst->content;
	ft_open_pipe(lst, &pipe_open);
	g_pid = fork();
	if (g_pid == -1)
		ft_print_error_exec("fork");
	else if (g_pid)
	{
		waitpid(g_pid, &status, 0);
		ft_close_pipe(lst, pipe_open);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
	}
	else
	{
		ft_redirect_pipe(lst);
		ft_redirect_in(command);
		ft_redirect_out(command);
		execve(command->name, command->args, g_env->merged);
		printf("(printed with printf)minishell: execve marche po\n");
		exit(1);
	}
}

void	ft_exec(t_list *commands)
{
	t_command	*command;

	ft_init_exec(commands);
	while (commands)
	{
		command = (t_command *)commands->content;
		if (command->name)
		{
			ft_init_redir(command);
			ft_merge_env(NULL);
			if (ft_get_builtin_id(command->name) != BUILTIN_DEFAULT)
				ft_init_builtin(commands);
			else
				ft_execute_cmd(commands);
		}
		commands = commands->next;
	}
	g_pid = 0;
}
