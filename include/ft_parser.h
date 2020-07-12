/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:29:53 by gboucett          #+#    #+#             */
/*   Updated: 2020/07/12 16:34:32 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

# include "ft_defs.h"

char		*ft_get_sep(char *command, int type);
char		*ft_subcmd(char *command, char *major, int side);
char		*ft_get_major(char *command, char **sep);
t_btree		*ft_parser(char *command);

#endif
