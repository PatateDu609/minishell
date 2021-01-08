/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 17:15:04 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/08 19:06:11 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS
# include "minishell.h"
#else
# include "minishell_bonus.h"
#endif

#include "ft_debug.h"

t_list	*g_parsed = NULL;
t_env	*g_env;

#ifndef BONUS

void		ft_apply_exit(void)
{
	if (g_parsed)
		ft_lstclear(&g_parsed, ft_free_command);
	ft_free_env();
	ft_signalhandler_disable();
	exit(g_exit_code);
}

void		process_parsed(void)
{
	if (g_parsed)
	{
		ft_exec(g_parsed);
		ft_print_cmd(g_parsed);
		ft_lstclear(&g_parsed, ft_free_command);
	}
}

static char	*get_command(int *ret)
{
	char	*command;

	*ret = 0;
	while (!*ret)
	{
		*ret = get_next_line(STDIN_FILENO, &command);
		if (ft_strlen(command) == 0)
			return (command);
		if (!*ret && *command)
			free(command);
	}
	if (!*ret)
	{
		free(command);
		return (NULL);
	}
	return (command);
}

void		minishell(void)
{
	char	*command;
	int		ret;

	while (1)
	{
		ft_printf("%s", PROMPT);
		command = get_command(&ret);
		if (!ret)
		{
			free(command);
			ft_putendl_fd("exit", 1);
			ft_apply_exit();
		}
		g_parsed = ft_ternary(command && *command != 0, ft_parser(command), NULL);
		free(command);
		process_parsed();
	}
}

int			main(int ac, char **av)
{
	t_env		*g_env;

	(void)ac;
	(void)av;
	ft_init_debug();
	ft_signalhandler_enable();
	g_env = ft_init_env(environ);
	if (!g_env)
		return (1);
	minishell();
	ft_free_env();
	return (0);
}

#endif
