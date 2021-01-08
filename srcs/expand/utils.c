/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:34:27 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/09 00:16:27 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expand.h"

char	*ft_strchr_quoted(char *str, char c, int *in_quotes)
{
	while (*str)
	{
		if (*str == '"')
			*in_quotes = !*in_quotes;
		if (!*in_quotes && *str == '\'')
		{
			ft_skip_quotes(&str, '\'');
			str++;
		}
		if (c != '\\' && *str == '\\')
			str += 2;
		if (*str == c)
			return (str);
		if (*str)
			str++;
	}
	return (NULL);
}

t_list	*ft_create_expansion(char *str, int expanded)
{
	t_expansion		*expansion;
	t_list			*node;

	expansion = ft_calloc(1, sizeof(t_expansion));
	if (!expansion)
		return (NULL);
	expansion->expanded = expanded;
	expansion->str = str;
	node = ft_lstnew(expansion);
	if (!node)
		free(expansion);
	return (node);
}

int		ft_has_special_meaning(int quoted, char c)
{
	return (c == '$' || (!quoted && c == '\'') || c == '"' || c == '\\'
			|| (!quoted && c == '#') || (!quoted && c == '|')
			|| (!quoted && c == ';') || (!quoted && c == '<')
			|| (!quoted && c == '>'));
}

void	ft_append_last(t_list **lst, char *str)
{
	t_list	*node;

	node = ft_create_expansion(ft_strdup(str), 0);
	ft_lstadd_back(lst, node);
}

void	ft_connect(t_list **target, t_list *newlst)
{
	t_list	*last;

	last = ft_lstlast(newlst);
	if (!last)
		return ;
	if ((*target)->next)
		(*target)->next->previous = last;
	last->next = (*target)->next;
	newlst->previous = (*target)->previous;
	if ((*target)->previous)
		(*target)->previous->next = newlst;
	ft_free_expansion((*target)->content);
	free(*target);
	*target = newlst;
}
