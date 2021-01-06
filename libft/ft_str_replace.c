/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 12:49:54 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 19:34:41 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	ft_count_matches(const char *str, const char *substr)
{
	size_t	count;
	char	*found;
	size_t	sstr_len;

	count = 0;
	sstr_len = ft_strlen(substr);
	while (*str)
	{
		found = ft_strnstr(str, substr, ft_strlen(str));
		if (!found)
			break ;
		count++;
		str = found + sstr_len;
	}
	return (count);
}

char			*ft_str_replace(char *str, char *substr, char *rep)
{
	size_t	matches;
	char	*result;
	char	*before;
	char	*found;
	size_t	len;

	len = ft_strlen(rep);
	matches = ft_count_matches(str, substr);
	result = ft_calloc(ft_strlen(str) + matches * (len - ft_strlen(substr)) + 1,
			sizeof(char));
	if (!result)
		return (0);
	while (*str)
	{
		found = ft_strnstr(str, substr, ft_strlen(str));
		before = ft_substr(str, 0, found - str);
		ft_memcpy(result + ft_strlen(result), before, ft_strlen(before));
		free(before);
		if (!found)
			break ;
		ft_memcpy(result + ft_strlen(result), rep, ft_strlen(rep));
		str = found + ft_strlen(substr);
	}
	return (result);
}

static size_t	ft_get_len(char *str, char *sub, char *rep, int af)
{
	char	*found;
	char	*after;

	found = ft_strnstr(str, sub, ft_strlen(str));
	after = found + ft_strlen(sub);
	if (af)
		return (ft_strlen(str) + ft_strlen(rep) - ft_strlen(sub) + 1);
	else
		return (ft_strlen(str) + ft_strlen(rep) - ft_strlen(sub)
			- ft_strlen(after) + 1);
}

char			*ft_str_replace_first(char *str, char *sub, char *rep, int af)
{
	char	*result;
	char	*found;
	char	*before;
	char	*after;

	found = ft_strnstr(str, sub, ft_strlen(str));
	if (!found)
		return (ft_strdup(str));
	after = found + ft_strlen(sub);
	result = ft_calloc(ft_get_len(str, sub, rep, af) + 1, sizeof(char));
	if (!result)
		return (NULL);
	before = ft_substr(str, 0, found - str);
	if (!before)
	{
		free(result);
		return (NULL);
	}
	ft_memcpy(result + ft_strlen(result), before, ft_strlen(before));
	ft_memcpy(result + ft_strlen(result), rep, ft_strlen(rep));
	if (af)
		ft_memcpy(result + ft_strlen(result), after, ft_strlen(after));
	free(before);
	return (result);
}
