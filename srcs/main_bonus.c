/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:17:05 by gboucett          #+#    #+#             */
/*   Updated: 2020/11/22 04:02:15 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "debug.h"

#ifdef BONUS

int g_fd;

void	ft_exit()
{
	write_commands();
	ft_putendl_fd("exit", 1);
	if (g_parsed)
		free_parsed(g_parsed);
	close(g_fd);
	exit(0);
}

void minishell(t_env *env, t_caps *caps)
{
	char		*command;
	t_termios	backup;

	while(1)
	{
		if (!init_termios(&backup))
			return ;
		command = ft_getline(caps, "\033[31m\033[1mminishell :>\033[0m\033[35m\033[0m ");
		if (!reset_terminal(&backup, caps))
			return ;
		add_command(command);
		printf("\n");
		g_parsed = *command != 0 ? ft_parser(env, command) : NULL;
		if (*command == 0)
		{
			free(command);
			free_env(env);
			ft_exit();
		}
		free(command);
		print_separator(g_parsed);
		ft_exec(env, g_parsed);
		free_parsed(g_parsed);
	}
}

int main(int ac, char **av, char **ev)
{
	t_env		*env;
	t_caps		caps;
	g_fd = open("/dev/pts/1", O_RDWR);

	(void)ac;
	(void)av;
	ft_signalhandler_enable();
	if (!(env = ft_env(ev)))
		return (1);
	if (!init_termcaps(env, &caps))
		return (1);
	write(g_fd, tgetstr("cl", NULL), ft_strlen(tgetstr("cl", NULL)));
	load_history();
	minishell(env, &caps);
	free_env(env);
	close(g_fd);
	return (0);
}

#endif
