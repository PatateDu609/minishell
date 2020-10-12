#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include "include/ft_defs.h"

// int main()
// {
// 	int fd[2], std_fd[2], status;
// 	pid_t pid, pid1;
// 	char str1[512];

// 	std_fd[0] = dup(STDIN_FILENO);
// 	std_fd[1] = dup(STDOUT_FILENO);

// 	if (pipe(fd))
// 	{
// 		perror("pipe");
// 		return (EXIT_FAILURE);
// 	}

// 	if ((pid = fork()))
// 	{
// 		waitpid(pid, &status, 0);
// 		close(fd[1]);

// 		int file = open("Makefile.copy", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 		printf("File copy : %d\n", file);
// 		dup2(file, 1);
// 		dup2(fd[0], 0);


// 		if ((pid1 = fork()))
// 		{
// 			waitpid(pid1, &status, 0);
// 		}
// 		else
// 		{
// 			execlp("cat", "cat",  NULL);
// 			perror("exec");
// 		}
// 	}
// 	else
// 	{
// 		close(fd[0]);

// 		int file = open("Makefile", O_RDONLY);
// 		printf("File : %d\n", file);

// 		dup2(file, 0);
// 		dup2(fd[1], 1);
// 		execlp("cat", "cat", NULL);
// 		perror("exec");
// 	}

// 	dup2(std_fd[0], STDIN_FILENO);
// 	dup2(std_fd[1], STDOUT_FILENO);
// 	close(fd[0]);
// 	close(fd[1]);

// 	write(1, "Hello World!\n", 13);
// 	return (0);
// }

int			ft_check_sep(char *command, int type)
{
	char	types[5];
	int		i;
	int		mode;

	types[PARSER_TOKEN_CMD] = ' ';
	types[PARSER_TOKEN_ARGS] = ' ';
	types[PARSER_TOKEN_PIPE] = '|';
	types[PARSER_TOKEN_SEPARATOR] = ';';
	i = 0;
	if (command[strlen(command) - 1] == '\\')
		return (-1);
	while (command[i])
	{
		if (command[i] == '\\')
			i += 2;
		if (command[i] == '"' || command[i] == '\'')
		{
			mode = (command[i] == '"');
			i++;
			while (command[i] && ((mode && command[i] != '"') || (!mode && command[i] != '\'')))
				i++;
			if (!command[i])
				return (-2);
		}
		if ((type != PARSER_TOKEN_REDIRECT && command[i] == types[type]) ||
			(type == PARSER_TOKEN_REDIRECT && (command[i] == '<' || command[i] == '>')))
		{
			printf("command + i = %s\n", command + i);
			return (1);
		}
		i++;
	}
	return (type == PARSER_TOKEN_CMD);
}

int main(int ac, char **av)
{
	if (ac < 3)
		return (1);
	int type = atoi(av[2]);
	if (!(0 <= type && type <= 4))
		return (1);
	printf("Sentence : %s, type : %d\n", av[1], type);
	printf("result : %d\n", ft_check_sep(av[1], type));
}
