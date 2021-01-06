/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:22:24 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 19:51:08 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

static char	*ft_prepare_return(char *command, char *found)
{
	char	*result;
	char	*tmp;

	if (*found == '#' && (found == command || *(found - 1) == ' '))
	{
		result = ft_strndup(command, found - command);
		tmp = result;
		result = ft_strtrim(result, " ");
		free(tmp);
	}
	else
		result = ft_strtrim(command, " ");
	return (result);
}

char		*ft_init_parsing(char *command)
{
	char	*found;

	found = command;
	while (*found)
	{
		if (*found == '\\')
			found += 2;
		if (*found == '\'' || *found == '"')
		{
			ft_skip_quotes(&found, ft_ternaryi(*found == '"', '"', '\''));
			found++;
		}
		if (*found == '#')
			break ;
		if (*found)
			found++;
	}
	return (ft_prepare_return(command, found));
}
