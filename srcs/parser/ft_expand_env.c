/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 11:03:23 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/31 02:05:16 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_env.h"

static void	ft_expand_env_redir(t_redirect **redirect)
{
	char	*tmp;

	if (!redirect)
		return ;
	while (*redirect)
	{
		tmp = ft_str_replace_var((*redirect)->filename);
		free((*redirect)->filename);
		(*redirect)->filename = tmp;
		redirect++;
	}
}

static void	ft_expand_env_args(char **args)
{
	char	*tmp;

	while (*args)
	{
		tmp = ft_str_replace_var(*args);
		free(*args);
		*args = tmp;
		args++;
	}
}

void	ft_expand_env(t_list *parsed)
{
	t_command	*command;

	while (parsed)
	{
		command = (t_command *)parsed->content;
		ft_expand_env_redir(command->redirects);
		ft_expand_env_args(command->args);
		parsed = parsed->next;
	}
}
