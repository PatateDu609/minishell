/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 13:15:33 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/31 16:04:41 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include "ft_parser.h"

void	ft_merge_env(void)
{
	char	**merged;
	char	*parts[3];
	size_t	len;
	size_t	i;

	len = ft_size_splitted(g_env->names);
	i = 0;
	merged = ft_calloc(len + 1, sizeof(char *));
	if (!merged)
		return ;
	parts[2] = NULL;
	while (i < len)
	{
		parts[0] = g_env->names[i];
		parts[1] = g_env->values[i];
		merged[i++] = ft_strjoin_arr(parts, '=');
	}
	free_splitted(g_env->merged);
	g_env->merged = merged;
}
