/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 02:51:10 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 05:36:31 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

static void	ft_execute_cmd(t_list *lst)
{
	int			status;
	t_command	*command;

	command = (t_command *)lst->content;
	g_pid = fork();
	if (g_pid == -1)
		ft_print_error_exec("fork");
	else if (g_pid)
	{
		waitpid(g_pid, &status, 0);
		ft_close_pipe(lst);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
	}
	else
	{
		ft_redirect_pipe(lst);
		ft_redirect_in(command);
		ft_redirect_out(command);
		execve(command->name, command->args, g_env->merged);
		ft_print_error_exec(command->args[0]);
		exit(1);
	}
}

static void	ft_exec_pipeline(t_list **commands)
{
	size_t		len;
	size_t		i;
	size_t		count;
	pid_t		*pids;

	len = ft_size_pipeline(*commands);
	pids = ft_calloc(len, sizeof(pid_t));
	i = 0;
	while (*commands && ft_is_pipe(*commands))
	{
		ft_open_pipe(*commands);
		pids[i] = fork();
		if (pids[i] == 0)
		{
			ft_execute_cmd(*commands);
			exit(0);
		}
		i++;
		*commands = (*commands)->next;
	}
	count = 0;
	while (count < len)
	{
		i = 0;
		while (i < len)
		{
			if (waitpid(pids[i], NULL, WNOHANG) != 0)
				count++;
			i++;
		}
	}
}

void	ft_exec(t_list *commands)
{
	t_command	*command;
	int			piped;

	while (commands)
	{
		command = (t_command *)commands->content;
		piped = 0;
		if (ft_check_command(command, &commands) && ft_init_redir(command))
		{
			ft_merge_env(NULL);
			if (ft_is_pipe(commands))
			{
				ft_exec_pipeline(&commands);
				piped = 1;
			}
			else if (ft_get_builtin_id(command->name) != BUILTIN_DEFAULT)
				ft_init_builtin(commands);
			else
				ft_execute_cmd(commands);
		}
		if (commands && !piped)
			commands = commands->next;
	}
	g_pid = 0;
}
