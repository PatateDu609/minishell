/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 23:51:13 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 18:57:16 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

void	ft_apply_redir_in(t_command *command, int fdout)
{
	t_redirect	**redirs;
	char		*input;

	if (command->in != 1)
		return ;
	redirs = command->redirects;
	while (*redirs)
	{
		if ((*redirs)->type == 1)
		{
			input = ft_load_file(*redirs);
			write(fdout, input, ft_strlen(input));
			free(input);
		}
		redirs++;
	}
}

void	ft_apply_redir_out(t_command *command, char *output)
{
	t_redirect	**redirs;
	int			fd;
	size_t		outlen;

	if (command->out != 1)
		return ;
	outlen = ft_strlen(output);
	redirs = command->redirects;
	while (*redirs)
	{
		if ((*redirs)->type == 1)
		{
			redirs++;
			continue ;
		}
		fd = ft_open(*redirs);
		write(fd, output, outlen);
		close(fd);
		redirs++;
	}
}
