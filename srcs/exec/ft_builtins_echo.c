/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 04:57:50 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/05 18:14:41 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

void	ft_echo(t_command *command)
{
	int		start;
	int		newline;

	start = ft_get_echo_start(command->args);
	newline = (start == 1);
	if (command->args[start])
	{
		ft_printf("%s", command->args[start++]);
		while (command->args[start])
			ft_printf(" %s", command->args[start++]);
	}
	if (newline)
		ft_printf("\n");
	g_exit_code = 0;
}
