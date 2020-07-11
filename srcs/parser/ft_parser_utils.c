/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:28:53 by gboucett          #+#    #+#             */
/*   Updated: 2020/07/11 23:21:35 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

char	*ft_get_sep(char *command, int type)
{
	int		len;

	len = ft_strlen(command);
	if (type == PARSER_TOKEN_REDIRECT)
	{
		if (ft_strnstr(command, "<", len))
			return (ft_strdup("<"));
		else if (ft_strnstr(command, ">>", len))
			return (ft_strdup(">>"));
		else if (ft_strnstr(command, ">", len))
			return (ft_strdup(">"));
	}
	else if (type == PARSER_TOKEN_PIPE)
		return (ft_strdup("|"));
	else if (type == PARSER_TOKEN_SEPARATOR)
		return (ft_strdup(";"));
	else if (type == PARSER_TOKEN_CMD || type == PARSER_TOKEN_ARGS)
		return (ft_strdup(" "));
	return (NULL);
}

char	*ft_subcmd(char *command, char *major, int side)
{
	char	*pos;
	char	*temp;
	char	*result;
	char	*trimmed;

	pos = ft_strnstr(command, major, ft_strlen(command));
	if (!side)
		temp = ft_substr(command, 0, pos - command);
	else
		temp = ft_substr(pos, 0, ft_strlen(pos));
	trimmed = ft_strjoin(major, " ");
	result = ft_strtrim(temp, trimmed);
	free(trimmed);
	free(temp);
	return (result);
}
