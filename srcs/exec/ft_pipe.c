/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 15:58:34 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/01 02:16:58 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

void	ft_open_pipe(t_list *list, int *pipe_open)
{
	t_command	*command;
	t_command	*prev;

	command = (t_command *)list->content;
	prev = NULL;
	if (list->previous)
		prev = (t_command *)list->previous->content;
	*pipe_open = 0;
	if (command->type == PIPE || (prev && prev->type == PIPE))
	{
		if (pipe(command->pipe))
			ft_print_error_exec("pipe");
		*pipe_open = 1;
	}
}

void	ft_close_pipe(t_list *list, int pipe_open)
{
	t_command	*command;
	t_command	*prev;

	command = (t_command *)list->content;
	prev = NULL;
	if (list->previous)
		prev = (t_command *)list->previous->content;
	if (pipe_open)
	{
		close(command->pipe[1]);
		if (command->type == BREAK)
			close(command->pipe[0]);
	}
	if (prev && prev->type == PIPE)
		close(prev->pipe[0]);
}

void	ft_redirect_pipe(t_list *list)
{
	t_command	*command;
	t_command	*prev;

	command = (t_command *)list->content;
	prev = NULL;
	if (list->previous)
		prev = (t_command *)list->previous->content;
	if (command->type == PIPE && dup2(command->pipe[1], 1) < 0)
	{
		ft_print_error_exec("dup2");
		exit(1);
	}
	if (prev && prev->type == PIPE && dup2(prev->pipe[0], 0) < 0)
	{
		ft_print_error_exec("dup2");
		exit(1);
	}
}
