/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:29:53 by gboucett          #+#    #+#             */
/*   Updated: 2020/11/06 01:04:10 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

# include "ft_defs.h"

char		*ft_get_sep(char *command, int type);
int			ft_check_sep(char *command, int type);
char		*ft_subcmd(char *command, char *major, int side);
char		*ft_get_major(char *command, char **sep);
t_btree		*ft_parser(t_env *env, char *command);
char		*ft_parse_env(t_env *env, char *command);
t_btree		*ft_parse_pipeline(char *command);
char		**ft_split_args(char *command);
t_btree		*ft_parse_command(char *command);
void		free_splitted(char **splitted);
void		free_parsed(t_btree *parsed);
int			ft_valid_sep(char *command);

#endif
