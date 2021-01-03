/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 04:50:03 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/03 17:50:59 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

void	ft_exit(t_command *command)
{
	char	*arg;
	int		value;

	arg = command->args[1];
	if (arg)
	{
		value = ft_atoi(arg);
		if (0 <= value && value <= 255)
			g_exit_code = value;
		else if (value > 256)
			g_exit_code = value % 256;
		else
			g_exit_code = value % 256 + 256;
	}
	ft_apply_exit();
}
