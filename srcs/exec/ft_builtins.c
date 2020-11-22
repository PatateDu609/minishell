/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 03:51:21 by gboucett          #+#    #+#             */
/*   Updated: 2020/11/22 03:52:13 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

void ft_unset(t_env *env, char **args)
{
	while (*args)
		ft_delete_var(env, *args++);
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

void	ft_cd(t_env *env, char **args)
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

void	ft_print_env(char **env)
{
	while (*env)
		ft_printf("%s\n", *env++);
}
