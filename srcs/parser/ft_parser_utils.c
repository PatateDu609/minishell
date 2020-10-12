/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:28:53 by gboucett          #+#    #+#             */
/*   Updated: 2020/10/12 03:22:59 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

#ifndef BONUS

char	*max(char *a, char *b)
{
	if (!a && !b)
		return (NULL);
	if (!a)
		return (b);
	if (!b)
		return (a);
	return (ft_strlen(a) > ft_strlen(b) ? a : b);
}

int		ft_get_token_len(char *res)
{
	char	c;
	int		len;

	c = res[0];
	len = ft_strlen(res);
	if (c == '<' || c == '|' || c == ';' || (c == '>' && (len == 1 || res[1] != '>')))
		return (1);
	return (2);
}

char	*ft_get_sep(char *command, int type)
{
	int		len;
	char	*s[3];
	char	*res;

	if (!command)
		return (type == PARSER_TOKEN_CMD ? ft_strdup(" ") : NULL);
	len = ft_strlen(command);
	if (type == PARSER_TOKEN_REDIRECT)
	{
		s[0] = ft_strnstr(command, "<", len);
		s[1] = ft_strnstr(command, ">>", len);
		s[2] = ft_strnstr(command, ">", len);
		if ((res = max(s[0], max(s[1], s[2]))))
			return (ft_substr(res, 0, ft_get_token_len(res)));
	}
	else if (type == PARSER_TOKEN_PIPE)
		return (ft_strdup("|"));
	else if (type == PARSER_TOKEN_SEPARATOR)
		return (ft_strdup(";"));
	else if (type == PARSER_TOKEN_CMD || type == PARSER_TOKEN_ARGS)
		return (ft_strdup(" "));
	return (NULL);
}

// int			ft_check_sep(char *command, int type)
// {
// 	if (type == PARSER_TOKEN_SEPARATOR)
// 		return (ft_strchr(command, ';') ? 1 : 0);
// 	else if (type == PARSER_TOKEN_PIPE)
// 		return (ft_strchr(command, '|') ? 1 : 0);
// 	else if (type == PARSER_TOKEN_REDIRECT)
// 		return (ft_strnstr(command, ">>", ft_strlen(command)) ||
// 				ft_strchr(command, '<') || ft_strchr(command, '>'));
// 	else if (type == PARSER_TOKEN_CMD || type == PARSER_TOKEN_ARGS)
// 		return (ft_strchr(command, ' ') ? 1 : 0);
// 	else
// 		return (1);
// }

int			ft_check_sep(char *command, int type)
{
	char	types[5];
	int		i;
	int		mode;

	types[PARSER_TOKEN_CMD] = ' ';
	types[PARSER_TOKEN_ARGS] = ' ';
	types[PARSER_TOKEN_PIPE] = '|';
	types[PARSER_TOKEN_SEPARATOR] = ';';
	i = 0;
	if (command[ft_strlen(command) - 1] == '\\')
		return (-1);
	while (command[i])
	{
		if (command[i] == '\\')
			i += 2;
		if (command[i] == '"' || command[i] == '\'')
		{
			mode = (command[i] == '"');
			i++;
			while (command[i] && ((mode && command[i] != '"') || (!mode && command[i] != '\'')))
				i++;
			if (!command[i])
				return (-2);
		}
		if ((type != PARSER_TOKEN_REDIRECT && command[i] == types[type]) ||
			(type == PARSER_TOKEN_REDIRECT && (command[i] == '<' || command[i] == '>')))
		{
			return (1);
		}
		i++;
	}
	return (type == PARSER_TOKEN_CMD);
}

char		*ft_get_major(char *command, char **sep)
{
	char	*types[5];
	int		i;

	types[0] = COMMAND_STR;
	types[1] = ARGUMENT_STR;
	types[2] = REDIRECTION_STR;
	types[3] = PIPELINE_STR;
	types[4] = SEPARATOR_STR;

	i = 4;
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
