/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 13:15:33 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 19:42:03 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include "ft_parser.h"

void		ft_merge_env(char **names)
{
	char	**merged;
	char	**source;
	char	*parts[3];
	size_t	len;
	size_t	i;

	source = g_env->names;
	if (names)
		source = names;
	len = ft_size_splitted(source);
	i = 0;
	merged = ft_calloc(len + 1, sizeof(char *));
	if (!merged)
		return ;
	parts[2] = NULL;
	while (i < len)
	{
		parts[0] = source[i];
		parts[1] = ft_getvar(source[i]);
		merged[i++] = ft_strjoin_arr(parts, '=');
	}
	free_splitted(g_env->merged);
	g_env->merged = merged;
}

static void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

char		**ft_sort_env(void)
{
	char	**sorted;
	size_t	i;
	size_t	j;
	size_t	len;

	len = ft_size_splitted(g_env->names);
	sorted = ft_calloc(len + 1, sizeof(char *));
	ft_memcpy(sorted, g_env->names, sizeof(char *) * len);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - 1)
		{
			if (ft_strcmp(sorted[j + 1], sorted[j]) < 0)
				ft_swap(sorted + j, sorted + (j + 1));
			j++;
		}
		i++;
	}
	return (sorted);
}
