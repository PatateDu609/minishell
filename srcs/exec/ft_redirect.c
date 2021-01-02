/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 16:41:54 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/02 21:52:36 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

void	ft_redirect_in(t_command *command)
{
	int		red[2];
	pid_t	pid;

	if (!command->input)
		return ;
	if (pipe(red))
	{
		ft_print_error_exec("pipe");
		exit(1);
	}
	if (dup2(red[0], 0) < 0)
	{
		ft_print_error_exec("dup2");
		exit(1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(red[0]);
		write(red[1], command->input, ft_strlen(command->input));
		close(red[1]);
		exit(0);
	}
	close(red[1]);
}
