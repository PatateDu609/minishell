/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 17:15:04 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/26 15:32:59 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS
# include "minishell.h"
#else
# include "minishell_bonus.h"
#endif

#include "debug.h"

t_btree	*g_parsed = NULL;

#ifndef BONUS

void	ft_exit(void)
{
	ft_putendl_fd("exit", 1);
	if (g_parsed)
		free_parsed(g_parsed);
	exit(0);
}

void	process_parsed(t_env *env)
{
	if (g_parsed)
	{
		print_separator(g_parsed);
		ft_exec(env, g_parsed);
		free_parsed(g_parsed);
	}
}

void	minishell(t_env *env)
{
	char		*command;
	int			ret;

	while (1)
	{
		ft_printf("%s", PROMPT);
		ret = get_next_line(STDIN_FILENO, &command);
		g_parsed = ft_ternary(*command != 0, ft_parser(env, command), NULL);
		if (*command == 0)
		{
			if (!ret)
			{
				free_env(env);
				free(command);
				ft_exit();
			}
			continue ;
		}
		free(command);
		process_parsed(env);
	}
}

int	main(int ac, char **av, char **ev)
{
	t_env		*env;

	(void)ac;
	(void)av;
	ft_signalhandler_enable();
	env = ft_env(ev);
	if (!env)
		return (1);
	minishell(env);
}

#endif
