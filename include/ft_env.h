/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 07:08:39 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/30 09:34:04 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H

# include "ft_defs.h"

void	ft_print_env(t_env *env);

t_env	*ft_init_env(char **ev);
char	**ft_find_str(char **strs, char *str);
char	*ft_getvar(t_env *env, char *name);
void	*ft_free_env(t_env *env);

int		ft_modify_var(t_env *env, char *name, char *value);
int		ft_add_var(t_env *env, char *var);
int		ft_delete_var(t_env *env, char *name);

#endif
