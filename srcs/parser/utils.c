/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 22:13:40 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/09 00:33:59 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_is_operator(char *str, char **op)
{
	while (*op)
	{
		if (ft_strstr_op(str, *op++))
			return (1);
	}
	return (0);
}

int		ft_is_redirect(char *str)
{
	if (!ft_strcmp(str, "<"))
		return (1);
	else if (!ft_strcmp(str, ">>"))
		return (2);
	else if (!ft_strcmp(str, ">"))
		return (3);
	return (0);
}

char	*ft_strstr_op(char *str, char *op)
{
	size_t	i;

	while (*str)
	{
		if (*str == '\\')
			str += 2;
		else if (*str == '\'' || *str == '"')
		{
			ft_skip_quotes(&str, ft_ternaryi(*str == '\'', '\'', '"'));
			str++;
		}
		if (!*str)
			return (NULL);
		i = 0;
		while (op[i] && *(str + i) && *(str + i) == op[i])
			i++;
		if (!op[i])
			return (str);
		str++;
	}
	return (NULL);
}

char	*ft_find_next_op(char *str, char **op, size_t *len)
{
	char	*found;
	char	*min;

	found = NULL;
	min = NULL;
	while (*op)
	{
		found = ft_strstr_op(str, *op++);
		if (found && (!min || found < min))
		{
			min = found;
			if (len)
				*len = ft_strlen(*(op - 1));
		}
	}
	return (min);
}

char	**ft_generate_op(void)
{
	char	**op;

	op = ft_calloc(6, sizeof(char *));
	op[0] = "<";
	op[1] = ">>";
	op[2] = ">";
	op[3] = "|";
	op[4] = ";";
	return (op);
}
