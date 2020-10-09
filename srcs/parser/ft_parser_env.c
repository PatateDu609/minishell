/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 22:26:00 by gboucett          #+#    #+#             */
/*   Updated: 2020/10/09 23:31:27 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_exec.h"

static char		*ft_get_words(char **command)
{
	size_t	len;
	char	*result;
	char	*found;

	result = 0;
	found = ft_strchr(*command, '$');
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

	result = ft_strdup("");
	while (*command)
	{
		tmp = result;
		tmp1 = ft_get_words(&command);
		result = ft_strjoin(result, tmp1);
		free(tmp);
		free(tmp1);
		if (*command == '$')
		{
			tmp1 = ft_get_name(&command);
			tmp = getquoted(getvar(env, tmp1));
			printf("tmp : %s\n", tmp);
			free(tmp1);
			tmp1 = result;
			result = ft_strjoin(result, tmp);
			free(tmp);
			free(tmp1);
		}
	}
	return (result);
}
