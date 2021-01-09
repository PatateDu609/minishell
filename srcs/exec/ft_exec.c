/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 02:51:10 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/09 00:45:45 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"
#include "ft_expand.h"

static void		ft_execute_cmd(t_list *lst)
{
	int			status;
	t_command	*command;

	command = (t_command *)lst->content;
	g_pid = fork();
	if (g_pid == -1)
		ft_print_error_exec("fork");
	else if (g_pid)
	{
		waitpid(g_pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		ft_close_pipe(lst);
	}
	else
	{
		ft_redirect_in(command);
		ft_redirect_out(command);
		execve(command->name, command->args, g_env->merged);
		ft_print_error_exec(command->args[0]);
		exit(1);
	}
}

static void		ft_wait_all(pid_t *pids, size_t len)
{
	size_t	count;
	size_t	i;
	int		status;
	pid_t	ret;

	i = 0;
	while (i < len)
	{
		ret = waitpid(pids[i], &status, 0);
		if (ret != 0)
		{
			if (WIFEXITED(status))
				g_exit_code = WEXITSTATUS(status);
			count++;
		}
		i++;
	}
	free(pids);
}

static void		ft_lauch_piped(t_list **commands, pid_t *pids, int i)
{
	pids[i] = fork();
	if (pids[i] == 0)
	{
		if (ft_get_builtin_id(((t_command *)(*commands)->content)->name)
			== BUILTIN_DEFAULT)
			ft_execute_cmd(*commands);
		else
			ft_init_builtin(*commands);
		exit(g_exit_code);
	}
	else if (pids[i] == -1)
		ft_print_error_exec("fork");
}

static void		ft_exec_pipeline(t_list **commands)
{
	size_t		len;
	size_t		i;
	pid_t		*pids;
	int			fd[2];

	len = ft_size_pipeline(*commands);
	pids = ft_calloc(len, sizeof(pid_t));
	i = 0;
	fd[0] = dup(0);
	fd[1] = dup(1);
	while (*commands && ft_is_pipe(*commands))
	{
		ft_open_pipe(*commands);
		ft_redirect_pipe(*commands);
		ft_lauch_piped(commands, pids, i++);
		close(1);
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		*commands = (*commands)->next;
	}
	ft_wait_all(pids, len);
}

void			ft_exec(t_list *commands)
{
	t_command	*command;
	int			piped;

	while (commands)
	{
		command = (t_command *)commands->content;
		piped = 0;
		if (ft_check_command(command, &commands) && ft_init_redir(command))
		{
			ft_merge_env(NULL);
			if (ft_is_pipe(commands))
			{
				ft_exec_pipeline(&commands);
				piped = 1;
			}
			else if (ft_get_builtin_id(command->name) != BUILTIN_DEFAULT)
				ft_init_builtin(commands);
			else
				ft_execute_cmd(commands);
		}
		if (commands && !piped)
			commands = commands->next;
	}
	g_pid = 0;
}
