/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapha <rapha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 13:34:18 by rbourgea          #+#    #+#             */
/*   Updated: 2020/11/02 12:02:06 by rapha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_defs.h"
# include "ft_parser.h"
# include "ft_exec.h"

# define SIGCAUGHT 128

void		ft_sigquit(int sigquit);
void		ft_sigint(int sigquit);
void		ft_signalhandler_enable(void);
void		ft_signalhandler_disable(void);

extern int g_sig;
extern int g_exit_code;
extern pid_t g_pid;

#endif
