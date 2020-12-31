/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 13:34:18 by rbourgea          #+#    #+#             */
/*   Updated: 2020/12/31 13:07:47 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_defs.h"
# include "ft_parser.h"
# include "ft_env.h"
# include "ft_exec.h"

extern int		g_sig;
extern t_list	*g_parsed;

#endif
