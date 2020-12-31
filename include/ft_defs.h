/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_defs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:31:37 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/31 14:15:17 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEFS_H
# define FT_DEFS_H

# define _GNU_SOURCE
// #include <features.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <libgen.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "libft.h"

# define COMMAND_STR				"COMMAND"
# define REDIRECTION_STR			"REDIRECT"
# define ARGUMENT_STR				"ARGUMENT"
# define PIPELINE_STR				"PIPELINE"
# define SEPARATOR_STR				"SEPARATOR"

# define PARSER_TOKEN_CMD			0
# define PARSER_TOKEN_ARGS			1
# define PARSER_TOKEN_REDIRECT		2
# define PARSER_TOKEN_PIPE			3

# ifndef BONUS
#  define PARSER_TOKEN_SEPARATOR	4
# else
// #  define PARSER_TOKEN_OPERATOR		4
#  define PARSER_TOKEN_SEPARATOR	4
# endif

# define REDIRECT_TYPE_IN			0 //<
# define REDIRECT_TYPE_OUT			1 //>>
# define REDIRECT_TYPE_OUT_FLUSH	2 //>
# ifdef BONUS
#  define REDIRECT_TYPE_HERE_DOC	3 //<<
# endif

# define BUILTIN_DEFAULT	-1
# define BUILTIN_ECHO		0
# define BUILTIN_CD			1
# define BUILTIN_PWD		2
# define BUILTIN_ENV		3
# define BUILTIN_EXPORT		4
# define BUILTIN_UNSET		5
# define BUILTIN_EXIT		6

# define HISTORY_SIZE		1000
# define HISTORY_FILE		".minishell_history"

# define PROMPT				"\033[31m\033[1mminishell :>\033[0m\033[35m\033[0m "

typedef enum e_type
{
	COMMAND,
	PIPE,
	BREAK
}	t_type;

typedef struct s_redirect
{
	int		type;
	char	*filename;
}	t_redirect;

typedef struct s_command
{
	char				**args;
	t_type				type;
	t_redirect			**redirects;
	int					pipe[2];
}	t_command;

typedef struct s_env
{
	char	**names;
	char	**values;
	char	**paths;
	char	**merged;
}	t_env;

extern int		g_fd;
extern int		g_tree;
extern t_env	*g_env;
extern int		g_exit_code;
extern pid_t	g_pid;

#endif
