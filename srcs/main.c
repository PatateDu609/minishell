/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 17:15:04 by gboucett          #+#    #+#             */
/*   Updated: 2020/07/10 16:43:39 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS
# include "minishell.h"
#else
# include "minishell_bonus.h"
#endif

void	ctrl_c(int signal)
{
	(void)signal;
}

void	ctrl_d()
{
	ft_printf("exit");
	exit(0);
}

int		main()
{
	if (signal(SIGINT, ctrl_c) == SIG_ERR)
	{
		ft_printf("Invalid signal.");
		return (-1);
	}

	char *result;

	while(1)
	{
		get_next_line(STDIN_FILENO, &result);
		if (*result == 0)
			ctrl_d();
	}
	return (0);
}
