/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:29:45 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/02 21:47:27 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

static int	ft_open(t_redirect *redir)
{
	int		fd;

	if (redir->type == 1)
		fd = open(redir->filename, O_RDONLY);
	else if (redir->type == 2)
		fd = open(redir->filename, O_WRONLY | O_APPEND | O_CREAT, 0664);
	else if (redir->type == 3)
		fd = open(redir->filename, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (fd == -1)
		ft_print_error_exec(redir->filename);
	return (fd);
}

static void	ft_load_file(t_command *command, t_redirect *redir, int fd)
{
	char	*result;
	char	*tmp;
	char	buffer[4096];
	int		ret;

	ret = 1;
	result = NULL;
	while (ret > 0)
	{
		ret = read(fd, buffer, 4095);
		if (ret == -1)
		{
			ft_print_error_exec(redir->filename);
			free(result);
			return ;
		}
		buffer[ret] = 0;
		tmp = result;
		result = ft_strjoin(result, buffer);
		free(tmp);
	}
	tmp = command->input;
	command->input = ft_strjoin(command->input, result);
	free(result);
	free(tmp);
}

int	ft_init_redir(t_command *command)
{
	t_redirect	**redirs;
	int			fd;
	int			initialized;

	redirs = command->redirects;
	if (!redirs)
		return (0);
	initialized = 0;
	while (*redirs)
	{
		if ((*redirs)->type == 1)
		{
			fd = ft_open(*redirs);
			ft_load_file(command, *redirs, fd);
			close(fd);
		}
		else if (!initialized || initialized == 1)
		{
			initialized |= 2;
			pipe(command->red_out);
		}
		redirs++;
	}
	return (1);
}
