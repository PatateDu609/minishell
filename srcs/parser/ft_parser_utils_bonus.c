/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:28:53 by gboucett          #+#    #+#             */
/*   Updated: 2020/10/20 15:06:58 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

#ifdef BONUS

int	ft_check_sep(char *command, int type)
{
	if (!command)
		return (type == PARSER_TOKEN_CMD);
	if (type == PARSER_TOKEN_SEPARATOR)
		return (ft_strchr(command, ';') ? 1 : 0);
	else if (type == PARSER_TOKEN_PIPE)
		return (ft_strchr(command, '|') ? 1 : 0);
	else if (type == PARSER_TOKEN_OPERATOR)
		return (ft_strnstr(command, "||", ft_strlen(command)) ||
			ft_strnstr(command, "&&", ft_strlen(command)));
	else if (type == PARSER_TOKEN_REDIRECT)
		return (ft_strnstr(command, ">>", ft_strlen(command)) ||
			ft_strchr(command, '<') || ft_strchr(command, '>'));
	else if (type == PARSER_TOKEN_CMD || type == PARSER_TOKEN_ARGS)
		return (ft_strchr(command, ' ') ? 1 : 0);
	else
		return (1);
}

char		*ft_get_sep(char *command, int type)
{
	int		len;

	if (!command)
		return (type == PARSER_TOKEN_CMD ? ft_strdup(" ") : NULL);
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
	else if (type == PARSER_TOKEN_OPERATOR && ft_strnstr(command, "||", len))
		return (ft_strdup("||"));
	else if (type == PARSER_TOKEN_OPERATOR && ft_strnstr(command, "&&", len))
		return (ft_strdup("&&"));
	else if (type == PARSER_TOKEN_PIPE)
		return (ft_strdup("|"));
	else if (type == PARSER_TOKEN_SEPARATOR)
		return (ft_strdup(";"));
	else if (type == PARSER_TOKEN_CMD || type == PARSER_TOKEN_ARGS)
		return (ft_strdup(" "));
	return (NULL);
}

char		*ft_get_major(char *command, char **sep)
{
	char	*types[6];
	int		i;

	types[0] = "COMMAND";
	types[1] = "ARGUMENTS";
	types[2] = "REDIRECT";
	types[3] = "PIPELINE";
	types[4] = "OPERATOR";
	types[5] = "SEPARATOR";
	i = 5;
	while (i >= 0)
	{
		if (ft_check_sep(command, i))
		{
			*sep = ft_get_sep(command, i);
			return (types[i]);
		}
		i--;
	}
	*sep = ft_strdup(" ");
	return (types[0]);
}

#endif
