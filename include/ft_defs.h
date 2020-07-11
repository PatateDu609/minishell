/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_defs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:31:37 by gboucett          #+#    #+#             */
/*   Updated: 2020/07/11 23:00:11 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEFS_H
# define FT_DEFS_H

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

# define PARSER_TOKEN_CMD			0
# define PARSER_TOKEN_ARGS			1
# define PARSER_TOKEN_REDIRECT		2
# define PARSER_TOKEN_PIPE			3
# define PARSER_TOKEN_SEPARATOR		4

typedef struct		s_command
{
	t_list			*args;
	t_list			*redirects;
}					t_command;

typedef union		u_token_content
{
	char			*string;
	t_command		*command;
}					t_token_content;

typedef struct		s_token
{
	int				type;
	t_token_content	*token;
}					t_token;

#endif
