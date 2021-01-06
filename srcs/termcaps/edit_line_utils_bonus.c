/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 22:47:54 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 19:54:11 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void		ft_cursor_home_end(t_caps *caps, t_line *line, int mode)
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

static void	ft_move_word(t_caps *caps, t_line *line, int mode, long *pos)
{
	char	*dir;
	int		m;

	m = ft_ternaryi(mode, -1, 1);
	dir = (char *)ft_ternary(mode, (void *)caps->le, (void *)caps->nd);
	if (mode)
	{
		*pos -= 1;
		tputs(caps->le, 1, ms_putchar);
	}
	while (!ft_isalnum(line->buffer[*pos]) && *pos
		< (long)ft_strlen(line->buffer))
	{
		tputs(dir, 1, ms_putchar);
		*pos += 1 * m;
	}
	while (ft_isalnum(line->buffer[*pos]) && *pos
		< (long)ft_strlen(line->buffer))
	{
		tputs(dir, 1, ms_putchar);
		*pos += 1 * m;
	}
}

void		ft_cursor_move_word(t_caps *caps, t_line *line, int mode)
{
	long	pos;

	pos = line->cursor;
	ft_move_word(caps, line, mode, &pos);
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

int			ft_parse_arrow(char *command)
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
