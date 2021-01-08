/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 05:02:30 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/08 03:30:47 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

void	ft_execute_piped_builtin(t_list *lst, t_builtin_func builtin)
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
		builtin(command);
		exit(g_exit_code);
	}
}

void	ft_execute_builtin(t_list *lst, t_builtin_func builtin)
{
	int			redir;
	t_command	*command;
	int			fds[2];

	command = (t_command *)lst->content;
	redir = command->in || command->out;
	if (!command->piped)
	{
		fds[0] = dup(0);
		fds[1] = dup(1);
		if (redir)
		{
			ft_redirect_in(command);
			ft_redirect_out(command);
		}
		builtin(command);
		dup2(fds[0], 0);
		dup2(fds[1], 1);
	}
	else
		ft_execute_piped_builtin(lst, builtin);
}
