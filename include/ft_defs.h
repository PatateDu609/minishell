/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_defs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:31:37 by gboucett          #+#    #+#             */
/*   Updated: 2020/10/20 22:15:26 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEFS_H
# define FT_DEFS_H

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

typedef struct		s_command
{
	char			*name;
	char			**args;
}					t_command;

typedef struct		s_redirect
{
	char			*type;
	char			*target;
	int				fd;
}					t_redirect;

typedef struct		s_env
{
	char			**env;
	char			**paths;
	int				vlast;
}					t_env;

#endif
