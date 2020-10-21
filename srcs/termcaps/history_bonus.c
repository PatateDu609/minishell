/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 22:50:58 by gboucett          #+#    #+#             */
/*   Updated: 2020/10/21 02:00:25 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

char	*g_history[HISTORY_SIZE + 1];
int		g_last;

void load_history(void)
{
	char	**current;
	int		fd;
	int		res;

	ft_bzero(g_history, HISTORY_SIZE + 1);
	fd = open(HISTORY_FILE, O_RDONLY);
	g_last = -1;
	if (fd == -1)
		return ;
	current = g_history;
	g_last = 0;
	while ((res = get_next_line(fd, current)) > 0)
	{
		if (ft_strlen(*current))
		{
			printf("|%s| -> %ld\n", *current, ft_strlen(*current));
			current++;
			g_last++;
		}
		else
		{
			free(*current);
			*current = NULL;
		}
	}
	free(g_history[g_last]);
	g_history[g_last] = 0;
	g_last--;
	close(fd);
}

void	add_command(char *command)
{
	if (g_last == HISTORY_SIZE)
	{
		// free(g_history[0]);
		ft_memmove_sp(g_history, g_history + 1, HISTORY_SIZE - 1);
		g_history[++g_last] = ft_strdup(command);
		g_last = HISTORY_SIZE;
	}
	else
		g_history[++g_last] = ft_strdup(command);
}

void	write_commands(void)
{
	int		fd;
	int		i;

	fd = open(HISTORY_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	i = 0;
	while (g_history[i])
	{
		if (ft_strlen(g_history[i]))
		{
			write(fd, g_history[i], ft_strlen(g_history[i]));
			write(fd, "\n", 1);
		}
		i++;
	}
	i = 0;
	while (g_history[i])
		free(g_history[i++]);
}
