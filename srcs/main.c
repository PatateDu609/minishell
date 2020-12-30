/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 17:15:04 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/30 09:31:55 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS
# include "minishell.h"
#else
# include "minishell_bonus.h"
#endif

t_list	*g_parsed = NULL;
int		g_tree;
int		g_fd;

#ifndef BONUS

void	ft_exit(void)
{
	ft_putendl_fd("exit", 1);
	if (g_parsed)
		ft_lstclear(&g_parsed, ft_free_command);
	close(g_fd);
	close(g_tree);
	exit(0);
}

void	process_parsed(t_env *env)
{
	(void)env;
	if (g_parsed)
	{
		printf("-------------------------------------\n");
		ft_lstiter(g_parsed, ft_print_command);
		printf("-------------------------------------\n");
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
				ft_free_env(env);
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

	g_fd = open("/dev/pts/2", O_RDWR);
	g_tree = open("/dev/pts/3", O_RDWR);

	write(g_fd, "\033c\033[3J", 6);
	write(g_tree, "\033c\033[3J", 6);

	ft_signalhandler_enable();
	env = ft_init_env(ev);
	if (!env)
		return (1);
	// minishell(env);
	ft_free_env(env);
	return (0);
}

#endif
