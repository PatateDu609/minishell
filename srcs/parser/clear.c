/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 18:13:32 by gboucett          #+#    #+#             */
/*   Updated: 2020/11/06 01:21:05 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

void	free_command(t_btree *parsed)
{
	t_command		*command;
	t_redirect		*redirections;
	t_redirect		*tmp;

	command = parsed->left->item;
	free_splitted(command->args - 1);
	free(command);
	if (parsed->right)
	{
		redirections = (t_redirect *)parsed->right->item;
		tmp = redirections;
		while (tmp->target)
		{
			free(tmp->target);
			free(tmp->type);
			tmp++;
		}
		free(redirections);
	}
	free(parsed->left);
	free(parsed->right);
	free(parsed);
}

void	free_pipeline(t_btree *parsed)
{
	int		len;

	if (!parsed)
		return ;
	len = ft_strlen(PIPELINE_STR);
	if (ft_strncmp(parsed->item, PIPELINE_STR, len))
	{
		free_command(parsed);
		return ;
	}
	if (ft_strncmp(parsed->left->item, PIPELINE_STR, len))
		free_command(parsed->left);
	else
		free_pipeline(parsed->left);
	if (parsed->right && ft_strncmp(parsed->right->item, PIPELINE_STR, len))
		free_command(parsed->right);
	else
		free_pipeline(parsed->right);
	free(parsed);
}

void	free_parsed(t_btree *parsed)
{
	int		len;

	if (!parsed)
		return ;
	len = ft_strlen(SEPARATOR_STR);
	if (ft_strncmp(parsed->item, SEPARATOR_STR, len))
	{
		free_pipeline(parsed);
		return ;
	}
	if (ft_strncmp(parsed->left->item, SEPARATOR_STR, len))
		free_pipeline(parsed->left);
	else
		free_parsed(parsed->left);
	if (parsed->right && ft_strncmp(parsed->right->item, SEPARATOR_STR, len))
		free_pipeline(parsed->right);
	else
		free_parsed(parsed->right);
	free(parsed);
}
