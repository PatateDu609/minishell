/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 22:47:54 by gboucett          #+#    #+#             */
/*   Updated: 2020/10/22 00:51:21 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void			ft_cursor_home_end(t_caps *caps, t_line *line, int mode)
{
	if (!mode)
	{
		while (line->cursor < ft_strlen(line->buffer))
		{
			tputs(caps->nd, 1, ms_putchar);
			line->cursor++;
		}
	}
	else
	{
		while (line->cursor > 0)
		{
			tputs(caps->le, 1, ms_putchar);
			line->cursor--;
		}
	}
}

void		ft_cursor_move_word(t_caps *caps, t_line *line, int mode)
{
	char	*dir;
	int		m;
	long	pos;

	pos = line->cursor;
	dir = mode ? caps->le : caps->nd;
	m = mode ? -1 : 1;
	if (mode)
	{
		pos--;
		tputs(caps->le, 1, ms_putchar);
	}
	while (!ft_isalnum(line->buffer[pos]) && pos < (long)ft_strlen(line->buffer))
	{
		tputs(dir, 1, ms_putchar);
		pos += 1 * m;
	}
	while (ft_isalnum(line->buffer[pos]) && pos < (long)ft_strlen(line->buffer))
	{
		tputs(dir, 1, ms_putchar);
		pos += 1 * m;
	}
	if (mode)
	{
		pos++;
		tputs(caps->nd, 1, ms_putchar);
	}
	while (pos < 0)
	{
		pos++;
		tputs(caps->nd, 1, ms_putchar);
	}
	while (pos > (long)ft_strlen(line->buffer))
	{
		pos--;
		tputs(caps->le, 1, ms_putchar);
	}
	line->cursor = pos;
}

int				ft_parse_arrow(char *command)
{
	command += 2;
	if (('A' <= *command && *command <= 'D'))
		return (*command - 65);
	if (*command == 'H')
		return (4);
	if (*command == 'F')
		return (5);
	if (*command != '1' && *(command + 1) != ';' && *(command + 2) != '5')
		return (-1);
	command += 3;
	if (*command == 'D')
		return (6);
	if (*command == 'C')
		return (7);
	return (-1);
}
