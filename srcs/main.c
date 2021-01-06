/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 17:15:04 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 00:19:21 by gboucett         ###   ########.fr       */
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
t_env	*g_env;

#ifndef BONUS

void	ft_apply_exit(void)
{
	if (g_parsed)
		ft_lstclear(&g_parsed, ft_free_command);
	ft_free_env();
	close(g_fd);
	close(g_tree);
	ft_signalhandler_disable();
	exit(g_exit_code);
}

void	process_parsed(void)
{
	if (g_parsed)
	{
		dprintf(g_tree, "-------------------------------------\n");
		ft_lstiter(g_parsed, ft_print_command);
		dprintf(g_tree, "-------------------------------------\n");
		ft_exec(g_parsed);
		ft_lstclear(&g_parsed, ft_free_command);
	}
}

static char	*get_command(int *ret)
{
	char	*command;
	int		first;

	*ret = 0;
	first = 1;
	while (!*ret && first)
	{
		*ret = get_next_line(STDIN_FILENO, &command);
		if (!*ret && *command)
			free(command);
		first = 0;
	}
	return (command);
}

void	minishell(void)
{
	char	*command;
	int		ret;

	while (1)
	{
		ft_printf("%s", PROMPT);
		command = get_command(&ret);
		g_parsed = ft_ternary(*command != 0, ft_parser(command), NULL);
		if (!ret)
		{
			free(command);
			ft_putendl_fd("exit", 1);
			ft_apply_exit();
		}
		free(command);
		process_parsed();
	}
}

int	main(int ac, char **av)
{
	t_env		*g_env;

	(void)ac;
	(void)av;
	g_fd = open("/dev/pts/7", O_RDWR);
	g_tree = open("/dev/pts/8", O_RDWR);
	write(g_fd, "\033c\033[3J", 6);
	write(g_tree, "\033c\033[3J", 6);
	ft_signalhandler_enable();
	g_env = ft_init_env(environ);
	if (!g_env)
		return (1);
	minishell();
	ft_free_env();
	return (0);
}

#endif
