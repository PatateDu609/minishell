/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 07:43:31 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 18:29:08 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_debug.h"

void	ft_print_env(void)
{
	size_t	i;

	dprintf(g_fd, "---------------------------------------------------\n");
	i = 0;
	dprintf(g_fd, "\033[38;5;196mValues :\033[0m\n");
	while (g_env->names[i])
	{
		dprintf(g_fd,
			"  - \033[38;5;166m%s\033[0m -> \033[38;5;206m%s\033[0m\n",
			g_env->names[i], g_env->values[i]);
		i++;
	}
	i = 0;
	if (g_env->paths)
	{
		dprintf(g_fd, "\n\n\033[38;5;196mPaths :\033[0m\n");
		while (g_env->paths[i])
		{
			dprintf(g_fd, "  - \033[38;5;206m%s\033[0m\n", g_env->paths[i]);
			i++;
		}
	}
	else
		dprintf(g_fd,
			"\n\n\033[38;5;196mPaths :\033[0m \033[38;5;206mNone\033[0m\n");
}
