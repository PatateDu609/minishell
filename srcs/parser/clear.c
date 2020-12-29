/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 21:59:27 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/29 22:25:30 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_splitted(char **strs)
{
	char	**saved;

	saved = strs;
	while (*strs)
		free(*strs++);
	free(saved);
}

void	ft_free_command(void *cmdv)
{
	t_command	*cmd;
	t_redirect	**saved;

	cmd = (t_command *)cmdv;
	free_splitted(cmd->args);
	saved = cmd->redirects;
	if (saved)
	{
		while (*saved)
		{
			free((*saved)->filename);
			free(*saved++);
		}
	}
	free(cmd->redirects);
	free(cmd);
}
