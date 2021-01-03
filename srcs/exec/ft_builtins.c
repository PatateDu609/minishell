/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 05:02:30 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/03 23:16:42 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

void	ft_execute_piped_builtin(t_list *lst, t_builtin_func builtin, int po)
{
	int		status;
	t_command	*command;

	command = (t_command *)lst->content;
	g_pid = fork();
	if (g_pid == -1)
		ft_print_error_exec("fork");
	else if (g_pid)
	{
		waitpid(g_pid, &status, 0);
		ft_close_pipe(lst, po);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
	}
	else
	{
		ft_redirect_pipe(lst);
		ft_redirect_in(command);
		ft_redirect_out(command);
		builtin((t_command *)lst->content);
		exit(g_exit_code);
	}
}

void	ft_execute_builtin(t_list *lst, t_builtin_func builtin)
{
	int			pipe_open;
	int			redir;
	t_command	*command;

	command = (t_command *)lst->content;
	ft_open_pipe(lst, &pipe_open);
	redir = command->in || command->out;
	(void)builtin;
	dprintf(g_fd, "name = %s, pipe_open = redir = %d\n", command->name, redir);
	if (!pipe_open && !redir)
		builtin(command);
	else
		ft_execute_piped_builtin(lst, builtin, pipe_open);
}
