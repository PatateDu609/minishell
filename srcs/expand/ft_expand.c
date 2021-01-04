/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:05:46 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/04 18:57:38 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expand.h"

static void	ft_expand_str(char **str)
{
	t_list	*expansion;
	char	*tmp;

	expansion = NULL;
	ft_expand_env(&expansion, *str);
	ft_expand_backslashs(&expansion);
	ft_quote_removal(expansion);
	tmp = *str;
	*str = ft_expanded_str(expansion);
	free(tmp);
	ft_lstclear(&expansion, ft_free_expansion);
}

static void	ft_expand_args(char **args)
{
	while (*args)
		ft_expand_str(args++);
}

static void	ft_expand_redirs(t_redirect **redirs)
{
	if (!redirs)
		return ;
	while (*redirs)
	{
		ft_expand_str(&((*redirs)->filename));
		redirs++;
	}
}

void	ft_expand(t_list *parsed)
{
	t_command	*command;

	while (parsed)
	{
		command = (t_command *)parsed->content;
		ft_expand_args(command->args);
		ft_expand_redirs(command->redirects);
		parsed = parsed->next;
	}
}
