/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 15:58:34 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/08 13:40:07 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

void	ft_open_pipe(t_list *list)
{
	t_command	*command;

	command = (t_command *)list->content;
	command->piped = 0;
	if (ft_is_pipe(list))
	{
		if (pipe(command->pipe))
			ft_print_error_exec("pipe");
		command->piped = 1;
	}
}

void	ft_close_pipe(t_list *list)
{
	t_command	*command;
	t_command	*prev;

	command = (t_command *)list->content;
	prev = NULL;
	if (list->previous)
		prev = (t_command *)list->previous->content;
	if (command->piped)
	{
		close(command->pipe[1]);
		if (command->type == BREAK)
		{
			close(command->pipe[0]);
		}
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
	else if (command->type == PIPE)
		close(command->pipe[1]);
	if (prev && prev->type == PIPE && dup2(prev->pipe[0], 0) < 0)
	{
		ft_print_error_exec("dup2");
		exit(1);
	}
	else if (prev && prev->type == PIPE)
		close(prev->pipe[0]);
}

size_t	ft_size_pipeline(t_list *list)
{
	t_command	*command;
	size_t		result;

	result = 1;
	while (list)
	{
		command = (t_command *)list->content;
		if (command->type != PIPE)
			break ;
		result++;
		list = list->next;
	}
	return (result);
}

int		ft_is_pipe(t_list *list)
{
	t_command	*command;
	t_command	*prev;

	command = (t_command *)list->content;
	prev = NULL;
	if (list->previous)
		prev = (t_command *)list->previous->content;
	return (command->type == PIPE || (prev && prev->type == PIPE));
}
