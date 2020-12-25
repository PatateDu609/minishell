/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 11:37:41 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/23 17:12:56 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXEC_H
# define FT_EXEC_H

# include "minishell.h"

t_env	*ft_env(char **env);
size_t	ft_sizeof(char **env);
void	init_paths(t_env *env);
void	ft_delete_var(t_env *env, char *name);
void	ft_add_var(t_env *env, char *name, char *value);
void	free_env(t_env *env);
char	*getvar(t_env *env, char *var);
char	*ft_construct_cmd(t_env *env, char *command);
void	ft_exec(t_env *env, t_btree *cmd);

int		exec_builtin(t_env *env, t_command *cmd, t_redirect *redirects);

void	ft_exit(void);
void	ft_cd(t_env *env, char **args);
void	ft_echo(char **args, t_redirect *redirects);
void	ft_print_env(char **env);
void	ft_export(t_env *env, char **args);
void	ft_unset(t_env *env, char **args);

#endif
