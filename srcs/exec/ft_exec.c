/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 02:51:10 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/01 05:25:24 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

void	ft_execute_cmd(t_list *lst, char *path)
{
	int			status;
	int			pipe_open;
	t_command	*command;

	command = (t_command *)lst->content;
	ft_open_pipe(lst, &pipe_open);
	g_pid = fork();
	if (g_pid == -1)
		ft_print_error_exec("fork");
	else if (g_pid)
	{
		waitpid(g_pid, &status, 0);
		ft_close_pipe(lst, pipe_open);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
	}
	else
	{
		ft_redirect_pipe(lst);
		execve(path, command->args, g_env->merged);
		printf("(printed with printf)minishell: execve marche po\n");
		exit(1);
	}
}

void	ft_init_cmd(t_list *commands, int *valid)
{
	t_command	*command;
	char		*path;

	command = (t_command *)commands->content;
	path = ft_construct_path(command->args[0]);
	if (path && *valid)
		ft_execute_cmd(commands, path);
	else if (!path)
	{
		*valid = 0;
		ft_print_error_exec(command->args[0]);
	}
	free(path);
}

void	ft_exec(t_list *commands)
{
	t_command	*command;
	int			valid;

	valid = 1;
	while (commands)
	{
		command = (t_command *)commands->content;
		ft_merge_env();
		if (ft_get_builtin_id(command->args[0]) != BUILTIN_DEFAULT)
			ft_init_builtin(commands);
		else
			ft_init_cmd(commands, &valid);
		commands = commands->next;
	}
	g_pid = 0;
}
