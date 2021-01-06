/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:07:50 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 19:53:27 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

static void	print_frame(t_caps *caps, t_line *line, char *command, char *prompt)
{
	if (line->cursor < ft_strlen(line->buffer))
		tputs(caps->sc, 1, ms_putchar);
	tputs(caps->dl, 1, ms_putchar);
	write(1, prompt, ft_strlen(prompt));
	write(1, line->buffer, ft_strlen(line->buffer));
	if (line->cursor < ft_strlen(line->buffer))
	{
		tputs(caps->rc, 1, ms_putchar);
		if (command[0] != 0x7f)
			tputs(caps->nd, 1, ms_putchar);
	}
}

static int	ft_edit_line(t_caps *caps, t_line *line, char *command)
{
	char	*tmp;

	if (command[0] == 0x7f)
	{
		tmp = line->buffer;
		line->buffer = ft_delete_char(line->buffer, line->cursor);
		line->cursor--;
		tputs(caps->le, 1, ms_putchar);
		free(tmp);
	}
	else if (command[0] == '\n' || (command[0] == 4 && !line->cursor))
	{
		if (command[0] == '\n')
			write(1, "\n", 1);
		return (0);
	}
	else
	{
		tmp = line->buffer;
		line->buffer = ft_add_char(line->buffer, line->cursor, command);
		line->cursor++;
		free(tmp);
	}
	return (1);
}

static void	init_getline(t_line *line, char *prompt)
{
	line->cursor = 0;
	line->buffer = ft_strdup("");
	line->prompt = prompt;
	line->reset = 0;
	line->old_buffer = NULL;
	write(1, prompt, ft_strlen(prompt));
}

char		*reset_line(t_caps *caps, t_line line)
{
	line.reset = 1;
	ft_move_line(caps, &line, NULL);
	free(line.old_buffer);
	return (line.buffer);
}

char		*ft_getline(t_caps *caps, char *prompt)
{
	t_line		line;
	char		command[16];
	ssize_t		i;

	init_getline(&line, prompt);
	i = 1;
	while (1)
	{
		i = read(0, command, 16);
		if (i <= 0)
			break ;
		command[i] = 0;
		if (i > 1)
		{
			ft_move_line(caps, &line, command);
			continue ;
		}
		if ((ft_strlen(line.buffer) == 0 && command[0] == 0x7f)
			|| (command[0] == 4 && line.cursor))
			continue ;
		else if (!ft_edit_line(caps, &line, command))
			break ;
		print_frame(caps, &line, command, line.prompt);
	}
	return (reset_line(caps, line));
}
