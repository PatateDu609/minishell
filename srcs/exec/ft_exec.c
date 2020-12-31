/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 02:51:10 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/31 20:24:50 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

void	ft_execute_cmd(t_list *lst, char *path)
{
	int			status;
	int			pipe_open;
	t_command	*command;

	command = (t_command *)lst->content;
	ft_open_pipe(lst, &pipe_open);
	g_pid = fork();
	if (g_pid == -1)
	{
		// TODO: error processing
		return ;
	}
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
		execve(path, command->args, g_env->merged);
		printf("(printed with printf)minishell: execve marche po\n");
		exit(1);
	}
}

void	ft_exec(t_list *commands)
{
	t_command	*command;
	char		*path;

	while (commands)
	{
		command = (t_command *)commands->content;
		ft_merge_env();
		path = ft_construct_path(command->args[0]);
		if (path)
			ft_execute_cmd(commands, path);
		free(path);
		commands = commands->next;
	}
	g_pid = 0;
}
