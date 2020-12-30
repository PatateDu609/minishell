/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 17:15:04 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/30 06:23:31 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS
# include "minishell.h"
#else
# include "minishell_bonus.h"
#endif

t_list	*g_parsed = NULL;
int g_tree;

#ifndef BONUS

void	ft_exit(void)
{
	ft_putendl_fd("exit", 1);
	if (g_parsed)
		ft_lstclear(&g_parsed, ft_free_command);
	exit(0);
}

void	process_parsed(t_env *env)
{
	(void)env;
	if (g_parsed)
	{
		ft_lstiter(g_parsed, ft_print_command);
		// ft_exec(env, g_parsed);
		ft_lstclear(&g_parsed, ft_free_command);
	}
}

void	minishell(t_env *env)
{
	char		*command;
	int			ret;

	(void)env;
	while (1)
	{
		ft_printf("%s", PROMPT);
		ret = get_next_line(STDIN_FILENO, &command);
		g_parsed = ft_ternary(*command != 0, ft_parser(command), NULL);
		if (*command == 0)
		{
			if (!ret)
			{
				// free_env(env);
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
	(void)ev;
	ft_signalhandler_enable();
	// env = ft_env(ev);
	// if (!env)
	// 	return (1);
	env = NULL;
	minishell(env);
}

#endif
