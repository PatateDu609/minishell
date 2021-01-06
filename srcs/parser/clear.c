/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 21:59:27 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 19:51:44 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_splitted(char **strs)
{
	char	**saved;

	if (!strs)
		return ;
	saved = strs;
	while (*strs)
		free(*strs++);
	free(saved);
}

static void	ft_free_redir(t_redirect *redir)
{
	free(redir->filename);
	free(redir);
}

void		ft_free_command(void *cmdv)
{
	t_command	*cmd;
	t_redirect	**saved;

	cmd = (t_command *)cmdv;
	free_splitted(cmd->args);
	saved = cmd->redirects;
	if (saved)
		while (*saved)
			ft_free_redir(*saved++);
	free(cmd->redirects);
	free(cmd->name);
	free(cmd);
}
