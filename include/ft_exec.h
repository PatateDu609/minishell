/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 03:13:36 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 05:10:42 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXEC_H
# define FT_EXEC_H

# include "ft_defs.h"
# include "ft_env.h"

# define SIGCAUGHT 128

void	ft_print_error_builtins(char *builtin, char *arg, int err);
void	ft_print_error_exec(char *pathname);
void	ft_print_error_env(char *builtin, char *var);

void	ft_sigquit(int sigquit);
void	ft_sigint(int sigquit);
void	ft_signalhandler_enable(void);
void	ft_signalhandler_disable(void);

void	ft_apply_redir_in(t_command *command, int fdout);
void	ft_apply_redir_out(t_command *command, char *output);
int		ft_open(t_redirect *redir);
void	ft_redirect_in(t_command *command);
void	ft_redirect_out(t_command *command);

char	*ft_load_file(t_redirect *redir);
char	*ft_load_pipe(int fdin);
int		ft_check_file(t_redirect *redir);

void	ft_open_pipe(t_list *list);
void	ft_close_pipe(t_list *list);
void	ft_redirect_pipe(t_list *list);
size_t	ft_size_pipeline(t_list *list);
int		ft_is_pipe(t_list *list);

int		ft_get_builtin_id(char *name);
size_t	ft_get_echo_start(char **args);
int		ft_check_shell_name(char *name);

void	ft_init_builtin(t_list *lst);
void	ft_execute_builtin(t_list *lst, t_builtin_func builtin);

void	ft_apply_exit(void);

void	ft_echo(t_command *command);
void	ft_cd(t_command *command);
void	ft_pwd(t_command *command);
void	ft_export(t_command *command);
void	ft_unset(t_command *command);
void	ft_env(t_command *command);
void	ft_exit(t_command *command);

char	*ft_construct_path(char *name);

int		ft_check_command(t_command *command, t_list **commands);

int		ft_init_redir(t_command *command);
void	ft_exec(t_list *commands);

#endif
