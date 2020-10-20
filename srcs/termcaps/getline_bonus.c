/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:07:50 by gboucett          #+#    #+#             */
/*   Updated: 2020/10/20 16:45:34 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

char	*ft_getline(t_caps *caps, char *prompt)
{
	t_line		line;
	char		command[16];
	char		*tmp;
	ssize_t		i;

	line.cursor = 0;
	line.buffer = ft_strdup("");
	write(1, prompt, ft_strlen(prompt));
	while ((i = read(0, command, 16)) > 0)
	{
		command[i] = 0;
		if (i > 1)
		{
			ft_move_line(caps, &line, command);
			continue ;
		}
		if ((ft_strlen(line.buffer) == 0 && command[0] == 0x7f) || (command[0] == 4 && line.cursor))
			continue;
		else if (command[0] == 0x7f)
		{
			tmp = line.buffer;
			line.buffer = ft_delete_char(line.buffer, line.cursor);
			line.cursor--;
			tputs(caps->le, 1, ms_putchar);
			free(tmp);
		}
		else if (command[0] == '\n' || (command[0] == 4 && !line.cursor))
		{
			if (command[0] == '\n')
				write(1, "\n", 1);
			break;
		}
		else
		{
			tmp = line.buffer;
			line.buffer = ft_add_char(line.buffer, line.cursor, command);
			line.cursor++;
			free(tmp);
		}
		if (line.cursor < ft_strlen(line.buffer))
			tputs(caps->sc, 1, ms_putchar);
		tputs(caps->dl, 1, ms_putchar);
		write(1, prompt, ft_strlen(prompt));
		write(1, line.buffer, ft_strlen(line.buffer));
		if (line.cursor < ft_strlen(line.buffer))
		{
			tputs(caps->rc, 1, ms_putchar);
			if (command[0] != 0x7f)
				tputs(caps->nd, 1, ms_putchar);
		}
	}
	return (line.buffer);
}
