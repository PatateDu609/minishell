/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:29:53 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/31 00:58:41 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

# include "ft_defs.h"

void		ft_print_splitted(char **strs);
void		ft_print_redirs(t_redirect **redirs);
void		ft_print_command(void *cmdv);
int			ft_print_error(char *error);

void		free_splitted(char **strs);
void		ft_free_command(void *cmdv);

char		**ft_generate_op(void);
int			ft_is_redirect(char *str);
char		*ft_strstr_op(char *str, char *op);
char		*ft_find_next_op(char *str, char **op, size_t *len);
int			ft_is_operator(char *str, char **op);

size_t		ft_skip_quotes(char **str, char quote);
char		*ft_expand_quoted(char *str);

size_t		ft_size_quoted(char *str);
size_t		ft_size_splitted(char **strs);
size_t		ft_size_redirs(t_redirect **redirs);
size_t		ft_wordlen(char *str);

char		**ft_copy_splitted(char **strs, size_t new_len);
t_redirect	**ft_append_redir(t_redirect **redirs, t_redirect *redir);
char		**ft_strs_append(char **strs1, char **to_append);
char		**ft_strs_append_str(char **strs, char *str);
char		**ft_strs_remove(char **strs, size_t index);

size_t		ft_count_tokens(char *str, char **op);
size_t		ft_count_spaces(char *str);
char		*ft_get_word(char **str);
char		*ft_get_token(char **str, char **op);
char		*ft_get_operator(char **str, char **op);

int			ft_check_quotes(char *token);
int			ft_check_last(char *last_token, char **op, size_t len);
int			ft_check_validity(char **litteral);

int			ft_add_command(t_list **lst, char *name);
int			ft_add_arg(t_list *lst, char *arg);
int			ft_add_redir(t_list *lst, char *redir, char *target);

void		ft_expand_env(t_list *parsed);

t_list		*ft_syntax_analyser(char **tokens);
char		**ft_split_lexical(char *str);
char		**ft_split_tokens(char *str, char **op);
t_list		*ft_parser(char *command);

#endif
