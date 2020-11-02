/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 13:34:18 by rbourgea          #+#    #+#             */
/*   Updated: 2020/11/02 11:14:09 by gboucett         ###   ########.fr       */
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

#endif
