/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 16:41:54 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 19:44:16 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

int			ft_init_redir(t_command *command)
{
	t_redirect	**redirs;

	redirs = command->redirects;
	command->in = 0;
	command->out = 0;
	if (!redirs)
		return (1);
	while (*redirs)
	{
		if ((*redirs)->type == 1)
		{
			if (ft_check_file(*redirs) && command->in != -1)
				command->in = 1;
			else
				command->in = -1;
		}
		else if (ft_check_file(*redirs) && command->out != -1)
			command->out = 1;
		else
			command->out = -1;
		redirs++;
	}
	return (command->out != -1 && command->in != -1);
}

void		ft_redirect_in(t_command *command)
{
	int		red[2];
	pid_t	pid;

	if (command->in != 1)
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
		ft_apply_redir_in(command, red[1]);
		close(red[1]);
		exit(0);
	}
	close(red[1]);
}

static void	ft_prep_redir_out(int red[2])
{
	if (pipe(red))
	{
		ft_print_error_exec("pipe");
		exit(1);
	}
	if (dup2(red[1], 1) < 0)
	{
		ft_print_error_exec("dup2");
		exit(1);
	}
}

void		ft_redirect_out(t_command *command)
{
	int		red[2];
	pid_t	pid;
	char	*output;

	if (command->out != 1)
		return ;
	ft_prep_redir_out(red);
	close(red[1]);
	pid = fork();
	if (pid == 0)
	{
		close(1);
		output = ft_load_pipe(red[0]);
		ft_apply_redir_out(command, output);
		close(red[0]);
		exit(0);
	}
	close(red[0]);
}
