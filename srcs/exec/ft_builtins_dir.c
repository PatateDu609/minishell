/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 03:35:08 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/01 05:15:42 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

void	ft_cd(t_command *command)
{
	char	*cwd;

	if (!command->args[1])
		return ;
	if (chdir(command->args[1]))
		ft_print_error_builtins("cd", command->args[1]);
	cwd = getcwd(NULL, 0);
	ft_modify_var(ft_strdup("PWD"), cwd);
}

void	ft_pwd(t_command *command)
{
	(void)command;
	ft_printf("%s\n", ft_getvar("PWD"));
}
