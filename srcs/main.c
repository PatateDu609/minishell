/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 17:15:04 by gboucett          #+#    #+#             */
/*   Updated: 2020/07/09 18:04:46 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ctrl_c(int signal)
{
	(void)signal;
}

void	ctrl_d(int signal)
{
	(void)signal;
}

int		main()
{
	if (signal(SIGINT, ctrl_c) == SIG_ERR)
	{
		ft_printf("Invalid signal.");
		return (-1);
	}
	if (signal(SIGQUIT, ctrl_d) == SIG_ERR)
	{
		ft_printf("Invalid signal.");
		return (-1);
	}
	printf("Hello World !\n");
	return (0);
}
