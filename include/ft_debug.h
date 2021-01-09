/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:27:22 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/09 00:32:56 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEBUG_H
# define FT_DEBUG_H

# include "minishell.h"

extern int	g_fd;
extern int	g_tree;

void		ft_print_redirs(t_redirect **redirs);
void		ft_print_command(void *cmdv);
void		ft_print_env(void);
void		ft_print_cmd(t_list *list);
void		ft_init_debug(void);

#endif
