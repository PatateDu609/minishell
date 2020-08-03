/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 11:37:41 by gboucett          #+#    #+#             */
/*   Updated: 2020/07/28 14:17:46 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXEC_H
# define FT_EXEC_H

# include "minishell.h"

t_env		*ft_env(char **env);
size_t		ft_sizeof(char **env);
void		init_paths(t_env *env);
void		ft_delete_var(t_env *env, char *name);
void		ft_add_var(t_env *env, char *name, char *value);
void		free_env(t_env *env);
char		*getvar(char **ev, char *var);
char		*ft_construct_cmd(t_env *env, char *command);

#endif
