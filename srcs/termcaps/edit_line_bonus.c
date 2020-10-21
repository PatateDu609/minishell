/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:03:02 by gboucett          #+#    #+#             */
/*   Updated: 2020/10/21 01:47:45 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int max_int(int a, int b)
{
	return (a > b ? a : b);
}

void	ft_move_line(t_caps *caps, t_line *line, char *command)
{
	static int	current = -1;

	if (line->reset)
	{
		current = -1;
		return ;
	}
	command += 2;
	if (command[0] == 'D' && line->cursor > 0)
	{
		tputs(caps->le, 1, ms_putchar);
		line->cursor--;
	}
	if (command[0] == 'C' && line->cursor < ft_strlen(line->buffer))
	{
		tputs(caps->nd, 1, ms_putchar);
		line->cursor++;
	}
	if (command[0] == 'A' || command[0] == 'B')
	{
		if (command[0] == 'A')
			current = (current == -1) ? g_last : max_int(current - 1, 0);
		else if (command[0] == 'B' && current != -1)
			current++;
		if (current > g_last)
			current = -1;
		if (current == -1 && line->old_buffer)
		{
			line->buffer = line->old_buffer;
			line->old_buffer = NULL;
		}
		else if (current != -1)
		{
			if (!line->old_buffer) line->old_buffer = line->buffer;
			line->buffer = ft_strdup(g_history[current]);
		}
		line->cursor = ft_strlen(line->buffer);
		tputs(caps->dl, 1, ms_putchar);
		write(1, line->prompt, ft_strlen(line->prompt));
		write(1, line->buffer, ft_strlen(line->buffer));
	}
}

char	*ft_add_char(char *str, int i, char *c)
{
	char	*substr;
	char	*substr1;
	char	*tmp;

	substr = ft_substr(str, 0, i);
	substr1 = ft_substr(str, i, ft_strlen(str));
	tmp = ft_strjoin(substr, c);
	free(substr);
	substr = ft_strjoin(tmp, substr1);
	free(tmp);
	free(substr1);
	return (substr);
}

char	*ft_delete_char(char *str, int i)
{
	char	*substr;
	char	*tmp;

	substr = ft_substr(str, 0, i - 1);
	tmp = ft_substr(str, i, ft_strlen(str));
	str = ft_strjoin(substr, tmp);
	free(tmp);
	free(substr);
	return (str);
}
