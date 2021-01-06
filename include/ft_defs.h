/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_defs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:31:37 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 19:27:47 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEFS_H
# define FT_DEFS_H

# define _GNU_SOURCE
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

typedef enum	e_type
{
	COMMAND,
	PIPE,
	BREAK
}				t_type;

typedef struct	s_redirect
{
	int			type;
	char		*filename;
}				t_redirect;

typedef struct	s_command
{
	char		*name;
	char		**args;
	t_type		type;
	t_redirect	**redirects;
	int			pipe[2];
	int			piped;
	int			in;
	int			out;
}				t_command;

typedef struct	s_env
{
	char		**names;
	char		**values;
	char		**paths;
	char		**merged;
}				t_env;

typedef struct	s_expansion
{
	char		*str;
	int			expanded;
}				t_expansion;

typedef void	(*t_builtin_func)(t_command *);

extern t_env	*g_env;
extern int		g_exit_code;
extern pid_t	g_pid;

#endif
