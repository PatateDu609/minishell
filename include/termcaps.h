/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 01:00:50 by gboucett          #+#    #+#             */
/*   Updated: 2020/10/20 16:22:45 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

# include "ft_defs.h"

# include <termios.h>
# include <term.h>
# include <termcaps.h>

typedef struct termios	t_termios;

typedef struct			s_line
{
	size_t				cursor;
	char				*buffer;
}						t_line;

/**
 * Contains the needed termcaps
 * le : move one character to the left
 * nd : move one character to the right
 * sc : save cursor position
 * rc : restore cursor position
 * dl : delete one line
 * reset : reset termcaps
 */
typedef struct			s_caps
{
	char				*le;
	char				*nd;
	char				*rc;
	char				*sc;
	char				*dl;
	char				*reset;
}						t_caps;

int						init_termcaps(t_env *env, t_caps *caps);
int						init_termios(t_termios *backup);
int						reset_terminal(t_termios *backup, t_caps *caps);
int						ms_putchar(int c);
void					ft_move_line(t_caps *caps, t_line *line, char *command);
char					*ft_add_char(char *str, int i, char *c);
char					*ft_delete_char(char *str, int i);
char					*ft_getline(t_caps *caps, char *prompt);

#endif
