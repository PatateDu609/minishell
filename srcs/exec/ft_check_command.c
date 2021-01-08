/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 04:18:24 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/08 20:00:46 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"
#include "ft_expand.h"

static int	ft_get_cmd_name(t_command *cmd)
{
	ft_expand(cmd);
	if (ft_get_builtin_id(cmd->args[0]) != BUILTIN_DEFAULT)
		cmd->name = ft_strdup(cmd->args[0]);
	else
		cmd->name = ft_construct_path(cmd->args[0]);
	if (!cmd->name)
		ft_print_error_exec(cmd->args[0]);
	return (!!cmd->name);
}

int			ft_check_command(t_command *command, t_list **commands)
{
	t_list	*current;
	int		result;

	if (command->type != PIPE)
		return (ft_get_cmd_name(command));
	current = *commands;
	result = 1;
	while (current && ft_is_pipe(current))
	{
		command = (t_command *)current->content;
		if (!ft_get_cmd_name(command))
			result = 0;
		current = current->next;
	}
	if (!result)
	{
		current = *commands;
		while (current && current->next && ft_is_pipe(current->next))
			current = current->next;
		*commands = current;
	}
	return (result);
}
