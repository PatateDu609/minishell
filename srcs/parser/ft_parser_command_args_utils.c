/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_command_args_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 16:26:59 by gboucett          #+#    #+#             */
/*   Updated: 2020/10/14 15:34:30 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

static int	ft_skip_quotes(char **command)
{
	int		mode;
	int		len;
	int		on;

	mode = (**command == '"');
	*command += 1;
	len = 0;
	on = 0;
	while ((mode && **command != '"') || (!mode && **command != '\''))
	{
		*command += 1;
		len++;
		on = 1;
	}
	if (on)
		len--;
	return (len);
}

static int	ft_count_tokens(char *command)
{
	int		count;

	count = 1;
	while (*command)
	{
		if (*command == '\\')
			command++;
		else if (*command == '"' || *command == '\'')
			ft_skip_quotes(&command);
		else if (*command == ' ')
		{
			count++;
			while (*command && *command == ' ')
				command++;
			command--;
		}
		command++;
	}
	return (count);
}

static char	*ft_get_token(char **command)
{
	size_t	len;
	char	*result;
	char	*saved;
	size_t	i;

	len = 0;
	saved = *command;
	while (**command && **command != ' ')
	{
		if (**command == '\\')
			*command += 1;
		else if (**command == '\'' || **command == '\"')
			len += ft_skip_quotes(command);
		len++;
		*command += 1;
	}
	if (!ft_assign(&result, (char *)ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	i = 0;
	while (i < len && *saved)
	{
		if (*saved == '\'' || *saved == '"' || *saved == '\\')
			saved++;
		result[i] = *saved;
		i++;
		saved++;
	}
	while (**command && **command == ' ')
		*command += 1;
	return (result);
}

char	**ft_split_args(char *command)
{
	char	**result;
	int		count;
	int		i;

	count = ft_count_tokens(command);
	if (!ft_assign(&result, ft_calloc(count + 1, sizeof(char *))))
		return (NULL);
	i = 0;
	while (i < count)
	{
		if (!ft_assign(&result[i], ft_get_token(&command)))
		{
			i = 0;
			while (result[i])
				free(result[i++]);
			free(result);
			return (NULL);
		}
		i++;
	}
	return (result);
}
