/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:03:02 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 19:54:25 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"
#include <stdio.h>

int			max_int(int a, int b)
{
	return (ft_ternaryi(a > b, a, b));
}

static void	ft_loop_history(t_caps *caps, t_line *line, int mode, int *cur)
{
	if (mode == 0)
		*cur = ft_ternaryi(*cur == -1, g_last, max_int(*cur - 1, 0));
	else if (mode == 1 && *cur != -1)
		*cur += 1;
	if (*cur > g_last)
		*cur = -1;
	if (*cur == -1 && line->old_buffer)
	{
		free(line->buffer);
		line->buffer = line->old_buffer;
		line->old_buffer = NULL;
	}
	else if (*cur != -1)
	{
		if (!line->old_buffer)
			line->old_buffer = line->buffer;
		else if (line->buffer != line->old_buffer)
			free(line->buffer);
		line->buffer = ft_strdup(g_history[*cur]);
	}
	line->cursor = ft_strlen(line->buffer);
	tputs(caps->dl, 1, ms_putchar);
	write(1, line->prompt, ft_strlen(line->prompt));
	write(1, line->buffer, ft_strlen(line->buffer));
}

void		ft_move_line(t_caps *caps, t_line *line, char *command)
{
	static int	current = -1;
	int			mode;

	if (line->reset)
	{
		current = -1;
		return ;
	}
	mode = ft_parse_arrow(command);
	if (mode == 4 || mode == 5)
		ft_cursor_home_end(caps, line, mode == 4);
	if (mode == 6 || mode == 7)
		ft_cursor_move_word(caps, line, mode == 6);
	if (mode == 3 && line->cursor > 0)
	{
		tputs(caps->le, 1, ms_putchar);
		line->cursor--;
	}
	if (mode == 2 && line->cursor < ft_strlen(line->buffer))
	{
		tputs(caps->nd, 1, ms_putchar);
		line->cursor++;
	}
	if (mode == 0 || mode == 1)
		ft_loop_history(caps, line, mode, &current);
}

char		*ft_add_char(char *str, int i, char *c)
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

char		*ft_delete_char(char *str, int i)
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
