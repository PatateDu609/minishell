/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 01:00:31 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/31 02:00:41 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"
#include "ft_env.h"

int	ms_putchar(int c)
{
	write(1, &c, 1);
	return (c);
}

int	init_termcaps(t_caps *caps)
{
	char	*term;

	term = ft_getvar("TERM");
	term = NULL;
	if (!term)
		term = ft_strdup("xterm-256color");
	if (tgetent(NULL, term) <= 0)
		return (0);
	free(term);
	caps->reset = tgetstr("me", NULL);
	caps->le = tgetstr("le", NULL);
	caps->nd = tgetstr("nd", NULL);
	caps->dl = tgetstr("dl", NULL);
	caps->sc = tgetstr("sc", NULL);
	caps->rc = tgetstr("rc", NULL);
	return (1);
}

int	init_termios(struct termios *backup)
{
	struct termios	term_attr;

	if (tcgetattr(STDIN_FILENO, &term_attr))
		return (0);
	if (tcgetattr(STDIN_FILENO, backup))
		return (0);
	term_attr.c_lflag &= ~(ICANON | ECHO);
	term_attr.c_cc[VMIN] = 1;
	term_attr.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term_attr))
		return (0);
	return (1);
}

int	reset_terminal(struct termios *backup, t_caps *caps)
{
	tputs(caps->reset, 1, ms_putchar);
	return (!tcsetattr(STDIN_FILENO, TCSANOW, backup));
}
