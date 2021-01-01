/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 21:59:27 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/01 22:22:18 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_splitted(char **strs)
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
	if (redir->fd != -1)
		close(redir->fd);
	free(redir->filename);
	free(redir->content);
	free(redir);
}

void	ft_free_command(void *cmdv)
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
