/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:17:05 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 19:39:27 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

#ifdef BONUS

t_env	*g_env;

void	ft_apply_exit(void)
{
	write_commands();
	ft_putendl_fd("exit", 1);
	if (g_parsed)
		ft_lstclear(&g_parsed, ft_free_command);
	ft_free_env();
	exit(g_exit_code);
}

void	minishell(t_caps *caps)
{
	char			*command;
	struct termios	backup;

	while (1)
	{
		if (!init_termios(&backup))
			return ;
		command = ft_getline(caps, PROMPT);
		if (!reset_terminal(&backup, caps))
			return ;
		add_command(command);
		g_parsed = ft_ternary(*command != 0, ft_parser(command), NULL);
		if (*command == 0)
		{
			free(command);
			ft_apply_exit();
		}
		free(command);
		ft_exec(g_parsed);
		ft_lstclear(&g_parsed, ft_free_command);
	}
}

int		main(int ac, char **av)
{
	t_caps		caps;

	(void)ac;
	(void)av;
	ft_signalhandler_enable();
	g_env = ft_init_env(environ);
	if (!g_env)
		return (1);
	if (!init_termcaps(&caps))
		return (1);
	load_history();
	minishell(&caps);
	return (0);
}

#endif
