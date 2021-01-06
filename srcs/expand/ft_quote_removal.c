/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_removal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:50:24 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 19:40:18 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expand.h"

static size_t	ft_count_quotes(char *str)
{
	size_t	result;

	result = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			result++;
			ft_skip_quotes(&str, '\'');
		}
		if (*str == '"')
		{
			result++;
			ft_skip_quotes(&str, '"');
		}
		if (*str == '\'' || *str == '"')
		{
			result++;
			str++;
		}
		if (*str)
			str++;
	}
	return (result);
}

static void		ft_skip_quote_char(char **str, int *mode)
{
	if ((!*mode || *mode == 1) && **str == '\'')
	{
		*mode = *mode % 2;
		*str += 1;
	}
	else if ((!*mode || *mode == 2) && **str == '"')
	{
		*mode = (*mode % 2) * 2;
		*str += 1;
	}
}

static char		*ft_remove_quotes(char *str)
{
	char	*result;
	char	*saved;
	size_t	len;
	size_t	i;
	int		mode;

	saved = str;
	if (!ft_strlen(str))
		return (str);
	len = ft_strlen(str) - ft_count_quotes(str);
	i = 0;
	mode = 0;
	result = ft_calloc(len + 1, sizeof(char));
	while (*str)
	{
		ft_skip_quote_char(&str, &mode);
		result[i++] = *str++;
	}
	free(saved);
	return (result);
}

void			ft_quote_removal(t_list *lst)
{
	t_expansion		*expansion;

	while (lst)
	{
		expansion = (t_expansion *)lst->content;
		if (!expansion->expanded)
			expansion->str = ft_remove_quotes(expansion->str);
		lst = lst->next;
	}
}
