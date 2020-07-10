/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 17:15:04 by gboucett          #+#    #+#             */
/*   Updated: 2020/07/10 19:04:40 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS
# include "minishell.h"
#else
# include "minishell_bonus.h"
#endif

int		g_skip = 0;

void	ctrl_c(int signal)
{
	(void)signal;
	g_skip = 1;
}

void	ctrl_d()
{
	ft_printf("exit");
	exit(0);
}

void	ctrl_q(int signal)
{
	(void)signal;
}

void minishell()
{
	char	*command;

	while(1)
	{
		ft_printf("minishell :> ");
		if (g_skip)
			continue ;
		get_next_line(STDIN_FILENO, &command);
		if (*command == 0)
			ctrl_d();
		// ft_exec(ft_parser(command));
	}
}

int		main(int ac, char **av, char **env)
{
	// (void) ac;
	// (void) av;
	// (void) env;
	// if (signal(SIGINT, ctrl_c) == SIG_ERR)
	// {
	// 	ft_printf("Invalid signal.");
	// 	return (-1);
	// }
	// if (signal(SIGQUIT, ctrl_q) == SIG_ERR)
	// {
	// 	ft_printf("Invalid signal.");
	// 	return (-1);
	// }

	// minishell();
	(void) ac;
	(void) av;
	(void) env;

	printf("%p\n", ft_get_major("cat"));
	return (0);
}
