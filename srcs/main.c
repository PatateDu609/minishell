/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 17:15:04 by gboucett          #+#    #+#             */
/*   Updated: 2020/10/21 00:33:07 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef BONUS
// #define BONUS
// #endif

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
	write_commands();
	ft_putendl_fd("exit", 1);
	exit(0);
}

void	ctrl_q(int signal)
{
	(void)signal;
}

int is_builtin(char *name)
{
	if (!ft_strcmp(name, "echo"))
		return (BUILTIN_ECHO);
	else if (!ft_strcmp(name, "cd"))
		return (BUILTIN_CD);
	else if (!ft_strcmp(name, "pwd"))
		return (BUILTIN_PWD);
	else if (!ft_strcmp(name, "env"))
		return (BUILTIN_ENV);
	else if (!ft_strcmp(name, "export"))
		return (BUILTIN_EXPORT);
	else if (!ft_strcmp(name, "unset"))
		return (BUILTIN_UNSET);
	else if (!ft_strcmp(name, "exit"))
		return (BUILTIN_EXIT);
	else
		return (BUILTIN_DEFAULT);
}

void ft_print_env(char **env)
{
	while (*env)
		ft_printf("%s\n", *env++);
}

void ft_cd(t_env *env, char **args)
{
	char *path;

	if (!args[0] || args[1])
	{
		ft_printf("cd: wrong number of arguments\n");
		return ;
	}
	if (chdir(args[0]))
		ft_printf("cd: %s: %s\n", strerror(errno), args[0]);
	printf("args[0] = %s\n", args[0]);
	path = getcwd(NULL, 0);
	ft_add_var(env, "PWD", path);
	free(path);
}

void ft_export(t_env *env, char **args)
{
	char	**tmp;
	char	*val;

	while (*args)
	{
		if (**args == '=')
		{
			ft_printf("export: bad assignment\n");
			args++;
			continue ;
		}
		tmp = ft_split(*args, '=');
		val = tmp[1] ? ft_strjoin_arr(tmp + 1, '=') : ft_strdup("");
		ft_add_var(env, tmp[0], val);
		free(val);
		free_splitted(tmp);
		args++;
	}
}

void ft_unset(t_env *env, char **args)
{
	while (*args)
		ft_delete_var(env, *args++);
}

void ft_echo(char **args, t_redirect *redirects)
{
	char	*end;
	char	**suitable;
	char	**saved;

	(void)redirects;

	if (*args)
		suitable = args;
	else
	{
		if (!(suitable = ft_calloc(2, sizeof(char *))))
			return ;
		saved = suitable;
		suitable[0] = "";
	}
	end = ft_strcmp(suitable[0], "-n") == 0 ? "" : "\n";
	if (*end == 0)
		suitable++;
	while (*suitable)
	{
		ft_printf("%s%s", *suitable, (*(suitable + 1) ? " " : end));
		suitable++;
	}
	if (!*args)
		free(saved);
}

int exec_builtin(t_env *env, t_command *cmd, t_redirect *redirects)
{
	int		id;
	void	*tfree;

	tfree = NULL;
	if ((id = is_builtin(cmd->name)) == BUILTIN_DEFAULT)
		return (0);
	else if (id == BUILTIN_ENV)
		ft_print_env(env->env);
	else if (id == BUILTIN_EXPORT)
		ft_export(env, cmd->args);
	else if (id == BUILTIN_UNSET)
		ft_unset(env, cmd->args);
	else if (id == BUILTIN_ECHO)
		ft_echo(cmd->args, redirects);
	else if (id == BUILTIN_PWD)
		ft_printf("%s\n", (tfree = getcwd(NULL, 0)));
	else if (id == BUILTIN_CD)
		ft_cd(env, cmd->args);
	else if (id == BUILTIN_EXIT)
		ctrl_d();
	free(tfree);
	return (1);
}

void exec_command(t_env *env, t_btree *cmd)
{
	size_t		len;
	t_command	*command;
	t_redirect	*redirects;
	char		*tmp;
	pid_t		pid;
	int			status;

	len = ft_strlen(cmd->item);
	if (len != ft_strlen(COMMAND_STR) || ft_strncmp(cmd->item, COMMAND_STR, len))
		return ;
	command = cmd->left->item;
	redirects = cmd->right ? cmd->right->item : NULL;
	if (exec_builtin(env, command, redirects))
		return ;
	if ((tmp = ft_construct_cmd(env, command->name)))
		command->args[-1] = tmp;
	else
	{
		ft_printf("%s: %s\n", command->name, (errno == 656 ? "command not found" : strerror(errno)));
		return ;
	}

	if ((pid = fork()) == 0)
	{
		execve(command->args[-1], command->args - 1, env->env);
		ft_printf("minishell: %s: %s\n", command->name, strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			env->vlast = WEXITSTATUS(status);
	}
	free(command->args[-1]);
	command->args[-1] = command->name;
}

#ifndef BONUS

void minishell(t_env *env)
{
	char		*command;
	t_btree		*parsed;
	int			ret;

	while(1)
	{
		ft_printf("\033[31m\033[1mminishell :>\033[0m\033[35m\033[0m ");
		if (g_skip)
			continue ;
		ret = get_next_line(STDIN_FILENO, &command);
		if (*command == 0)
		{
			free(command);
			if (!ret)
				ctrl_d();
			else
				continue ;
		}
		parsed = ft_parser(env, command);
		print_separator(parsed);
		exec_command(env, parsed);
		free_parsed(parsed);
		free(command);
	}
}

int		main(int ac, char **av, char **ev)
{
	t_env		*env;

	(void)ac;
	(void)av;
	if (!(env = ft_env(ev)))
		return (1);
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
	minishell(env);
}

#else

void minishell(t_env *env, t_caps *caps)
{
	char		*command;
	t_btree		*parsed;
	t_termios	backup;

	(void)parsed;
	(void)env;
	while(1)
	{
		if (g_skip)
			continue ;
		if (!init_termios(&backup))
			return ;
		command = ft_getline(caps, "\033[31m\033[1mminishell :>\033[0m\033[35m\033[0m ");
		if (!reset_terminal(&backup, caps))
			return ;
		add_command(command);
		printf("\n");
		if (*command == 0)
		{
			free(command);
			ctrl_d();
		}
		parsed = ft_parser(env, command);
		print_separator(parsed);
		exec_command(env, parsed);
		free_parsed(parsed);
		free(command);
	}
}

int main(int ac, char **av, char **ev)
{
	t_env		*env;
	t_caps		*caps;

	(void)ac;
	(void)av;
	if (!(env = ft_env(ev)))
		return (1);
	if (!(caps = (t_caps *)malloc(sizeof(t_caps))))
		return (1);
	if (!init_termcaps(env, caps))
		return (1);
	load_history();
	minishell(env, caps);
	free_env(env);
	free(caps);
	return (0);
}
#endif

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
