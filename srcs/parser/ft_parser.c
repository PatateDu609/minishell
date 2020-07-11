/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:02:45 by gboucett          #+#    #+#             */
/*   Updated: 2020/07/11 23:28:28 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_sep(char *command, int type)
{
	if (type == PARSER_TOKEN_SEPARATOR)
		return (ft_strchr(command, ';') ? 1 : 0);
	else if (type == PARSER_TOKEN_PIPE)
		return (ft_strchr(command, '|') ? 1 : 0);
	else if (type == PARSER_TOKEN_REDIRECT)
		return (ft_strnstr(command, ">>", ft_strlen(command)) ||
			ft_strchr(command, '<') || ft_strchr(command, '>'));
	else if (type == PARSER_TOKEN_CMD || type == PARSER_TOKEN_ARGS)
		return (ft_strchr(command, ' ') ? 1 : 0);
	else
		return (1);
}

char		*ft_get_major(char *command, char **sep)
{
	char	*types[4];
	int		i;

	types[0] = "COMMAND"; // cat
	types[1] = "ARGUMENTS"; // " "
	types[2] = "REDIRECT"; // < > >>
	types[3] = "PIPELINE"; // |
	types[4] = "SEPARATOR"; // ;
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

t_btree		*ft_parser(char *command)
{
	(void)command;
	// t_btree		*parsed;

	// if (!(parsed = ft_btree_create_node("")))

	return (NULL);
}
