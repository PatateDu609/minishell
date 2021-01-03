/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:29:45 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/03 00:37:18 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

int	ft_open(t_redirect *redir)
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

int	ft_check_file(t_redirect *redir)
{
	int		fd;

	fd = ft_open(redir);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

char	*ft_load_file(t_redirect *redir)
{
	char	*result;
	char	*tmp;
	char	buffer[4096];
	int		ret;
	int		fd;

	fd = ft_open(redir);
	if (fd == -1)
	{
		ft_print_error_exec(redir->filename);
		return (NULL);
	}
	ret = 1;
	result = NULL;
	while (ret > 0)
	{
		ret = read(fd, buffer, 4095);
		if (ret == -1)
		{
			ft_print_error_exec(redir->filename);
			free(result);
			return (NULL);
		}
		buffer[ret] = 0;
		tmp = result;
		result = ft_strjoin(result, buffer);
		free(tmp);
	}
	return (result);
}
