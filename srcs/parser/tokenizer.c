/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 22:02:25 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/03 15:08:23 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_count_tokens(char *str, char **op)
{
	size_t	tokens;
	size_t	len;
	char	*found;
	char	*saved;

	saved = str;
	tokens = (ft_find_next_op(str, op, NULL) != str);
	while (*str)
	{
		found = ft_find_next_op(str, op, &len);
		if (found)
		{
			tokens += 1 + (str - found != 0);
			str = found + len;
		}
		else
			break ;
	}
	if (ft_is_operator(saved + (ft_strlen(saved) - 2), op))
		tokens--;
	if (ft_strlen(str) && ft_strlen(str) != ft_strlen(saved))
		tokens++;
	return (tokens);
}

size_t	ft_count_spaces(char *str)
{
	size_t	len;

	len = (*str != ' ' && *str);
	while (*str)
	{
		if (*str == '\\')
			str++;
		else if (*str == '\'')
			ft_skip_quotes(&str, '\'');
		else if (*str == '"')
			ft_skip_quotes(&str, '"');
		else if (*str == ' ')
		{
			len++;
			while (*str == ' ')
				str++;
			str--;
		}
		str++;
	}
	return (len);
}

char	*ft_get_word(char **str)
{
	char	*result;
	size_t	len;
	size_t	i;

	len = ft_wordlen(*str);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = (*str)[i];
		i++;
	}
	*str += len + (len < ft_strlen(*str));
	while (**str && **str == ' ')
		*str += 1;
	return (result);
}

char	*ft_get_token(char **str, char **op)
{
	char	*found;
	char	*result;
	size_t	len;

	found = ft_find_next_op(*str, op, NULL);
	if (!found)
		return (ft_strdup(*str));
	len = found - *str;
	result = ft_substr(*str, 0, len);
	if (!ft_strlen(result))
	{
		free(result);
		return (NULL);
	}
	*str += len;
	return (result);
}

char	*ft_get_operator(char **str, char **op)
{
	char	*found;
	char	*result;
	size_t	len;

	found = ft_find_next_op(*str, op, &len);
	if (!found)
	{
		*str += ft_strlen(*str);
		return (NULL);
	}
	result = ft_substr(*str, 0, len);
	*str += len;
	return (result);
}
