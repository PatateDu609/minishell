/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:03:02 by gboucett          #+#    #+#             */
/*   Updated: 2020/10/20 16:07:04 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	ft_move_line(t_caps *caps, t_line *line, char *command)
{
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
