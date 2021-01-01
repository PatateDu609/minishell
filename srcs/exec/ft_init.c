/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 19:45:14 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/01 23:42:39 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

static int	ft_get_cmd_name(t_command *cmd)
{
	if (ft_get_builtin_id(cmd->args[0]) != BUILTIN_DEFAULT)
		cmd->name = ft_strdup(cmd->args[0]);
	else
		cmd->name = ft_construct_path(cmd->args[0]);
	if (!cmd->name)
		ft_print_error_exec(cmd->args[0]);
	return (!!cmd->name);
}

static t_list	*ft_invalidate_pipe(t_list *list)
{
	t_command	*command;

	while (list)
	{
		command = (t_command *)list->content;
		free(command->name);
		command->name = NULL;
		if (command->type == BREAK)
			return (list->next);
		list = list->next;
	}
	return (NULL);
}

void	ft_init_exec(t_list *list)
{
	t_command	*command;
	t_list		*start_pipe;
	int			valid;

	valid = 1;
	start_pipe = NULL;
	while (list)
	{
		command = (t_command *)list->content;
		if (!start_pipe && command->type != COMMAND)
		{
			start_pipe = list;
			valid = 1;
		}
		valid &= ft_get_cmd_name(command);
		if (valid == 0)
		{
			list = ft_invalidate_pipe(start_pipe);
			start_pipe = NULL;
			continue ;
		}
		if (command->type == BREAK)
			valid = !(start_pipe = NULL);
		list = list->next;
	}
}
