/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 01:21:59 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/01 04:53:19 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

void	ft_print_error_exec(char *pathname)
{
	char	*error;

	error = strerror(errno);
	write(2, program_invocation_short_name,
			ft_strlen(program_invocation_short_name));
	write(2, ": ", 2);
	write(2, pathname, ft_strlen(pathname));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

void	ft_print_error_builtins(char *builtin, char *arg)
{
	char	*error;

	error = strerror(errno);
	write(2, program_invocation_short_name,
			ft_strlen(program_invocation_short_name));
	write(2, ": ", 2);
	write(2, builtin, ft_strlen(builtin));
	write(2, ": ", 2);
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

void	ft_print_error_env(char *builtin, char *var)
{
	write(2, program_invocation_short_name,
			ft_strlen(program_invocation_short_name));
	write(2, ": ", 2);
	write(2, builtin, ft_strlen(builtin));
	write(2, ": `", 2);
	write(2, var, ft_strlen(var));
	write(2, "': not a valid identifier\n", 26);
}
