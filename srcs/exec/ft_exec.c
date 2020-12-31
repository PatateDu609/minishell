/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:11:31 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/31 01:18:10 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

void	ft_exec(t_env *g_env, t_btree *cmd)
{
	size_t		len;
	t_command	*command;
	t_redirect	*redirects;
	char		*tmp;
	int			status;

	len = ft_strlen(cmd->item);
	if (len != ft_strlen(COMMAND_STR) || ft_strncmp(cmd->item, COMMAND_STR, len))
		return ;
	command = cmd->left->item;
	redirects = ft_ternary(cmd->right, cmd->right->item, NULL);
	if (exec_builtin(g_env, command, redirects))
		return ;
	if (ft_assign(&tmp, ft_construct_cmd(g_env, command->name)))
		command->args[-1] = tmp;
	else
	{
		ft_printf("%s: %s\n", command->name, (
			ft_ternary(errno == 656, "command not found", strerror(errno))));
		return ;
	}
	g_pid = fork();
	if (g_pid == 0)
	{
		execve(command->args[-1], command->args - 1, g_env->env);
		ft_printf("minishell: %s: %s\n", command->name, strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(g_pid, &status, 0);
		if (WIFEXITED(status))
		{
			g_exit_code = WEXITSTATUS(status);
		}
	}
	free(command->args[-1]);
	command->args[-1] = command->name;
	g_pid = 0;
}
