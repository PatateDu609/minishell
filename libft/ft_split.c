/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 14:41:18 by rbourgea          #+#    #+#             */
/*   Updated: 2020/07/10 16:29:54 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		count_substrings(char const *s, char c)
{
	int		strings;
	size_t	i;

	i = 0;
	strings = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			strings++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	strings += 1;
	return (strings);
}

static	size_t	to_sep(char const *s, char c)
{
	size_t i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

void			*free_result(char **result)
{
	size_t		i;
	size_t		size;

	size = sizeof(result) / sizeof(char *);
	i = 0;
	while (i < size)
	{
		free(result[i]);
		i++;
	}
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	size_t	nbs[3];

	nbs[0] = 0;
	nbs[1] = 0;
	if (!s || !(result = malloc(sizeof(char *) * (count_substrings(s, c) + 1))))
		return (NULL);
	while (s[nbs[0]])
	{
		if (s[nbs[0]] != c && s[nbs[0]])
		{
			if (!(result[nbs[1]] = malloc(sizeof(char *)
				* (to_sep(&s[nbs[0]], c) + 1))))
				return (free_result(result));
			nbs[2] = 0;
			while (s[nbs[0]] != c && s[nbs[0]])
				result[nbs[1]][nbs[2]++] = s[nbs[0]++];
			result[nbs[1]][nbs[2]] = '\0';
			nbs[1]++;
		}
		while (s[nbs[0]] == c && s[nbs[0]])
			nbs[0]++;
	}
	result[nbs[1]] = NULL;
	return (result);
}
