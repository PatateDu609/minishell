/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 02:51:10 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/31 05:08:19 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

void	ft_exec(t_list *commands)
{
	t_command	*command;

	while (commands)
	{
		command = (t_command *)commands->content;

		commands = commands->next;
	}
}
