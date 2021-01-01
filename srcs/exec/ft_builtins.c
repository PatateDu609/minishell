/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 05:02:30 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/01 16:54:46 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

void	ft_execute_piped_builtin(t_list *lst, t_builtin_func builtin)
{
	int		status;

	g_pid = fork();
	if (g_pid == -1)
		ft_print_error_exec("fork");
	else if (g_pid)
	{
		waitpid(g_pid, &status, 0);
		ft_close_pipe(lst, 1);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
	}
	else
	{
		ft_redirect_pipe(lst);
		builtin((t_command *)lst->content);
		exit(g_exit_code);
	}
}

void	ft_execute_builtin(t_list *lst, t_builtin_func builtin)
{
	int		pipe_open;

	ft_open_pipe(lst, &pipe_open);
	if (!pipe_open)
		builtin((t_command *)lst->content);
	else
		ft_execute_piped_builtin(lst, builtin);
}
