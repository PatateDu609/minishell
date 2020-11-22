/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:39:12 by rapha             #+#    #+#             */
/*   Updated: 2020/11/13 12:26:33 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sig;
int		g_exit_code;
pid_t	g_pid;

void	ft_sigquit(int sig)
{
	g_exit_code = 3;
	if (g_pid == 0)
	{
		g_exit_code = 0;
	}
	// ft_putstr_fd("Quit : ", 2);
	// ft_putnbr_fd(sig, 2);
	// ft_putchar_fd('\n', 2);
	kill(g_pid, g_exit_code);
	g_sig = SIGCAUGHT + sig;
}

void	ft_sigint(int sig)
{
	g_exit_code = 2;
	ft_putchar_fd('\n', 2);
	if (g_pid == 0)
	{
		g_exit_code = 130;
		ft_printf("\033[31m\033[1mminishell :>\033[0m\033[35m\033[0m ");
	}
	else
		kill(g_pid, g_exit_code);
	g_sig = SIGCAUGHT + sig;
	g_exit_code = g_sig;
}

void	ft_signalhandler_enable(void)
{
	signal(SIGQUIT, ft_sigquit);
	signal(SIGINT, ft_sigint);
}

void	ft_signalhandler_disable(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
