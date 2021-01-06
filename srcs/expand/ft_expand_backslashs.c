/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_backslashs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 03:49:04 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 19:40:37 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expand.h"

static t_list	*ft_get_backslashed(int in_quotes, char *found)
{
	t_list	*node;

	if (ft_has_special_meaning(in_quotes, *(found + 1)))
		node = ft_create_expansion(ft_strndup(found + 1, 1), 1);
	else
		node = ft_create_expansion(ft_strndup(found, 2), 1);
	return (node);
}

static t_list	*ft_expand_backslashs_str(char *str)
{
	t_list			*result;
	t_list			*node;
	char			*found;
	int				in_quotes;

	result = NULL;
	found = ft_strchr_quoted(str, '\\', &in_quotes);
	if (!found)
		return (NULL);
	in_quotes = 0;
	while (*str)
	{
		found = ft_strchr_quoted(str, '\\', &in_quotes);
		if (!found)
			break ;
		node = ft_create_expansion(ft_strndup(str, found - str), 0);
		ft_lstadd_back(&result, node);
		node = ft_get_backslashed(in_quotes, found);
		ft_lstadd_back(&result, node);
		str = found + 2;
	}
	if (*str)
		ft_append_last(&result, str);
	return (result);
}

void			ft_expand_backslashs(t_list **lst)
{
	t_list			*current;
	t_expansion		*expansion;

	current = *lst;
	while (current)
	{
		expansion = (t_expansion *)current->content;
		if (!expansion->expanded)
			ft_connect(&current, ft_expand_backslashs_str(expansion->str));
		*lst = current;
		current = current->next;
	}
	*lst = ft_lstfirst(*lst);
}
