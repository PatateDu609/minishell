/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 22:00:47 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/09 00:12:15 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_quote_case(char **token, int *result)
{
	*result = 1;
	if (**token == '\'')
		ft_skip_quotes(token, '\'');
	else
		ft_skip_quotes(token, '"');
	if (**token)
		*result = 0;
}

int			ft_check_quotes(char *token)
{
	int	result;

	while (*token)
	{
		result = 0;
		if (*token == '\\')
		{
			token++;
			if (!*token)
				return (ft_print_error("newline"));
		}
		else if (*token == '\'' || *token == '"')
			ft_check_quote_case(&token, &result);
		if (!*token)
			break ;
		token++;
	}
	if (result)
		ft_print_error("newline");
	return (!result);
}

int			ft_check_last(char *last_token, char **op, size_t len)
{
	int	result;

	result = 1;
	if (*last_token == ';' && len > 1)
		result = 1;
	else if (*last_token == ';')
		result = ft_print_error(";");
	else if (ft_is_operator(last_token, op))
		result = ft_print_error("newline");
	else
		result = ft_check_quotes(last_token);
	free(op);
	return (result);
}

int			ft_check_validity(char **litteral)
{
	char	**op;
	int		first;
	int		mode;
	int		old;
	size_t	len;

	if (!*litteral)
		return (0);
	op = ft_generate_op();
	len = ft_size_splitted(litteral);
	mode = ft_is_operator(*litteral++, op);
	first = !mode;
	while (*litteral && first)
	{
		old = mode;
		mode = ft_is_operator(*litteral++, op);
		if (mode && old)
			break ;
	}
	if (*litteral)
	{
		free(op);
		return (ft_print_error(*(litteral - 1)));
	}
	return (ft_check_last(*(litteral - 1), op, len));
}
