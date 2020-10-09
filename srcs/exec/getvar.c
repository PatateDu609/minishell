/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 23:33:48 by gboucett          #+#    #+#             */
/*   Updated: 2020/10/09 23:20:51 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

char	*getvar(t_env *env, char *var)
{
	char	**splitted;
	char	*result;
	size_t	len;
	char	**ev;

	if (!ft_strcmp(var, "?"))
		return (ft_itoa(env->vlast));
	result = 0;
	len = ft_strlen(var);
	ev = env->env;
	while (*ev)
	{
		splitted = ft_split(*ev, '=');
		if (ft_strlen(splitted[0]) == len && !ft_strncmp(splitted[0], var, len))
			result = ft_strjoin_arr(splitted + 1, '=');
		free_splitted(splitted);
		if (result)
			break;
		ev++;
	}
	return (result);
}
