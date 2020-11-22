/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 01:24:44 by gboucett          #+#    #+#             */
/*   Updated: 2020/11/22 03:59:27 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static void		print_command(t_btree	*parsed)
{
	printf("\033[1;32m%s\033[0m\n", (char *) parsed->item);
	printf("\033[0;34m%s\033[0m\n", ((t_command *)parsed->left->item)->name);
	char **args = ((t_command *) parsed->left->item)->args;
	while (args && *args)
	{
		printf("%s\n", *args);
		args++;
	}
	if (parsed->right)
	{
		t_redirect	*redirections = (t_redirect *)parsed->right->item;
		while (redirections->target)
		{
			printf("\033[0;35m%s\033[0m %s\n", redirections->type, redirections->target);
			redirections++;
		}
	}
}

static void		print_pipeline(t_btree *parsed)
{
	int len;

	len = ft_strlen(PIPELINE_STR);
	if (ft_strncmp(parsed->item, PIPELINE_STR, len))
	{
		print_command(parsed);
		return ;
	}
	printf("\033[1;31mPIPELINE\033[0m\n");
	if (ft_strncmp(parsed->left->item, PIPELINE_STR, len))
		print_command(parsed->left);
	else
		print_pipeline(parsed->left);
	if (ft_strncmp(parsed->right->item, PIPELINE_STR, len))
		print_command(parsed->right);
	else
		print_pipeline(parsed->right);
	printf("\n");
}

void			print_separator(t_btree *parsed)
{
	int len;

	len = ft_strlen(SEPARATOR_STR);
	if (ft_strncmp(parsed->item, SEPARATOR_STR, len))
	{
		print_pipeline(parsed);
		return ;
	}
	printf("\033[1;31mSEPARATOR\033[0m\n");
	if (ft_strncmp(parsed->left->item, SEPARATOR_STR, len))
		print_pipeline(parsed->left);
	else
		print_separator(parsed->left);
	if (ft_strncmp(parsed->right->item, SEPARATOR_STR, len))
		print_pipeline(parsed->right);
	else
	{
		printf("\n");
		print_separator(parsed->right);
	}
}
