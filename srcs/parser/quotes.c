/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 22:08:46 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/04 17:52:30 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

size_t	ft_skip_quotes(char **str, char quote)
{
	char	*current;
	size_t	len;

	current = *str;
	current++;
	while (*current && *current != quote)
	{
		if (quote == '\"' && *current == '\\')
			current++;
		current++;
	}
	len = current - *str;
	*str = current;
	return (len);
}
