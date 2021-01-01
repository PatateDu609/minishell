/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 03:13:36 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/01 01:27:15 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXEC_H
# define FT_EXEC_H

# include "ft_defs.h"
# include "ft_env.h"

# define SIGCAUGHT 128

void	ft_print_error_exec(char *pathname);

void	ft_sigquit(int sigquit);
void	ft_sigint(int sigquit);
void	ft_signalhandler_enable(void);
void	ft_signalhandler_disable(void);

void	ft_open_pipe(t_list *list, int *pipe_open);
void	ft_close_pipe(t_list *list, int pipe_open);
void	ft_redirect_pipe(t_list *list);

char	*ft_construct_path(char *name);
void	ft_exec(t_list *commands);

#endif
