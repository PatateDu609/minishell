/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:02:45 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/08 17:34:28 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_tokens(char *str, char **op)
{
	char	**result;
	size_t	len;
	size_t	i;
	char	*token[2];

	len = ft_count_tokens(str, op);
	result = ft_calloc(len + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		token[0] = ft_get_token(&str, op);
		token[1] = ft_get_operator(&str, op);
		if (token[0])
			result[i++] = token[0];
		if (token[1])
			result[i++] = token[1];
	}
	if (ft_strlen(str))
		result = ft_strs_append_str(result, str);
	return (result);
}

char	**ft_split_lexical(char *str)
{
	char	**result;
	size_t	len;
	size_t	i;
	char	*word;
	char	**op;

	op = ft_generate_op();
	len = ft_count_spaces(str);
	result = ft_calloc(len + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		word = ft_get_word(&str);
		result = ft_strs_append(result, ft_split_tokens(word, op));
		free(word);
		if (!result)
			return (NULL);
	}
	free(op);
	return (result);
}

t_list	*ft_syntax_analyser_return(t_list *cmd)
{
	if (cmd->previous)
		((t_command *)cmd->content)->type = BREAK;
	cmd = ft_lstfirst(cmd);
	return (cmd);
}

t_list	*ft_syntax_analyser(char **tokens)
{
	t_list	*cmd;
	int		type;

	cmd = NULL;
	while (*tokens)
	{
		type = (ft_strcmp(";", *tokens) == 0);
		if (!type && (!cmd || ((t_command *)cmd->content)->type > COMMAND))
			ft_add_command(&cmd, ft_strdup(*tokens));
		else if (type && cmd)
			((t_command *)cmd->content)->type = BREAK;
		else if (!ft_strcmp("|", *tokens))
			((t_command *)cmd->content)->type = PIPE;
		else if (ft_is_redirect(*tokens))
		{
			ft_add_redir(cmd, *tokens, ft_strdup(*(tokens + 1)));
			tokens++;
		}
		else
			ft_add_arg(cmd, ft_strdup(*tokens));
		tokens++;
	}
	return (ft_syntax_analyser_return(cmd));
}

t_list	*ft_parser(char *command)
{
	char	**tokens;
	int		valid;
	t_list	*parsed;

	command = ft_init_parsing(command);
	tokens = ft_split_lexical(command);
	free(command);
	if (!tokens)
		return (NULL);
	valid = ft_check_validity(tokens);
	if (!valid)
	{
		free_splitted(tokens);
		return (NULL);
	}
	parsed = ft_syntax_analyser(tokens);
	if (!parsed)
		return (NULL);
	free_splitted(tokens);
	return (parsed);
}
