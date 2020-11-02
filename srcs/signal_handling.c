/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:39:12 by rapha             #+#    #+#             */
/*   Updated: 2020/11/02 11:14:02 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig;

void	ft_sigquit(int sig)
{
	ft_putstr_fd("Quit : ", 2);
	ft_putnbr_fd(sig, 2);
	ft_putchar_fd('\n', 2);
	g_sig = SIGCAUGHT + sig;
}

void	ft_sigint(int sig)
{
	ft_putchar_fd('\n', 2);
	g_sig = SIGCAUGHT + sig;
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
