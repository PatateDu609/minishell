/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 03:13:36 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/31 04:35:54 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXEC_H
# define FT_EXEC_H

#include "ft_defs.h"

# define SIGCAUGHT 128

void	ft_sigquit(int sigquit);
void	ft_sigint(int sigquit);
void	ft_signalhandler_enable(void);
void	ft_signalhandler_disable(void);

char	*ft_construct_path(char *name);

#endif
