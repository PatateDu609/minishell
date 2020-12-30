/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:17:05 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/30 06:28:23 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

#ifdef BONUS

int	g_fd;

void	ft_exit(void)
{
	write_commands();
	ft_putendl_fd("exit", 1);
	if (g_parsed)
		ft_lstclear(&g_parsed, ft_free_command);
	close(g_fd);
	exit(0);
}

void	minishell(t_env *env, t_caps *caps)
{
	char			*command;
	struct termios	backup;

	(void)env;

	while (1)
	{
		if (!init_termios(&backup))
			return ;
		command = ft_getline(caps, PROMPT);
		if (!reset_terminal(&backup, caps))
			return ;
		add_command(command);
		printf("\n");
		g_parsed = ft_ternary(*command != 0, ft_parser(command), NULL);
		if (*command == 0)
		{
			free(command);
			// free_env(env);
			ft_exit();
		}
		free(command);
		ft_lstiter(g_parsed, ft_print_command);
		// ft_exec(env, g_parsed);
		ft_lstclear(&g_parsed, ft_free_command);
	}
}

int	main(int ac, char **av, char **ev)
{
	t_env		*env;
	t_caps		caps;

	g_fd = open("/dev/pts/1", O_RDWR);
	(void)ac;
	(void)av;
	(void)ev;
	ft_signalhandler_enable();
	// env = ft_env(ev);
	// if (!env)
	// 	return (1);
	env = NULL;
	if (!init_termcaps(env, &caps))
		return (1);
	write(g_fd, tgetstr("cl", NULL), ft_strlen(tgetstr("cl", NULL)));
	load_history();
	minishell(env, &caps);
	// free_env(env);
	close(g_fd);
	return (0);
}

#endif
