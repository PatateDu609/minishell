/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:26:57 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/08 19:05:36 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_debug.h"

void	ft_print_redirs(t_redirect **redirs)
{
	dprintf(g_tree, "\033[1;38;5;197mRedirections :");
	if (redirs)
	{
		dprintf(g_tree, "\033[0m\n");
		while (*redirs)
		{
			dprintf(g_tree, "  - \033[38;5;129m");
			if ((*redirs)->type == 1)
				dprintf(g_tree, "input");
			else if ((*redirs)->type == 2)
				dprintf(g_tree, "output and trunc");
			else if ((*redirs)->type == 3)
				dprintf(g_tree, "output without trunc");
			dprintf(g_tree, "\033[0m : \033[38;5;229m%s\033[0m\n",
				(*redirs)->filename);
			redirs++;
		}
	}
	else
		dprintf(g_tree, "\033[38;5;229m None\033[0m\n");
}

void	ft_print_command(void *cmdv)
{
	t_command	*cmd;
	char		**args;

	cmd = (t_command *)cmdv;
	dprintf(g_tree, "\033[1;38;5;196mCommand :\033[0m\033[38;5;41m %s\033[0m\n",
		cmd->args[0]);
	dprintf(g_tree, "\033[1;38;5;197mType :\033[0m\033[38;5;85m ");
	if (cmd->type == COMMAND)
		dprintf(g_tree, "Command\033[0m\n");
	else if (cmd->type == PIPE)
		dprintf(g_tree, "Pipe\033[0m\n");
	else if (cmd->type == BREAK)
		dprintf(g_tree, "Break\033[0m\n");
	else
		dprintf(g_tree, "Unknown\033[0m\n");
	dprintf(g_tree, "\033[1;38;5;197mArgs :\033[0m\n");
	args = cmd->args;
	while (*args)
		dprintf(g_tree, "  - \033[38;5;229m%s\033[0m\n", *args++);
	ft_print_redirs(cmd->redirects);
	dprintf(g_tree, "\n");
}

void	ft_print_cmd(t_list *list)
{
	dprintf(g_tree, "------------------------------------------------------\n");
	ft_lstiter(list, ft_print_command);
	dprintf(g_tree, "------------------------------------------------------\n");
}
