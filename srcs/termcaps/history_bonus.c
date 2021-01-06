/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 22:50:58 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 19:53:50 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

char	*g_history[HISTORY_SIZE];
int		g_last;

static void	read_history(int fd, char **current)
{
	int	res;

	res = get_next_line(fd, current);
	while (res > 0)
	{
		current++;
		g_last++;
		if (g_last + 1 == HISTORY_SIZE)
			break ;
		res = get_next_line(fd, current);
		if (res == 0)
			free(*current);
	}
}

void		load_history(void)
{
	char	**current;
	int		fd;

	ft_bzero(g_history, HISTORY_SIZE + 1);
	fd = open(HISTORY_FILE, O_RDONLY);
	g_last = -1;
	if (fd == -1)
		return ;
	current = g_history;
	g_last = -1;
	read_history(fd, current);
	if (!ft_strlen(*current))
	{
		free(*current);
		*current = 0;
	}
	close(fd);
}

void		add_command(char *command)
{
	if (!(command && ft_strlen(command)))
		return ;
	if (g_last >= HISTORY_SIZE - 1)
	{
		free(g_history[0]);
		ft_memmove(g_history, g_history + 1, (HISTORY_SIZE - 1)
			* sizeof(char *));
		g_history[g_last] = ft_strdup(command);
		g_last = HISTORY_SIZE - 1;
	}
	else
		g_history[++g_last] = ft_strdup(command);
}

void		write_commands(void)
{
	int		fd;
	int		i;

	fd = open(HISTORY_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	i = 0;
	while (i <= g_last)
	{
		write(fd, g_history[i], ft_strlen(g_history[i]));
		write(fd, "\n", 1);
		free(g_history[i]);
		i++;
	}
	close(fd);
}
