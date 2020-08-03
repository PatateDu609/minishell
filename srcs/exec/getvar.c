/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 23:33:48 by gboucett          #+#    #+#             */
/*   Updated: 2020/07/28 14:18:47 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

char	*getvar(char **ev, char *var)
{
	char	**splitted;
	char	*result;
	size_t	len;

	result = 0;
	len = ft_strlen(var);
	while (*ev)
	{
		splitted = ft_split(*ev, '=');
		if (ft_strlen(splitted[0]) == len && !ft_strncmp(splitted[0], var, len))
			result = ft_strdup(splitted[1]);
		free_splitted(splitted);
		if (result)
			break;
		ev++;
	}
	return (result);
}
