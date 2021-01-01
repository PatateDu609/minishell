/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 04:57:50 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/01 05:01:57 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

void	ft_echo(t_command *command)
{
	int		start;
	int		newline;

	start = ft_get_echo_start(command->args);
	if (!command->args[start])
		return ;
	newline = (start == 1);
	ft_printf("%s", command->args[start++]);
	while (command->args[start])
		ft_printf(" %s", command->args[start++]);
	if (newline)
		ft_printf("\n");
}
