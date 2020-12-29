/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 22:07:21 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/29 22:08:10 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_size_quoted(char *str)
{
	size_t	result;

	result = 0;
	while (*str)
	{
		if (*str == '\\' || *str == '\'' || *str == '"')
			str++;
		if (!*str)
			break ;
		str++;
		result++;
	}
	return (result);
}

size_t	ft_size_splitted(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

size_t	ft_size_redirs(t_redirect **redirs)
{
	size_t	i;

	i = 0;
	if (redirs)
		while (redirs[i])
			i++;
	return (i);
}

size_t	ft_wordlen(char *str)
{
	size_t	len;

	len = 0;
	while (*str && *str != ' ')
	{
		if (*str == '\\')
		{
			str++;
			len++;
		}
		else if (*str == '\'')
			len += ft_skip_quotes(&str, '\'');
		else if (*str == '"')
			len += ft_skip_quotes(&str, '"');
		str++;
		len++;
	}
	return (len);
}
