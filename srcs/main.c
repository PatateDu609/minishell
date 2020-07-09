/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 17:15:04 by gboucett          #+#    #+#             */
/*   Updated: 2020/07/09 13:48:28 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ctrl_c(int signal)
{

}

void	ctrl_q(int signal)
{
	
}

int		main()
{
	if (signal(SIGINT, ctrl_c) == SIG_ERR)
	{
		ft_printf("Invalid signal.");
		return (-1);
	}
	if (signal(SIGQUIT, ctrl_q) == SIG_ERR)
	{
		ft_printf("Invalid signal.");
		return (-1);
	}
	printf("Hello World !\n");
	return (0);
}
