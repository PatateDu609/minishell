/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 22:08:46 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/29 22:24:34 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_skip_quotes(char **str, char quote)
{
	char	*current;
	size_t	len;

	current = *str;
	current++;
	while (*current && *current != quote)
		current++;
	len = current - *str;
	*str = current;
	return (len);
}

char	*ft_expand_quoted(char *str)
{
	char	*result;
	size_t	len;
	size_t	i;

	len = ft_size_quoted(str);
	result = ft_calloc(len + 1, sizeof(char *));
	i = 0;
	while (*str)
	{
		if (*str == '\\' || *str == '\'' || *str == '"')
			str++;
		if (!*str)
			break ;
		result[i++] = *str++;
	}
	return (result);
}
