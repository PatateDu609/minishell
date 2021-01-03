/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 07:08:39 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/03 20:52:41 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H

# include "ft_defs.h"

void	ft_print_env(void);

t_env	*ft_init_env(char **ev);
char	**ft_find_str(char **strs, char *str);
char	*ft_getvar(char *name);
void	*ft_free_env(void);

int		ft_modify_var(char *name, char *value);
int		ft_add_var(char *var);
int		ft_delete_var(char *name);

void	ft_merge_env(char **names);
char	**ft_sort_env(void);

char	*ft_str_replace_var(char *str);

#endif
