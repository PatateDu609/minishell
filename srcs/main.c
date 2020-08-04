/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 17:15:04 by gboucett          #+#    #+#             */
/*   Updated: 2020/08/03 21:16:22 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS
# include "minishell.h"
#else
# include "minishell_bonus.h"
#endif

#include "debug.h"

int		g_skip = 0;

void	ctrl_c(int signal)
{
	(void)signal;
	g_skip = 1;
}

void	ctrl_d()
{
	ft_putendl_fd("exit", 1);
	exit(0);
}

void	ctrl_q(int signal)
{
	(void)signal;
}

void minishell()
{
	char		*command;
	t_btree		*parsed;

	while(1)
	{
		ft_printf("\033[31m\033[1mminishell :>\033[0m\033[35m ");
		if (g_skip)
			continue ;
		get_next_line(STDIN_FILENO, &command);
		if (*command == 0)
			ctrl_d();
		parsed = ft_parser(command);
		print_separator(parsed);
		free_parsed(parsed);
		free(command);
	}
}

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	// if (signal(SIGINT, ctrl_c) == SIG_ERR)
	// {
	// 	ft_printf("Invalid signal.");
	// 	return (-1);
	// }
	// if (signal(SIGQUIT, ctrl_q) == SIG_ERR)
	// {
	// 	ft_printf("Invalid signal.");
	// 	return (-1);
	// }
	minishell();
}

// int main(int ac, char **av, char **ev)
// {
// 	(void)ac;
// 	(void)av;
// 	t_env *env = ft_env(ev);

// 	char *res = getcwd(NULL, 0);
// 	printf("result = %s\n", res);
// 	free(res);
// 	char *pwd = getpwd(env->env);
// 	printf("PWD = %s\n", pwd);
// 	free(pwd);
// 	chdir("../..");

// 	res = getcwd(NULL, 0);
// 	printf("result = %s\n", res);
// 	ft_add_var(env, "PWD", res);
// 	free(res);
// 	pwd = getpwd(env->env);
// 	printf("PWD = %s\n", pwd);
// 	free(pwd);
// 	free_env(env);
// }

// int		main(int ac, char **av, char **ev)
// {
// 	(void)av;
// 	(void)ac;
// 	t_env *env = ft_env(ev);
// 	char *command = "clear";

// 	char *cmd = ft_construct_cmd(env, command);
// 	char	*argv[3];
// 	argv[0] = cmd;
// 	argv[1] = NULL;
// 	argv[2] = NULL;
// 	if (cmd)
// 	{
// 		pid_t	pid = fork();

// 		if (!pid)
// 		{
// 			if (execve(cmd, argv, env->env))
// 			{
// 				free(cmd);
// 				fprintf(stderr, "zsh: %s: %s\n", strerror(errno), command);
// 				return (0);
// 			}
// 		}
// 		else
// 		{
// 			int status;
// 			printf("waitpid : %d\n", waitpid(pid, &status, 0));
// 			printf("status : %d\n", WEXITSTATUS(status));
// 		}
// 	}
// 	else if (!errno)
// 		printf("minishell: command not found: %s\n", command);
// 	else
// 	{
// 		char *error = ft_strjoin("minishell: ", command);
// 		perror(error);
// 		free(error);
// 	}
// 	free(cmd);
// 	free_env(env);
// 	return (0);
// }

// int main(int ac, char **av, char **env)
// {
// 	pid_t	pid;
// 	int		status;
// 	char	*file;
// 	int		fd;

// 	if (ac == 1)
// 	{
// 		printf("Arguments...\n");
// 		return (1);
// 	}
// 	file = av[ac - 1];
// 	av[ac - 1] = NULL;
// 	if ((pid = fork()) == -1)
// 	{
// 		perror("fork");
// 		return (3);
// 	}

// 	if (pid != 0)
// 	{
// 		wait(&status);
// 	}
// 	else
// 	{
// 		fd = open(file, O_RDONLY);
// 		dup2(fd, 0);
// 		if (execve(av[1], av + 1, env) == -1)
// 		{
// 			perror("execve");
// 			return (4);
// 		}
// 	}
// 	return (0);
// }
