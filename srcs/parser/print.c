/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 21:56:12 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 19:52:40 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_splitted(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		ft_printf("%s\n", strs[i++]);
}

int		ft_print_error(char *error)
{
	write(2, program_invocation_short_name,
		ft_strlen(program_invocation_short_name));
	write(2, ": syntax error near unexpected token `", 38);
	write(2, error, ft_strlen(error));
	write(2, "'\n", 2);
	return (0);
}
