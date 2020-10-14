/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 22:26:00 by gboucett          #+#    #+#             */
/*   Updated: 2020/10/14 15:35:53 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_exec.h"

static char		*ft_strchr_backslash(char *str, char c)
{
	while (*str && *str != c)
		if (*str++ == '\\')
			str += 1;
	return (*str == c ? str : NULL);
}

static char		*ft_get_words(char **command, int *mode)
{
	size_t	len;
	char	*result;
	char	*found;
	char	*str;
	int		searching;

	result = 0;
	found = ft_strchr_backslash(*command, '$');
	str = *command;
	searching = 0;
	while (str < found)
	{
		if ((!searching || searching == 1) && *str == '"')
		{
			*mode += 1;
			searching = 1;
		}
		else if ((!searching || searching == 2) && *str == '\'')
		{
			*mode += 1;
			searching = 2;
		}
		str++;
	}
	len = found ? (size_t)(found - *command) : ft_strlen(*command);
	if (!(result = ft_substr(*command, 0, len)))
		return (NULL);
	*command += len;
	return (result);
}

static char		*ft_get_name(char **command)
{
	size_t	len;
	char	*name;

	len = 0;
	*command += 1;
	if (ft_isdigit(**command))
	{
		*command += 1;
		return (ft_strdup(""));
	}
	while ((*command)[len] && (ft_isalnum((*command)[len]) ||
		(*command)[len] == '_'))
		len++;
	if (!(name = ft_substr(*command, 0, len)))
		return (NULL);
	*command += len;
	return (name);
}

static char		*getquoted(char *to_quote)
{
	char	*tmp;
	char	*result;

	result = ft_strjoin("\"", to_quote);
	tmp = result;
	result = ft_strjoin(result, "\"");
	free(tmp);
	free(to_quote);
	return (result);
}

char			*ft_parse_env(t_env *env, char *command)
{
	char	*result;
	char	*tmp;
	char	*tmp1;
	char	*saved;
	int		mode;

	result = ft_strdup("");
	command = ft_strtrim(command, " ");
	saved = command;
	mode = 0;
	while (*command)
	{
		tmp = result;
		tmp1 = ft_get_words(&command, &mode);
		result = ft_strjoin(result, tmp1);
		free(tmp);
		free(tmp1);
		if (*command == '$')
		{
			tmp1 = ft_get_name(&command);
			tmp = !(mode % 2) ? getquoted(getvar(env, tmp1)) : getvar(env, tmp1);
			free(tmp1);
			tmp1 = result;
			result = ft_strjoin(result, tmp);
			free(tmp);
			free(tmp1);
		}
	}
	free(saved);
	return (result);
}
