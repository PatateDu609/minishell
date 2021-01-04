/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 22:17:20 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/04 00:53:11 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_command(t_list **lst, char *name)
{
	t_command	*cmd;
	t_list		*element;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (0);
	cmd->args = ft_calloc(2, sizeof(char *));
	if (!cmd->args)
	{
		free(cmd);
		return (0);
	}
	element = ft_lstnew(cmd);
	if (!element)
	{
		free(element);
		free(cmd->args);
		free(cmd);
		return (0);
	}
	cmd->args[0] = name;
	cmd->type = COMMAND;
	ft_lstadd_back(lst, element);
	*lst = ft_lstlast(*lst);
	return (1);
}

int	ft_add_arg(t_list *lst, char *arg)
{
	t_command	*cmd;
	char		**tmp;

	cmd = (t_command *)lst->content;
	tmp = ft_strs_append_str(cmd->args, arg);
	free(arg);
	if (!tmp)
		return (0);
	cmd->args = tmp;
	return (1);
}

int	ft_add_redir(t_list *lst, char *redir, char *target)
{
	t_command	*cmd;
	t_redirect	**tmp;
	t_redirect	*new;

	cmd = (t_command *)lst->content;
	new = ft_calloc(1, sizeof(t_redirect));
	if (!new)
		return (0);
	new->filename = target;
	new->type = ft_is_redirect(redir);
	if (cmd->redirects)
		tmp = ft_append_redir(cmd->redirects, new);
	else
	{
		tmp = ft_calloc(2, sizeof(t_redirect *));
		if (!tmp)
			return (0);
		tmp[0] = new;
	}
	if (tmp)
		cmd->redirects = tmp;
	return (tmp != NULL);
}
