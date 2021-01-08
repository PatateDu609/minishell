/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 01:49:09 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/08 17:34:17 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPAND_H
# define FT_EXPAND_H

# include "ft_defs.h"
# include "ft_parser.h"
# include "ft_env.h"

void	ft_expand_backslashs(t_list **lst);
void	ft_expand_env(t_list **lst, char *str);
void	ft_quote_removal(t_list *lst);

void	ft_free_expansion(void *expv);

void	ft_connect(t_list **target, t_list *newlst);
char	*ft_strchr_quoted(char *str, char c, int *in_quotes);
int		ft_has_special_meaning(int quoted, char c);
void	ft_append_last(t_list **lst, char	*str);
t_list	*ft_create_expansion(char *str, int expanded);

char	*ft_expanded_str(t_list *lst);
void	ft_expand(t_command *command);

#endif
