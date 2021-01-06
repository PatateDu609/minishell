/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:28:09 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 19:41:17 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expand.h"

static char	*ft_get_name(char *str)
{
	char	*result;
	char	*tmp;
	int		len;

	len = 0;
	str++;
	if (ft_isdigit(*str))
		return (ft_substr(str - 1, 0, 2));
	if (*str == '?')
		return (ft_strdup("$?"));
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	result = ft_substr(str, 0, len);
	tmp = result;
	result = ft_strjoin("$", result);
	free(tmp);
	return (result);
}

static char	*ft_get_value(char *str)
{
	char	*val;

	if (!str)
		return (ft_strdup(str));
	else if (ft_isdigit(str[1]))
		return (ft_strdup(""));
	else if (!str[1])
		return (ft_strdup(str));
	else if (str[1] == '?')
		return (ft_itoa(g_exit_code));
	val = ft_getvar(str + 1);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

void		ft_expand_env(t_list **lst, char *str)
{
	char	*found;
	t_list	*node;
	char	*name;
	int		in_quotes;

	in_quotes = 0;
	while (*str)
	{
		found = ft_strchr_quoted(str, '$', &in_quotes);
		if (!found)
			break ;
		name = ft_get_name(found);
		node = ft_create_expansion(ft_strndup(str, found - str), 0);
		ft_lstadd_back(lst, node);
		node = ft_create_expansion(ft_get_value(name), 1);
		ft_lstadd_back(lst, node);
		str = found + ft_strlen(name);
		free(name);
	}
	if (*str)
		ft_append_last(lst, str);
}
