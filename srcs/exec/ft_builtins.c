/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 05:02:30 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/08 18:59:48 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

void	ft_execute_builtin(t_list *lst, t_builtin_func builtin)
{
	int			redir;
	t_command	*command;
	int			fds[2];

	command = (t_command *)lst->content;
	redir = command->in || command->out;
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
	if (command->piped)
		exit(g_exit_code);
}
