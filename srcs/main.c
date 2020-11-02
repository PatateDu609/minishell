/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 17:15:04 by gboucett          #+#    #+#             */
/*   Updated: 2020/11/02 13:29:45 by gboucett         ###   ########.fr       */
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

t_btree *g_parsed = NULL;

// void	ctrl_c(int signal)
// {
// 	(void)signal;
// 	g_skip = 1;
// }

#ifndef BONUS
void	ctrl_d()
{
	ft_putendl_fd("exit", 1);
	if (g_parsed)
		free_parsed(g_parsed);
	exit(0);
}

#else
void	ctrl_d()
{
	write_commands();
	ft_putendl_fd("exit", 1);
	if (g_parsed)
		free_parsed(g_parsed);
	exit(0);
}
#endif

// void	ctrl_q(int signal)
// {
// 	(void)signal;
// }

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
	{
		free_env(env);
		ctrl_d();
	}
	free(tfree);
	g_exit_code = 0;
	return (1);
}

void exec_command(t_env *env, t_btree *cmd)
{
	size_t		len;
	t_command	*command;
	t_redirect	*redirects;
	char		*tmp;
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

	if ((g_pid = fork()) == 0)
	{
		execve(command->args[-1], command->args - 1, env->env);
		ft_printf("minishell: %s: %s\n", command->name, strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(g_pid, &status, 0);
		if (WIFEXITED(status))
		{
			g_exit_code = WEXITSTATUS(status);
		}
	}
	free(command->args[-1]);
	command->args[-1] = command->name;
	g_pid = 0;
}

#ifndef BONUS

void minishell(t_env *env)
{
	char		*command;
	int			ret;

	while(1)
	{
		ft_printf("\033[31m\033[1mminishell :>\033[0m\033[35m\033[0m ");
		ret = get_next_line(STDIN_FILENO, &command);
		g_parsed = (*command != 0) ? ft_parser(env, command) : NULL;
		if (*command == 0)
		{
			if (!ret)
			{
				free_env(env);
				free(command);
				ctrl_d();
			}
			else
				continue ;
		}
		free(command);
		print_separator(g_parsed);
		exec_command(env, g_parsed);
		free_parsed(g_parsed);
	}
}

int		main(int ac, char **av, char **ev)
{
	t_env		*env;

	(void)ac;
	(void)av;
	ft_signalhandler_enable();
	if (!(env = ft_env(ev)))
		return (1);
	minishell(env);
}

#else
int g_fd;
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
			ctrl_d();
		}
		free(command);
		print_separator(g_parsed);
		exec_command(env, g_parsed);
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
	write(g_fd, tgetstr("cl", NULL), ft_strlen("`clear`"));
	load_history();
	minishell(env, &caps);
	free_env(env);
	close(g_fd);
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
// 		g_pid = fork();

// 		if (!g_pid)
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
// 			printf("waitpid : %d\n", waitpid(g_pid, &status, 0));
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
// 	if ((g_pid = fork()) == -1)
// 	{
// 		perror("fork");
// 		return (3);
// 	}

// 	if (g_pid != 0)
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
