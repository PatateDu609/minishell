/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 11:16:17 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/31 01:03:04 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

char	*ft_get_name(char *str)
{
	char	*result;
	char	*tmp;
	int		len;

	len = 0;
	str++;
	if (ft_isdigit(*str))
		return (ft_substr(str - 1, 0, 2));
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	result = ft_substr(str, 0, len);
	tmp = result;
	result = ft_strjoin("$", result);
	free(tmp);
	return (result);
}

char	*ft_get_value(char *str)
{
	char	*val;

	if (!str)
		return (str);
	else if (ft_isdigit(str[1]))
		return ("");
	else if (!str[1])
		return (str);
	val = ft_getvar(str + 1);
	if (!val)
		return ("");
	return (val);
}

char	*ft_str_join_last(char *str, char *result)
{
	char	*tmp;

	tmp = result;
	result = ft_strjoin(result, str);
	free(tmp);
	return (result);
}

char	*ft_str_replace_var(char *str)
{
	char	*result;
	char	*tmp[2];
	char	*found;
	char	*name;
	char	*value;

	result = NULL;
	while (*str)
	{
		found = ft_strchr(str, '$');
		if (!found)
			return (ft_str_join_last(str, result));
		name = ft_get_name(found);
		value = ft_get_value(name);
		tmp[0] = result;
		tmp[1] = ft_str_replace_first(str, name, value, 0);
		result = ft_strjoin(result, tmp[1]);
		free(tmp[0]);
		free(tmp[1]);
		str = found + ft_strlen(name);
		free(name);
	}
	return (result);
}
