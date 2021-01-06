/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 01:00:50 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 19:28:51 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

# include "ft_defs.h"

# include <termios.h>
# include <term.h>
# include <termcaps.h>

typedef struct	s_line
{
	size_t		cursor;
	char		*buffer;
	char		*old_buffer;
	char		*prompt;
	int			reset;
}				t_line;

extern char		*g_history[HISTORY_SIZE];
extern int		g_last;

/*
** Contains the needed termcaps
** le : move one character to the left
** nd : move one character to the right
** sc : save cursor position
** rc : restore cursor position
** dl : delete one line
** reset : reset termcaps
*/
typedef struct	s_caps
{
	char		*le;
	char		*nd;
	char		*rc;
	char		*sc;
	char		*dl;
	char		*reset;
}				t_caps;

int				init_termcaps(t_caps *caps);
int				init_termios(struct termios *backup);
int				reset_terminal(struct termios *backup, t_caps *caps);
int				ms_putchar(int c);
void			ft_move_line(t_caps *caps, t_line *line, char *command);
char			*ft_add_char(char *str, int i, char *c);
char			*ft_delete_char(char *str, int i);
char			*ft_getline(t_caps *caps, char *prompt);
void			load_history(void);
void			add_command(char *command);
void			write_commands(void);
void			ft_cursor_home_end(t_caps *caps, t_line *line, int mode);
int				ft_parse_arrow(char *command);
void			ft_cursor_move_word(t_caps *caps, t_line *line, int mode);

#endif
