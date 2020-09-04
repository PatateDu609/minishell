/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:02:45 by gboucett          #+#    #+#             */
/*   Updated: 2020/08/25 17:20:30 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_subcmd(char *command, char *major, int side)
{
	char	*pos;
	char	*temp;
	char	*result;
	char	*trimmed;

	pos = ft_strnstr(command, major, ft_strlen(command));
	temp = NULL;
	if (!side)
		temp = ft_substr(command, 0, pos - command);
	else if (pos)
		temp = ft_substr(pos, 0, ft_strlen(pos));
	trimmed = ft_strjoin(major, " ");
	result = ft_strtrim(temp, trimmed);
	free(trimmed);
	free(temp);
	return (result);
}

t_btree		*ft_parse_command_args(char *command)
{
	t_command	*cmd;
	t_btree		*result;
	char		**splitted;

	if (!(cmd = (t_command *)ft_calloc(1, sizeof(t_command))))
		return (NULL);
	if (!(result = ft_btree_create_node(cmd)))
	{
		free(cmd);
		return (NULL);
	}
	if (!(splitted = ft_split(command, ' ')))
	{
		free(cmd);
		free(result);
		return (NULL);
	}
	cmd->name = splitted[0];
	cmd->args = splitted + 1;
	return (result);
}

void		free_splitted(char **splitted)
{
	char	**saved;

	saved = splitted;
	while (*splitted)
	{
		free(*splitted);
		splitted++;
	}
	free(saved);
}

t_btree		*ft_parse_command_redirect(char *command, char *sep)
{
	t_redirect	*cmd;
	t_btree		*result;
	int			i;
	int			count;
	char		**splitted;

	if (command[0] == '<' || command[0] == '>')
		return (NULL);
	i = 1;
	count = 1;
	while (command[i])
	{
		if (command[i] == '<' || (command[i] == '>' && command[i - 1] != '>'))
			count++;
		i++;
	}
	if (!(cmd = (t_redirect *)ft_calloc(count + 1, sizeof(t_redirect))))
		return (NULL);
	if (!(splitted = ft_split(command, ' ')))
	{
		free(cmd);
		return (NULL);
	}
	i = -1;
	int j = 0;
	while ((i == -1 || splitted[i]) && j < count)
	{
		if (!(i % 2))
		{
			cmd[j].target = splitted[i == -1 ? 0 : i];
			j++;
		}
		else
			cmd[j].type = i == -1 ? ft_strdup(sep) : splitted[i];
		i++;
	}
	if (!(result = ft_btree_create_node(cmd)))
	{
		free_splitted(splitted);
		free(cmd);
		return (NULL);
	}
	free(splitted);
	return (result);
}

t_btree		*ft_parse_command(char *command)
{
	t_btree		*result;
	char		*sub;
	char		*sep;

	if (!(result = ft_btree_create_node(COMMAND_STR)))
		return (NULL);
	if (!(sep = ft_get_sep(command, PARSER_TOKEN_REDIRECT)))
	{
		result->left = ft_parse_command_args(command);
		free(sep);
		return (result);
	}
	sub = ft_subcmd(command, sep, 0);
	result->left = ft_parse_command_args(sub);
	free(sub);
	sub = ft_subcmd(command, sep, 1);
	result->right = ft_parse_command_redirect(sub, sep);
	free(sub);
	free(sep);
	return (result);
}

t_btree		*ft_parse_pipeline(char *command)
{
	char	*sep;
	char	*major;
	char	*sub;
	t_btree	*cmd;

	major = ft_get_major(command, &sep);
	free(sep);
	if (ft_strncmp(major, PIPELINE_STR, ft_strlen(PIPELINE_STR)))
		return (ft_parse_command(command));
	if (!(cmd = ft_btree_create_node(PIPELINE_STR)))
		return (NULL);
	sub = ft_subcmd(command, "|", 0);
	major = ft_get_major(sub, &sep);

	if (ft_strncmp(major, PIPELINE_STR, ft_strlen(PIPELINE_STR)))
		cmd->left = ft_parse_command(sub);
	else
		cmd->left = ft_parse_pipeline(sub);
	free(sub);
	free(sep);
	sub = ft_subcmd(command, "|", 1);
	major = ft_get_major(sub, &sep);
	free(sep);
	if (ft_strncmp(major, PIPELINE_STR, ft_strlen(PIPELINE_STR)))
		cmd->right = ft_parse_command(sub);
	else
		cmd->right = ft_parse_pipeline(sub);
	free(sub);
	return (cmd);
}

char		*ft_parse_env(char *command)
{
	// char *start;
	// int

	// while (*command)
	// {
	// 	while (*command != '$')
	// 		command++;
	// }
	return command;
}

t_btree		*ft_parser(char *input)
{
	char	*sep;
	char	*major;
	char	*sub;
	char	*command;
	t_btree	*cmd;

	command = ft_parse_env(input);
	major = ft_get_major(command, &sep);
	free(sep);
	if (ft_strncmp(major, SEPARATOR_STR, ft_strlen(SEPARATOR_STR)))
		return (ft_parse_pipeline(command));
	if (!(cmd = ft_btree_create_node(SEPARATOR_STR)))
		return (NULL);
	sub = ft_subcmd(command, ";", 0);
	major = ft_get_major(sub, &sep);

	if (ft_strncmp(major, SEPARATOR_STR, ft_strlen(SEPARATOR_STR)))
		cmd->left = ft_parse_pipeline(sub);
	else
		cmd->left = ft_parser(sub);
	free(sub);
	free(sep);
	sub = ft_subcmd(command, ";", 1);
	major = ft_get_major(sub, &sep);
	free(sep);
	if (ft_strncmp(major, SEPARATOR_STR, ft_strlen(SEPARATOR_STR)))
		cmd->right = ft_parse_pipeline(sub);
	else
		cmd->right = ft_parser(sub);
	free(sub);
	free(command);
	return (cmd);
}
